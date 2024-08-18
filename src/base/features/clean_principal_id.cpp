#include <base/features.hpp>

namespace base
{
    void features::clean_principal_id()
    {
        auto list = utilities::get_player_list();

        if (list.empty())
            utilities::print_error("Error: Empty Player list (Clean PID)", true);
        
        for (auto player : list)
        {
            if (player.loaded)
            {
                u32 station_id = utilities::get_station_id(player.id, true);

                if (!station_id)
                    utilities::print_error(std::format("Error: Fetching Station ID (Clean PID) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);

                auto station = utilities::get_station_from_list(station_id);

                if (!station)
                    utilities::print_error(std::format("Error: Fetching Station (Clean PID) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);

                if (station->station_id != station_id)
                    utilities::print_error(std::format("Error: Matching Station ID (Clean PID)) | Station ID: {:X} Station ID From List: {:X} | Player ID: {:d} | Name: {}", station_id, station->station_id, player.id, player.info.name), true);
                
                if (auto clean_pid = utilities::get_principal_id(station))
                {
                    if (player.info.principal_id != clean_pid)
                        player.instance->principal_id = clean_pid;
                }
                else
                    utilities::print_error(std::format("Error: Retrieving Principal ID (Clean PID) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);
            }
        }
    }
}