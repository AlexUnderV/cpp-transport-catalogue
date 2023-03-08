/*#include "stat_reader.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

void transport::output::detail::StatBus(const Bus* bus, const string& bus_name, ostream& out) {

    out << "Bus "s;
    if (bus == nullptr) {
        out << bus_name << ": "s << "not found"s << endl;
    } else {
        out << bus->name << ": "s
             << bus->info.stops_count << " stops on route, "s
             << bus->info.unique_stops << " unique stops, "s
             << bus->info.route_actual << " route length, "s
             << bus->info.curvature << " curvature"s << endl;
    }
}


void transport::output::detail::StatStop(const std::string& stop_name,
                                         const vector<Bus*>& buses,
                                         TransportCatalogue& catalogue, ostream& out) {
    out << "Stop "s << stop_name << ": "s;

    if (!catalogue.FindStop(stop_name)) {
        out << "not found"s << endl;
        return;
    }

    if (buses.empty()) {
        out << "no buses"s << endl;
        return;
    }

    out << "buses "s;


    for (const auto& bus : buses) {
        out << (bus)->name << " "s;
    }
    out << endl;

}


void transport::output::Output(const std::vector<RawQuery>& query, TransportCatalogue& catalogue, ostream& out) {
    for (const auto& q : query) {
        if (q.type == QyeryTypes::BUS) {
            output::detail::StatBus(catalogue.GetBusInfo(q.name), q.name, out);
        } else if (q.type == QyeryTypes::STOP) {
            output::detail::StatStop(q.name, catalogue.GetStopInfo(q.name), catalogue, out);
        }

    }
}*/