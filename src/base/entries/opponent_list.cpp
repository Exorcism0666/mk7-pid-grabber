#include <base/entries.hpp>

#include <base/settings.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::opponent_list(MenuEntry *entry)
    {
        auto opponent_list = *reinterpret_cast<OpponentList **>(OPPONENT_LIST);
        
        if (!opponent_list)
            return;

        std::vector<OpponentInfo> list;

        for (size_t i = 0; i < std::size(opponent_list->opponents); i++)
        {
            auto player_data = &opponent_list->opponents[i];

            if (player_data->check)
                list.push_back({ utilities::parse_name(player_data), player_data->principal_id });
        }

        if (!list.empty())
        {
            std::vector<std::string> items;

            for (const OpponentInfo &i : list)
                items.push_back(i.name);
            
            auto const &pid_display = g_settings.m_options.pid_display;
            
            Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Opponent Amount", Utils::Format("%d", list.size()), false), items);
            keyboard.CanAbort(true);
            
            int option = keyboard.Open();
            
            if (option != UINT32_MAX)
            {
                auto player = list[option];

                std::string message_box = "";

                switch (pid_display.mode)
                {
                    case decltype(pid_display.mode)::Decimal:
                        message_box += utilities::format_output("Principal ID", std::format("{:d}", player.principal_id), false);
                    break;

                    case decltype(pid_display.mode)::Hexadecimal:
                        message_box += utilities::format_output("Principal ID", std::format("0x{:X}", player.principal_id), false);
                    break;

                    case decltype(pid_display.mode)::Both:
                        message_box += utilities::format_output("Principal ID (DEC)", std::format("{:d}", player.principal_id), false);
                        message_box += utilities::format_output("Principal ID (HEX)", std::format("0x{:X}", player.principal_id), true);
                    break;
                }
                
                message_box += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(player.principal_id)), true);

                utilities::pop_up(Color::DodgerBlue << player.name, message_box, true);
            }
        }
    }
}