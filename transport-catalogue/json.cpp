#include "json.h"
#include <sstream>
#include <algorithm>
#include <variant>

using namespace std;

namespace json {

    namespace {

        Node LoadNode(istream& input);
        Node LoadDict(istream& input);
        Node LoadString(istream& input);

        Node LoadArray(istream& input) {
            Array result;

            string str = {};
            std::stringstream ss;

            char last = ' ';
            char c;
            while (input >> c) {
                if (c == ']') {
                    last = c;
                    break;
                }
                if (c != ',') {
                    input.putback(c);
                }

                result.emplace_back(LoadNode(input));

                last = c;
            }

            if (last != ']') {
                throw ParsingError("Array parsing error!"s);
            }

            return Node(move(result));
        }
        Node LoadDict(istream& input) {
            Dict result;

            string str = {};
            std::stringstream ss;

            char last = ' ';
            char c;
            while (input >> c) {
                if (c == '}') {
                    last = c;
                    break;
                }

                if (c == ',') {
                    input >> c;
                }

                string key = LoadString(input).AsString();

                input >> c;

                result.insert({move(key), LoadNode(input)});

                last = c;
            }
            if (last != '}') {
                throw ParsingError("Map parsing error!"s);
            }

            return Node(move(result));
        }

        using Number = std::variant<int, double>;

        Number LoadNumber(std::istream& input) {
            using namespace std::literals;

            std::string parsed_num;

            // Считывает в parsed_num очередной символ из input
            auto read_char = [&parsed_num, &input] {
                parsed_num += static_cast<char>(input.get());
                if (!input) {
                    throw ParsingError("Failed to read number from stream"s);
                }
            };

            // Считывает одну или более цифр в parsed_num из input
            auto read_digits = [&input, read_char] {
                if (!std::isdigit(input.peek())) {
                    throw ParsingError("A digit is expected"s);
                }
                while (std::isdigit(input.peek())) {
                    read_char();
                }
            };

            if (input.peek() == '-') {
                read_char();
            }
            // Парсим целую часть числа
            if (input.peek() == '0') {
                read_char();
                // После 0 в JSON не могут идти другие цифры
            } else {
                read_digits();
            }

            bool is_int = true;
            // Парсим дробную часть числа
            if (input.peek() == '.') {
                read_char();
                read_digits();
                is_int = false;
            }

            // Парсим экспоненциальную часть числа
            if (int ch = input.peek(); ch == 'e' || ch == 'E') {
                read_char();
                if (ch = input.peek(); ch == '+' || ch == '-') {
                    read_char();
                }
                read_digits();
                is_int = false;
            }

            try {
                if (is_int) {
                    // Сначала пробуем преобразовать строку в int
                    try {
                        return std::stoi(parsed_num);
                    } catch (...) {
                        // В случае неудачи, например, при переполнении,
                        // код ниже попробует преобразовать строку в double
                    }
                }
                return std::stod(parsed_num);
            } catch (...) {
                throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
            }
        }

        // Считывает содержимое строкового литерала JSON-документа
        // Функцию следует использовать после считывания открывающего символа ":
        Node LoadString(istream& input) {
            using namespace std::literals;

            auto it = std::istreambuf_iterator<char>(input);
            auto end = std::istreambuf_iterator<char>();
            std::string s;
            while (true) {
                if (it == end) {
                    // Поток закончился до того, как встретили закрывающую кавычку?
                    throw ParsingError("String parsing error");
                }
                const char ch = *it;
                if (ch == '"') {
                    // Встретили закрывающую кавычку
                    ++it;
                    break;
                } else if (ch == '\\') {
                    // Встретили начало escape-последовательности
                    ++it;
                    if (it == end) {
                        // Поток завершился сразу после символа обратной косой черты
                        throw ParsingError("String parsing error");
                    }
                    const char escaped_char = *(it);
                    // Обрабатываем одну из последовательностей: \\, \n, \t, \r, \"
                    switch (escaped_char) {
                        case 'n':
                            s.push_back('\n');
                            break;
                        case 't':
                            s.push_back('\t');
                            break;
                        case 'r':
                            s.push_back('\r');
                            break;
                        case '"':
                            s.push_back('"');
                            break;
                        case '\\':
                            s.push_back('\\');
                            break;
                        default:
                            // Встретили неизвестную escape-последовательность
                            throw ParsingError("Unrecognized escape sequence \\"s + escaped_char);
                    }
                } else if (ch == '\n' || ch == '\r') {
                    // Строковый литерал внутри- JSON не может прерываться символами \r или \n
                    throw ParsingError("Unexpected end of line"s);
                } else {
                    // Просто считываем очередной символ и помещаем его в результирующую строку
                    s.push_back(ch);
                }
                ++it;
            }
            //cout << "string "s << s << endl;
            return Node(move(s));
        }

        Node LoadBool(istream& input) {
            string str;

            char c;
            while (input >> c) {
                if (c == ',' || c == '}' || c == ']') {
                    input.putback(c);
                    break;
                }
                str += c;
            }

            if (str != "true"s && str != "false"s) {
                throw ParsingError("Bool parsing error!"s);
            }
            return str == "true"s ? Node{true} : Node{false};
        }

        Node LoadNull(istream& input) {
            string str;
            char c;
            while (input >> c) {
                if (c == ',' || c == '}' || c == ']') {
                    input.putback(c);
                    break;
                }
                str += c;
            }
            //cout << str << endl;
            if (str != "null"s) {
                throw ParsingError("Null parsing error!"s);
            }
            return Node();
        }

        Node LoadNode(istream& input) {
            char c;
            input >> c;

            if (c == ']' || c == '}') {
                throw ParsingError("Parsing error!"s);
            }

            if (c == '[') {
                return LoadArray(input);
            } else if (c == '{') {
                return LoadDict(input);
            } else if (c == '"') {
                return LoadString(input);
            } else if (c == 'n') {
                input.putback(c);
                return LoadNull(input);
            } else if (c == 't' || c == 'f') {
                input.putback(c);
                return LoadBool(input);
            } else {
                input.putback(c);
                Number number = LoadNumber(input);
                if (holds_alternative<double>(number)) {
                    return Node(get<double>(number));
                } else {
                    return Node(get<int>(number));
                }
            }
        }
    }  // namespace

// ------------ Node ------------

    Node::Node(Array array)
            : value_(move(array)) {
    }

    Node::Node(Dict map)
            : value_(move(map)) {
    }

    Node::Node(int value)
            : value_(value) {
    }

    Node::Node(double value)
            : value_(value) {
    }

    Node::Node(string value)
            : value_(move(value)) {
    }

    Node::Node(std::nullptr_t null)
            : value_(null) {
    }

    Node::Node(bool b)
            : value_(b) {
    }

    bool Node::IsInt() const {

        if (const auto* roots = get_if<int>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsDouble() const {
        if (const auto* roots = get_if<double>(&value_)) {
            (void)roots;
            return true;
        } else if (const auto* roots1 = get_if<int>(&value_)) {
            (void)roots1;
            return true;
        }
        return false;
    }
    bool Node::IsPureDouble() const {
        if (const auto* roots = get_if<double>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsBool() const {
        if (const auto* roots = get_if<bool>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsString() const {
        if (const auto* roots = get_if<string>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsNull() const {
        if (const auto* roots = get_if<nullptr_t>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsArray() const {
        if (const auto* roots = get_if<Array>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }
    bool Node::IsMap() const {
        if (const auto* roots = get_if<Dict>(&value_)) {
            (void)roots;
            return true;
        }
        return false;
    }

    int Node::AsInt() const {
        if (IsInt()) {
            return get<int>(value_);
        }
        throw logic_error("AsInt not int!"s);
    }
    bool Node::AsBool() const {
        if (IsBool()) {
            return get<bool>(value_);
        }
        throw logic_error("AsBool is not a bool"s);
    }
    double Node::AsDouble() const {
        if (IsPureDouble()) {
            return get<double>(value_);
        } else if (IsInt()) {
            return get<int>(value_);
        }
        throw logic_error("AsDouble is not a double or int!"s);
    }
    const string& Node::AsString() const {
        if (IsString()) {
            return get<string>(value_);
        }
        throw logic_error("AsString not string");
    }
    const Array& Node::AsArray() const {
        if (IsArray()) {
            return get<Array>(value_);
        }
        throw logic_error("AsArray not array"s);
    }
    const Dict& Node::AsMap() const {
        if (IsMap()) {
            return get<Dict>(value_);
        }
        throw logic_error("AsMap is not a map"s);
    }

    bool operator==(const Node& lhs, const Node& rhs) {
        return lhs.GetValue() == rhs.GetValue();
    }
    bool operator!=(const Node& lhs, const Node& rhs) {
        return lhs.GetValue() != rhs.GetValue();
    }


// ------------ Document ------------

    Document::Document(Node root)
            : root_(move(root)) {
    }

    const Node& Document::GetRoot() const {
        return root_;
    }

    bool operator==(const Document& lhs, const Document& rhs) {
        return lhs.GetRoot().GetValue() == rhs.GetRoot().GetValue();
    }

    bool operator!=(const Document& lhs, const Document& rhs) {
        return lhs.GetRoot().GetValue() != rhs.GetRoot().GetValue();
    }


// ------------ Other ------------

    Document Load(istream& input) {
        return Document{LoadNode(input)};
    }

    // Контекст вывода, хранит ссылку на поток вывода и текущий отсуп
    struct PrintContext {
        std::ostream& out;
        int indent_step = 4;
        int indent = 0;

        void PrintIndent() const {
            for (int i = 0; i < indent; ++i) {
                out.put(' ');
            }
        }

        // Возвращает новый контекст вывода с увеличенным смещением
        PrintContext Indented() const {
            return {out, indent_step, indent_step + indent};
        }
    };

    struct OstreamNodePrinter {
        ostream& out;

        void operator()(nullptr_t) const {
            out << "null"s;
            //cout << "null"s;
        }
        void operator()(double root) const {
            out <<  root;
            //cout <<  root;
        }
        void operator()(int root) const {
            out << root;
            //cout <<  root;
        }
        void operator()(bool root) const {
            out << boolalpha << root;
            //cout << boolalpha << root;
        }
        void operator()(string str) const {
            out << "\""s;
            for (const auto& c : str) {
                switch (c) {
                    case '"' : out << "\\"s << c;
                        break;
                    case '\n' : out << "\\n"s;
                        break;
                    case '\r' : out << "\\r"s;
                        break;
                    case '\\' : out << "\\"s << c;
                        break;
                    default:
                        out << c;
                }
            }
            out << "\""s;
        }
        void operator()(Array root) const {
            out << "["s;
            int size = root.size();
            int count = 0;
            for (const auto& a : root) {
                visit(OstreamNodePrinter{out}, a.GetValue());

                if (count != size - 1) {
                    out << ',';
                    //cout << ',';
                }
                ++count;
            }
            out << "]"s;

        }
        void operator()(Dict root) const {
            out << '{';
            int size = root.size();
            int count = 0;
            for (const auto& [key, value] : root) {
                out << '"' << key << '"' << ": "s;

                visit(OstreamNodePrinter{out}, value.GetValue());

                if (count != size - 1) {
                    out << ',';
                }
                ++count;
            }
            out << '}';
        }
    };

    template <typename Value>
    void PrintValue(const Value& value, const PrintContext& ctx) {
        //visit(OstreamNodePrinter{output}, doc.GetRoot().GetValue());
    }

    void Print(const Document& doc, std::ostream& output) {
        visit(OstreamNodePrinter{output}, doc.GetRoot().GetValue());
    }

    std::string Print(const Node& node) {
        std::ostringstream out;
        Print(Document{node}, out);
        return out.str();
    }

}  // namespace json