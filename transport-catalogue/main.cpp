#include "transport_catalogue.h"
#include "json_reader.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void RunFile() {
    using namespace transport;

    TransportCatalogue catalogue;
    ifstream data_file("test_json_input.txt"s);
    JsonReader json_reader(data_file);
    json_reader.FillCatalogue(catalogue);
    ofstream output("test_json_output.txt"s);
    json_reader.OutputStat(catalogue, output);
}

void RunCin() {
    using namespace transport;

    TransportCatalogue catalogue;
    JsonReader json_reader(cin);
    json_reader.FillCatalogue(catalogue);
    json_reader.OutputStat(catalogue, cout);
}

int main() {
    RunCin();
    //RunFile();

    return 0;
}
