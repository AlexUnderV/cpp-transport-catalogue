#include "transport_catalogue.h"
#include "input_reader.h"
#include "stat_reader.h"
//#include "global_tests.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void RunFile() {
    using namespace transport;

    ifstream data_file("tsC_case1_data_input.txt"s);
    auto raw_data = input::Data(data_file);

    TransportCatalogue catalogue;
    FillCatalogue(catalogue, raw_data);


    std::fstream fs("somefile.txt");
    ifstream query_file("tsC_case1_query_input.txt"s);
    output::Output(input::Query(query_file), catalogue, fs);
}

void RunCin() {
    using namespace transport;

    auto raw_data = input::Data(cin);

    TransportCatalogue catalogue;
    FillCatalogue(catalogue, raw_data);

    output::Output(input::Query(cin), catalogue, cout);
}

/*void Tests() {
    transport::test::ParseStop();
    transport::test::ParseStopWithDistance();
    transport::test::CalculateDistance();
}*/

int main() {
    //Tests();
    //TestFromFile3();

    RunCin();
    //RunFile();

    return 0;
}
