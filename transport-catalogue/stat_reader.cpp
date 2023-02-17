#include "stat_reader.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

void transport::output::detail::StatBus(BusInfo bus_info) {
    cout << "Bus "s;
    if (bus_info.stops == 0) {
        cout << bus_info.name << ": "s << "not found"s << endl;
    } else {
        cout << bus_info.name << ": "s
             << bus_info.stops << " stops on route, "s
             << bus_info.unique_stops << " unique stops, "s
             << bus_info.route_actual << " route length, "s
             << bus_info.curvature << " curvature"s << endl;
    }
}


void transport::output::detail::StatStop(const std::string& stop_name, const vector<Bus*>& buses, TransportCatalogue& catalogue) {
    cout << "Stop "s << stop_name << ": "s;

    if (!catalogue.FindStop(stop_name)) {
        cout << "not found"s << endl;
        return;
    }

    if (buses.empty()) {
        cout << "no buses"s << endl;
        return;
    }

    cout << "buses "s;


    for (const auto& bus : buses) {
        cout << (bus)->name << " "s;
    }
    cout << endl;

}


void transport::output::Output(std::vector<Query> query, TransportCatalogue& catalogue) {
    for (const auto& q : query) {
        if (q.type == QyeryTypes::BUS) {
            output::detail::StatBus(catalogue.GetBusInfo(q.name));
        } else if (q.type == QyeryTypes::STOP) {
            output::detail::StatStop(q.name, catalogue.GetStopInfo(q.name), catalogue);
        }

    }
}