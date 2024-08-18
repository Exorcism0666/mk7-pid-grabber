#include <base/features.hpp>

#include <base/settings.hpp>
#include <base/pointers.hpp>
#include <base/notifier.hpp>
#include <base/logger.hpp>
#include <base/files.hpp>

namespace base
{
    void features::dump_session()
    {
        auto &session_logger = g_settings.m_options.session_logger;

        if (session_logger.enabled)
        {
            auto const network_engine = (*g_pointers->m_network_engine);

            std::string session = "";

            session += std::format("MK7-PID-Grabber for Mario Kart 7 created by {}\nGithub: {}\nUpdate: {}", CREATOR, GITHUB, DATE);

            session += std::format("\n\nDate Time: {}\nSession ID: {:d}", g_logger.get_current_date_time_string(true), network_engine->session_net_z->room_id);
            
            session += std::format("\n\nPlayer Amount: {:d}\n\nYou were in Slot: {:d}\n", utilities::get_player_amount(false), (network_engine->local_player_id + 1));

            auto list = utilities::get_player_list();

            if (list.empty())
                utilities::print_error("Error: Empty Player List (Dump Session)", true);

            for (auto player : list)
            {
                auto slot = (player.id == 0 ? "1 (Host)" : std::to_string(player.id + 1));

                if (player.loaded)
                {
                    u32 station_id = utilities::get_station_id(player.id, true);

                    if (!station_id)
                        utilities::print_error(std::format("Error: Retrieving Station ID (Dump Session) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);

                    auto station = utilities::get_station_from_list(station_id);

                    if (!station)
                        utilities::print_error(std::format("Error: Retrieving Station (Dump Session) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);
                    
                    if (station->station_id != station_id)
                        utilities::print_error(std::format("Error: Matching Station ID (Dump Session) | Station ID: {:X} | Station ID From List: {:X} | Player ID: {:d} | Name: {}", station_id, station->station_id, player.id, player.info.name), true);

                    if (auto clean_pid = utilities::get_principal_id(station))
                    {
                        if (player.info.principal_id != clean_pid)
                            session += std::format("\nName: {} - Slot: {} - PID: {:d} (0x{:X}) - Spoofed PID: {:d} (0x{:X})", player.info.name, slot, clean_pid, clean_pid, player.info.principal_id, player.info.principal_id);
                        else
                            session += std::format("\nName: {} - Slot: {} - PID: {:d} (0x{:X})", player.info.name, slot, player.info.principal_id, player.info.principal_id);
                    }
                    else
                        utilities::print_error(std::format("Error: Retrieving Principal ID (Dump Session) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);
                }
                else
                    session += std::format("\nName: {} - Slot: {} - Disconnected (CPU)", player.info.name, slot);
            }

            g_files->m_session.Clear();

            g_logger.dump_session(session);

            if (session_logger.notify)
                g_notifier.send("{} got updated", g_files->m_session.GetName());
        }
    }
}