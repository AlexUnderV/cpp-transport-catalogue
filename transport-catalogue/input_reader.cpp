#include "input_reader.h"

#include <algorithm>
#include <fstream>

using namespace std;



transport::Stop transport::parse::OnStop(string& line) {

    string stop_name;
    auto pos_p = line.find_first_of('p');
    auto pos_div = line.find_first_of(':');
    stop_name = line.substr(pos_p + 2, pos_div - 5);

    string coordinates = line.substr(pos_div + 2, line.size() - 1);

    string num1;
    string num2;
    auto pos_middle = coordinates.find_first_of(',');
    num1 = coordinates.substr(0, pos_middle);
    num2 = coordinates.substr(pos_middle + 2, coordinates.size() - 1);



    if (count(num2.begin(), num2.end(), ',') > 0) {
        auto pos_end = num2.find_first_of(',');
        string num2_cut = num2.substr(0, pos_end);

        //cout << "("s << stop_name << ") - ("s << num1 << ") - ("s << num2_cut << ")"s << endl;

        return {stop_name, {stod(num1), stod(num2_cut)}};
    }
    //cout << "("s << stop_name << ") - ("s << num1 << ") - ("s << num2 << ")"s << endl;

    return {stop_name, {stod(num1), stod(num2)}};
}
transport::StopDistances transport::parse::OnStopWithDistances(std::string& line) {
    string stop_name;
    auto pos_p = line.find_first_of('p');
    auto pos_div = line.find_first_of(':');
    stop_name = line.substr(pos_p + 2, pos_div - 5);

    auto first_comma = line.find_first_of(',');
    string delete_first_comma = line.substr(first_comma + 2, line.size() - 1);
    auto second_comma = delete_first_comma.find_first_of(',');
    string distances = delete_first_comma.substr(second_comma + 2, delete_first_comma.size() - 1);

    //cout << "("s << stop_name << ") - ("s << distances << ")"s << endl;

    int count_distances = count(distances.begin(), distances.end(), ',') + 1;
    vector<pair<string, int64_t>> dists;
    while (count_distances-- != 0) {
        auto sign_pos = distances.find_first_of(',');
        string dist = distances.substr(0, sign_pos);

        auto pos_m = dist.find_first_of('m');
        string metrs = dist.substr(0, pos_m);
        string stop = dist.substr(pos_m + 5, dist.size() - 1);

        dists.push_back({stop, stoi(metrs)});
        string temp = distances.substr(sign_pos + 2, distances.size() - 1);
        distances = temp;
    }

    /*for (auto& d : dists) {
        cout << "("s << d.first << ") - ("s << d.second << ")"s << endl;
    }*/
    return {stop_name, dists};
}
transport::Bus transport::parse::OnBus(string& line, const unordered_map<string_view, Stop*>& for_stop_ptrs) {

    string cut_bus_begin;
    auto pos_s = line.find_first_of('s');
    cut_bus_begin = line.substr(pos_s + 2, line.size() - 1);

    string bus_name;
    auto bus_name_end = cut_bus_begin.find_first_of(':');
    bus_name = cut_bus_begin.substr(0, bus_name_end);

    string travels;
    auto travels_begin = line.find_first_of(':');
    travels = line.substr(travels_begin + 2, line.size() - 1);


    BusType type;
    char sign;
    int count_sign = 0;

    if (find(travels.begin(), travels.end(), '>') != travels.end()) {
        count_sign = count(travels.begin(), travels.end(), '>') + 1;
        sign = '>';
        type = BusType::RING;
    } else {
        count_sign = count(travels.begin(), travels.end(), '-') + 1;
        sign = '-';
        type = BusType::DIRECT;
    }

    vector<string> stops;
    while (count_sign-- != 0) {
        auto sign_pos = travels.find_first_of(sign);
        string stop = travels.substr(0, sign_pos - 1);
        stops.push_back(stop);
        string temp = travels.substr(sign_pos + 2, travels.size() - 1);
        travels = temp;
    }

    vector<Stop*> stops_ptrs;
    for (const auto& stop : stops) {
        stops_ptrs.push_back(for_stop_ptrs.at(stop));
    }

    return {bus_name, stops_ptrs, type};
}


transport::RawData transport::input::DataFromCommandLine() {
    int count_data_input = 0;
    cin >> count_data_input;
    ++count_data_input;

    RawData raw_data;

    string line;
    while (count_data_input-- > 0) {
        getline(cin, line);
        if (line[0] == 'S') {
            raw_data.stops.push_back(line);
        } else if (line[0] == 'B') {
            raw_data.buses.push_back(line);
        }
    }
    return raw_data;
}
std::vector<transport::Query> transport::input::QueryFromCommandLine() {
    int count = 0;
    cin >> count;

    vector<Query> raw_query;

    ++count;
    string line;
    while (count-- > 0) {
        getline(cin, line);
        if (line[0] == 'B') {

            string cut_bus_word;
            auto pos_s = line.find_first_of('s');
            cut_bus_word = line.substr(pos_s + 2, line.size() - 1);

            raw_query.push_back({transport::QyeryTypes::BUS, cut_bus_word});
        } else if (line[0] == 'S') {

            string cut_stop_word;
            auto pos_s = line.find_first_of('p');
            cut_stop_word = line.substr(pos_s + 2, line.size() - 1);

            raw_query.push_back({transport::QyeryTypes::STOP, cut_stop_word});
        }
    }
    return raw_query;
}

transport::RawData transport::input::DataFromFile(string file_name) {
    ifstream myfile;
    myfile.open(file_name);
    RawData raw_data;
    string line;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] == 'S') {
                raw_data.stops.push_back(line);
            } else if (line[0] == 'B') {
                raw_data.buses.push_back(line);
            }
        }
    }
    return raw_data;
}
vector<transport::Query> transport::input::QueryFromFile(string file_name) {
    ifstream myfile;
    myfile.open(file_name);
    vector<Query> raw_query;
    string line;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] == 'B') {

                string cut_bus_word;
                auto pos_s = line.find_first_of('s');
                cut_bus_word = line.substr(pos_s + 2, line.size() - 1);

                raw_query.push_back({transport::QyeryTypes::BUS, cut_bus_word});
            } else if (line[0] == 'S') {

                string cut_stop_word;
                auto pos_s = line.find_first_of('p');
                cut_stop_word = line.substr(pos_s + 2, line.size() - 1);

                raw_query.push_back({transport::QyeryTypes::STOP, cut_stop_word});
            }
        }
    }
    return raw_query;
}


void transport::FillCatalogue(transport::TransportCatalogue& catalogue, RawData& raw_data) {
    vector<string> temp_distance;

    for (auto& stop : raw_data.stops) {
        if (count(stop.begin(), stop.end(), ',') > 1) {
            temp_distance.push_back(stop);
        }
        auto st = parse::OnStop(stop);
        catalogue.AddStop(st);
    }

    for (auto& distance : temp_distance) {
        auto d = parse::OnStopWithDistances(distance);
        catalogue.AddDistance(d);
    }

    const auto stops_in_catalogue_ptrs = catalogue.GetStopPtrs();
    for (auto& bus : raw_data.buses) {
        auto b = parse::OnBus(bus, stops_in_catalogue_ptrs);
        catalogue.AddBus(b);
    }
}