#include <base/entries.hpp>

#include <base/settings.hpp>
#include <base/pointers.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::game_session(MenuEntry *entry)
    {
        if ((*g_pointers->m_network_engine)->local_player_id != UINT32_MAX && utilities::get_player_amount(true) != 0)
        {
            auto list = utilities::get_player_list();

            if (list.empty())
                utilities::print_error(std::format("Error: Empty Player List (Game Session)"), true);
            
            std::vector<std::string> items;

            for (const PlayerInfo &i : list)
                items.push_back(i.info.name);
            
            auto const &pid_display = g_settings.m_options.pid_display;
            
            std::string keyboard_message = "";

            keyboard_message += Color::Turquoise << "Select a player\n\n";
            keyboard_message += utilities::format_output("Session ID", std::format("{:d}", (*g_pointers->m_network_engine)->session_net_z->room_id), false);
            keyboard_message += utilities::format_output("Player Amount", std::format("{:d}", utilities::get_player_amount(false)), true);
            keyboard_message += utilities::format_output("Room Host", list.at(0).info.name, true);

            auto player_id = (*g_pointers->m_network_engine)->local_player_id;
            auto client_data = utilities::get_network_player_data(player_id);
            auto principal_id = utilities::get_my_principal_id();

            keyboard_message += Color::Cyan << "\n\n— Your Details —";
            keyboard_message += utilities::format_output("Player", std::format("{} (Slot {:d})", utilities::parse_name(client_data), (player_id + 1)), true);
            
            switch (pid_display.mode)
            {
                case decltype(pid_display.mode)::Decimal:
                    keyboard_message += utilities::format_output("Principal ID", std::format("{:d}", principal_id), true);
                break;

                case decltype(pid_display.mode)::Hexadecimal:
                    keyboard_message += utilities::format_output("Principal ID", std::format("0x{:X}", principal_id), true);
                break;

                case decltype(pid_display.mode)::Both:
                    keyboard_message += utilities::format_output("Principal ID (DEC)", std::format("{:d}", principal_id), true);
                    keyboard_message += utilities::format_output("Principal ID (HEX)", std::format("0x{:X}", principal_id), true);
                break;
            }
            
            keyboard_message += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(principal_id)), true);

            Keyboard keyboard(keyboard_message, items);
            keyboard.CanAbort(true);
            
            int option = keyboard.Open();
            
            if (option != UINT32_MAX)
            {
                auto player = list[option];

                if (player.loaded)
                {
                    u32 station_id = utilities::get_station_id(player.id, true);

                    if (!station_id)
                        utilities::print_error(std::format("Error: Fetching Station ID (Game Session) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);

                    u32 clean_pid{};

                    if (auto station = utilities::get_station_from_list(station_id))
                    {
                        if (station->station_id != station_id)
                            utilities::print_error(std::format("Error: Matching Station ID (Game Session) | Station ID: {:X} | Station ID From List: {:X} | Player ID: {:d} | Name: {}", station_id, station->station_id, player.id, player.info.name), true);

                        clean_pid = utilities::get_principal_id(station);
                    }
                    else
                        clean_pid = utilities::get_principal_id(player.id);

                    if (clean_pid)
                    {
                        std::string message_box = "";

                        u32 principal_id = player.info.principal_id;

                        if (clean_pid != principal_id)
                        {
                            switch (pid_display.mode)
                            {
                                case decltype(pid_display.mode)::Decimal:
                                    message_box += utilities::format_output("Spoofed PID", std::format("{:d}", principal_id), false) + "\n\n";
                                break;

                                case decltype(pid_display.mode)::Hexadecimal:
                                    message_box += utilities::format_output("Spoofed PID", std::format("0x{:X}", principal_id), false) + "\n\n";
                                break;

                                case decltype(pid_display.mode)::Both:
                                    message_box += utilities::format_output("Spoofed PID (DEC)", std::format("{:d}", principal_id), false);
                                    message_box += utilities::format_output("Spoofed PID (HEX)", std::format("0x{:X}", principal_id), true) + "\n\n";
                                break;
                            }
                            
                            principal_id = clean_pid;
                        }
                        
                        switch (pid_display.mode)
                        {
                            case decltype(pid_display.mode)::Decimal:
                                message_box += utilities::format_output("Principal ID", std::format("{:d}", principal_id), true);
                            break;

                            case decltype(pid_display.mode)::Hexadecimal:
                                message_box += utilities::format_output("Principal ID", std::format("0x{:X}", principal_id), true);
                            break;

                            case decltype(pid_display.mode)::Both:
                                message_box += utilities::format_output("Principal ID (DEC)", std::format("{:d}", principal_id), true);
                                message_box += utilities::format_output("Principal ID (HEX)", std::format("0x{:X}", principal_id), true);
                            break;
                        }
                        
                        message_box += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(principal_id)), true);
                        
                        utilities::pop_up(Color::DodgerBlue << player.info.name, message_box, true);
                    }
                    else
                        utilities::print_error(std::format("Error: Retrieving Principal ID (Game Session) | Station ID: {:X} | Player ID: {:d} | Name: {}", station_id, player.id, player.info.name), true);
                }
                else
                    utilities::print_error(Color::DodgerBlue << player.info.name << Color::White << " is unavailable", false);
            }
        }
        else
            utilities::print_error(Color::White << "Make sure you're online & in a lobby", false);
    }
}