#pragma once

#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

namespace transport {

    class TransportCatalogue;
    struct Stop;
    struct StopDistances;
    enum class BusType;
    struct Bus;

    struct RawData {
        std::vector<std::string> stops;
        std::vector<std::string> buses;
    };

    enum class QyeryTypes {
        BUS,
        STOP
    };

    struct RawQuery {
        QyeryTypes type;
        std::string name;
    };

    namespace parse {
        Stop OnStop(std::string& line);
        StopDistances OnStopWithDistances(const std::string& line);
        Bus OnBus(std::string& line, const std::unordered_map<std::string_view, Stop*>& for_stop_ptrs);
    }

    namespace input {
        RawData Data(std::istream& input);
        std::vector<RawQuery> Query(std::istream& input);
    }


    void FillCatalogue(TransportCatalogue& catalogue, RawData& raw_data);

    namespace test {
        void ParseStop();
        void ParseStopWithDistance();
    }

}

