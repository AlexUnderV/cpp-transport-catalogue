#pragma once

#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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

    struct Query {
        QyeryTypes type;
        std::string name;
    };

    namespace parse {
        Stop OnStop(std::string& line);
        StopDistances OnStopWithDistances(std::string& line);
        Bus OnBus(std::string& line, const std::unordered_map<std::string_view, Stop*>& for_stop_ptrs);
    }

    namespace input {
        RawData DataFromCommandLine();
        std::vector<Query> QueryFromCommandLine();

        RawData DataFromFile(std::string file_name);
        std::vector<Query> QueryFromFile(std::string file_name);
    }


    void FillCatalogue(TransportCatalogue& catalogue, RawData& raw_data);

    namespace test {
        void ParseStop();
        void ParseStopWithDistance();
    }

}

