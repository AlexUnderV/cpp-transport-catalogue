#pragma once

#include "transport_catalogue.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace transport {
    namespace output {
        namespace detail {
            void StatBus(BusInfo bus_info);
            void StatStop(const std::string& stop_name, const std::vector<Bus*>& buses, TransportCatalogue& catalogue);
        }

        void Output(std::vector<Query> query, TransportCatalogue& catalogue);
    }
}



