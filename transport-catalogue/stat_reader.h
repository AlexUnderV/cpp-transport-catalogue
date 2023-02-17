#pragma once

#include "transport_catalogue.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace transport {
    namespace output {
        namespace detail {
            void StatBus(Bus* bus, const std::string& bus_name, std::ostream& out);
            void StatStop(const std::string& stop_name,
                          const std::vector<Bus*>& buses,
                          TransportCatalogue& catalogue, std::ostream& out);
        }

        void Output(std::vector<RawQuery> query,
                    TransportCatalogue& catalogue, std::ostream& out);
    }
}



