#include "transport_catalogue.h"
#include "input_reader.h"
#include "stat_reader.h"
//#include "global_tests.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Run() {
    using namespace transport;
    auto raw_data = input::DataFromCommandLine();

    TransportCatalogue catalogue;
    TransportCatalogue& link = catalogue;

    FillCatalogue(link, raw_data);

    output::Output(input::QueryFromCommandLine(), link);
}

/*void Tests() {
    transport::test::ParseStop();
    transport::test::ParseStopWithDistance();
    transport::test::CalculateDistance();
}*/

int main() {
    //Tests();
    //TestFromFile3();

    Run();


    return 0;
}
