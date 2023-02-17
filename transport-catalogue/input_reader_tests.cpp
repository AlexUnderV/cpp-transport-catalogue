#include "input_reader.h"

#include <cassert>

using namespace std;
using namespace transport;

void test::ParseStop() {
    {
        {
            Stop stop1 = {"Tolstopaltsevo"s, {55.611087, 37.20829}};

            string line1 = "Stop Tolstopaltsevo: 55.611087, 37.20829"s;
            string line2 = "Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino"s;

            assert(stop1 == parse::OnStop(line1));
            assert(stop1 == parse::OnStop(line2));
        }

        {
            Stop stop1 = {"Biryulyovo Zapadnoye"s, {55.574371, 37.6517}};

            string line1 = "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517"s;
            string line2 = "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam"s;

            assert(stop1 == parse::OnStop(line1));
            assert(stop1 == parse::OnStop(line2));
        }

        {
            Stop stop1 = {"M"s, {55.595884, 37.209755}};

            string line1 = "Stop M: 55.595884, 37.209755"s;
            string line2 = "Stop M: 55.595884, 37.209755, 9900m to Rasskazovka, 100m to Marushkino"s;

            assert(stop1 == parse::OnStop(line1));
            assert(stop1 == parse::OnStop(line2));
        }

        {
            Stop stop1 = {"A"s, {-55.595884, 37.209755}};

            string line1 = "Stop A: -55.595884, 37.209755"s;
            string line2 = "Stop A: -55.595884, 37.209755, 9900m to Rasskazovka, 100m to Marushkino"s;

            assert(stop1 == parse::OnStop(line1));
            assert(stop1 == parse::OnStop(line2));
        }

        cerr << "TestParseStop - Success!"s << endl;
    }
}

void test::ParseStopWithDistance() {
    {
        {
            StopDistances stop_distance = {"Marushkino"s, { {"Rasskazovka"s, 9900},
                                                            {"Marushkino"s, 100} }};
            string line = "Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka, 100m to Marushkino"s;
            assert(stop_distance == parse::OnStopWithDistances(line));
        }

        {
            StopDistances stop_distance = {"Biryulyovo Zapadnoye"s, { {"Rossoshanskaya ulitsa"s, 7500},
                                                                      {"Biryusinka"s, 1800},
                                                                      {"Universam"s, 2400} }};
            string line = "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam"s;
            assert(stop_distance == parse::OnStopWithDistances(line));
        }

        {
            StopDistances stop_distance = {"Tolstopaltsevo"s, { {"Marushkino"s, 3900} }};
            string line = "Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino"s;
            assert(stop_distance == parse::OnStopWithDistances(line));
        }
        cerr << "TestParseStopWithDistance - Success!"s << endl;
    }
}