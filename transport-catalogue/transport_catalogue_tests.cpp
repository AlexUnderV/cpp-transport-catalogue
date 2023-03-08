/*#include "transport_catalogue.h"

#include <cassert>

using namespace std;
using namespace transport;

void test::CalculateDistance() {
    {
        {
            TransportCatalogue catalogue;

            Stop stop1 = {"Tolstopaltsevo"s, {55.611087, 37.20829}};
            Stop stop2 = {"Marushkino"s, {55.595884, 37.209755}};

            StopDistances dists1 = {"Tolstopaltsevo"s, {{"Marushkino"s, 1000}}};
            StopDistances dists2 = {"Marushkino"s, {{"Tolstopaltsevo"s, 1200}}};

            catalogue.AddStop(stop1);
            catalogue.AddStop(stop2);

            catalogue.AddDistance(dists1);
            catalogue.AddDistance(dists2);

            string bus1 = "Bus 256: Tolstopaltsevo - Marushkino"s;
            const auto stops_in_catalogue_ptrs = catalogue.GetStopPtrs();
            auto b = parse::OnBus(bus1, stops_in_catalogue_ptrs);
            catalogue.AddBus(b);

            assert(catalogue.CalculateRouteForward("256"s) == 1000);
            assert(catalogue.CalculateRouteBackward("256"s) == 1200);
            assert(catalogue.CalculateRouteActual("256"s) == 2200);
        }

        {
            TransportCatalogue catalogue;

            Stop stop1 = {"Tolstopaltsevo"s, {55.611087, 37.20829}};
            Stop stop2 = {"Marushkino"s, {55.595884, 37.209755}};
            Stop stop3 = {"Rasskazovka"s, {55.632761, 37.333324}};

            StopDistances dists1 = {"Tolstopaltsevo"s, {{"Marushkino"s, 3900}}};
            StopDistances dists2 = {"Marushkino"s, {{"Rasskazovka"s, 9900},
                                                    {"Marushkino"s, 100}}};
            StopDistances dists3 = {"Rasskazovka"s, {{"Marushkino"s, 9500}}};

            catalogue.AddStop(stop1);
            catalogue.AddStop(stop2);
            catalogue.AddStop(stop3);

            catalogue.AddDistance(dists1);
            catalogue.AddDistance(dists2);
            catalogue.AddDistance(dists3);

            string bus1 = "Bus 256: Tolstopaltsevo - Marushkino - Marushkino - Rasskazovka"s;
            const auto stops_in_catalogue_ptrs = catalogue.GetStopPtrs();
            auto b = parse::OnBus(bus1, stops_in_catalogue_ptrs);
            catalogue.AddBus(b);

            assert(catalogue.CalculateRouteForward("256"s) == 13900);
            assert(catalogue.CalculateRouteBackward("256"s) == 13500);
            assert(catalogue.CalculateRouteActual("256"s) == 27400);
        }

        {
            TransportCatalogue catalogue;

            Stop stop1 = {"Biryulyovo Zapadnoye"s, {55.574371, 37.6517}};
            Stop stop2 = {"Biryusinka"s, {55.581065, 37.64839}};
            Stop stop3 = {"Universam"s, {55.587655, 37.645687}};
            Stop stop4 = {"Biryulyovo Tovarnaya"s, {55.592028, 37.653656}};
            Stop stop5 = {"Biryulyovo Passazhirskaya"s, {55.580999, 37.659164}};

            StopDistances dists1 = {"Biryulyovo Zapadnoye"s, { {"Biryusinka"s, 1800}, {"Universam"s, 2400} }};
            StopDistances dists2 = {"Biryusinka"s, { {"Universam"s, 750} }};
            StopDistances dists3 = {"Universam"s, { {"Biryulyovo Tovarnaya"s, 900} }};
            StopDistances dists4 = {"Biryulyovo Tovarnaya"s, { {"Biryulyovo Passazhirskaya"s, 1300} }};
            StopDistances dists5 = {"Biryulyovo Passazhirskaya"s, { {"Biryulyovo Zapadnoye"s, 1200} }};

            catalogue.AddStop(stop1);
            catalogue.AddStop(stop2);
            catalogue.AddStop(stop3);
            catalogue.AddStop(stop4);
            catalogue.AddStop(stop5);

            catalogue.AddDistance(dists1);
            catalogue.AddDistance(dists2);
            catalogue.AddDistance(dists3);
            catalogue.AddDistance(dists4);
            catalogue.AddDistance(dists5);


            string bus1 = "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye"s;
            const auto stops_in_catalogue_ptrs = catalogue.GetStopPtrs();
            auto b = parse::OnBus(bus1, stops_in_catalogue_ptrs);
            catalogue.AddBus(b);

            // 5950   4371.02

            assert(catalogue.CalculateRouteForward("256"s) == 5950);
            assert(catalogue.CalculateRouteBackward("256"s) == 5950);
            assert(catalogue.CalculateRouteActual("256"s) == 5950);

            assert((catalogue.CalculateRouteGeographic("256"s) - 4371.02) < EPSILON);
        }
    }
    cerr << "TestCalculateDistance - Success!"s << endl;*/
}
