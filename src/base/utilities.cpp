#include <base/utilities.hpp>

#include <base/pointers.hpp>
#include <base/logger.hpp>
#include <base/files.hpp>
#include <base/menu.hpp>

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace base
{
    bool utilities::check_process(std::string process_name)
    {
        std::string current_process{};

        Process::GetName(current_process);

        return (process_name == current_process);
    }

    std::string utilities::read_file(File file)
    {
        std::vector<char> buffer{};

        buffer.resize(file.GetSize());

        file.Read(buffer.data(), file.GetSize());

        return std::string(buffer.data());
    }
    
    void utilities::print_error(std::string error, bool abort)
    {
        if (abort)
        {
            auto file = g_logger.error("{}", error.c_str());

            error = Color::SkyBlue << "File Location:\n" << Color::DodgerBlue << std::format("sd:{}", file.GetFullName());
        }

        MessageBox(Color::Orange << "An error occurred", error, DialogType::DialogOk, ClearScreen::Both)();
        
        if (abort)
        {
            Sleep(Seconds(1));

            Process::ReturnToHomeMenu();
        }
    }

    void utilities::popup(std::string title, std::string text, bool update)
    {
        if (update)
            text += Color::Turquoise << "\n\nUpdate" << Color::White << ": " << Color::Silver << DATE;

        MessageBox(title, text, DialogType::DialogOk, ClearScreen::Both)();
    }

    std::string utilities::format_output(std::string name, std::string value, bool linebreak)
    {
        return Color::SkyBlue << (linebreak ? "\n" << name : name) << Color::White << ": " << Color::LimeGreen << value;
    }

    std::string utilities::format_friendcode(u64 friendcode)
    {
        return Utils::Format("%012llu", friendcode).insert(4, 1, '-').insert(9, 1, '-');
    }

    u64 utilities::pid_to_fc(u32 principal_id)
    {
        if (R_SUCCEEDED(frdInit()))
        {
            u64 friendcode{};
            
            bool res = R_SUCCEEDED(FRD_PrincipalIdToFriendCode(principal_id, &friendcode));
            
            frdExit();

            return (res ? friendcode : 0);
        }

        return {};
    }

    std::string utilities::parse_name(Net::NetworkPlayerData *network_player)
    {
        std::string name{};

        Process::ReadString((u32)network_player->name, name, (std::size(network_player->name) + 1), StringFormat::Utf16);
        
        return ((name.empty() || name == GUEST_NAME) ? DEFAULT_NAME : name);
    }

    std::string utilities::parse_name(System::OpponentData *opponent)
    {
        std::string name{};

        Process::ReadString((u32)opponent->data.name, name, (std::size(opponent->data.name) + 1), StringFormat::Utf16);
        
        return ((name.empty() || name == GUEST_NAME) ? DEFAULT_NAME : name);
    }

    Net::NetworkPlayerData * utilities::get_network_player_data(u8 player_id)
    {
        return g_pointers->get_network_player_data((*g_pointers->m_network_engine)->network_player_data_mgr, player_id);
    }

    u32 utilities::get_station_id(u8 player_id, bool use_handle)
    {
        auto list = (*g_pointers->m_network_engine)->station_buffer_mgr->racers;

        if (player_id >= std::size(list->entries))
            return {};
        
        if (auto station_info = list->entries[player_id].station_info)
            return (use_handle ? station_info->do_handle : station_info->station_id);

        return {};
    }

    nn::nex::Station * utilities::get_station(u32 station_id)
    {
        nn::nex::Station *station{};

        nn::nex::SelectionIteratorTemplate_Station iterator{};

        g_pointers->station_selection_iterator_template(&iterator);
        
        while (iterator.do_ref.do_handle)
        {
            if ((iterator.do_ref.station->station_id & 0x3FFFFF) == station_id)
            {
                station = iterator.do_ref.station;

                break;
            }
            
            g_pointers->iterator_over_DOs_advance_to_valid_item(&iterator, false);
        }

        g_pointers->iterator_over_DOs_destructor(&iterator);

        return station;
    }

    std::vector<nn::nex::Station *> utilities::get_station_list()
    {
        std::vector<nn::nex::Station *> list{};

        nn::nex::SelectionIteratorTemplate_Station iterator{};

        g_pointers->station_selection_iterator_template(&iterator);
        
        while (iterator.do_ref.do_handle)
        {
            list.push_back(iterator.do_ref.station);
            
            g_pointers->iterator_over_DOs_advance_to_valid_item(&iterator, false);
        }

        g_pointers->iterator_over_DOs_destructor(&iterator);

        return list;
    }
    
    nn::nex::Station * utilities::get_station_from_list(u32 station_id)
    {
        auto list = g_menu->station_list;

        if (station_id && !list.empty())
            for (auto station : list)
                if (station && station->station_id == station_id)
                    return station;
        
        return {};
    }

    std::vector<PlayerInfo> utilities::get_player_list()
    {
        std::vector<PlayerInfo> list{};

        for (size_t i = 0; i < get_player_amount(false); i++)
        {
            if (is_local_client(i, false))
                continue;

            auto network_player = get_network_player_data(i);
            
            std::string name = parse_name(network_player);

            bool loaded = (is_connected(i) && network_player->created);

            PlayerInfo player = { i, loaded, { name, network_player->principal_id }, network_player };

            if (is_duplicate(list, player))
            {
                player.loaded = false;
                player.info.name = "Player";
            }

            list.push_back(player);
        }

        return list;
    }

    std::vector<OpponentInfo> utilities::get_opponent_list()
    {
        std::vector<OpponentInfo> list{};

        if (auto opponent_list = *reinterpret_cast<System::OpponentList **>(0x6673C8))
            for (auto opponent : opponent_list->opponents)
                if (opponent.data.loaded)
                    list.push_back({ parse_name(&opponent), opponent.data.principal_id });

        return list;
    }

    u32 utilities::get_principal_id(nn::nex::Station *station)
    {
       if (station && station->station_url)
        {
            std::string str{};

            if (Process::ReadString(station->station_url, str, (station->url_length * sizeof(u32)), StringFormat::Utf16))
            {
                std::string target = "PID";

                size_t start = str.find(target + "=") + std::size(target + "=");
                size_t end = str.find(";", start);
                
                return stoi(str.substr(start, end - start));
            }
        }
        
        return {};
    }

    u32 utilities::get_principal_id(u8 player_id)
    {
        if (auto station_id = get_station_id(player_id, false))
        {
            if (auto station = get_station(station_id))
            {
                if (station->station_url)
                {
                    std::string str{};

                    if (Process::ReadString(station->station_url, str, (station->url_length * sizeof(u32)), StringFormat::Utf16))
                    {
                        std::string target = "PID";

                        size_t start = str.find(target + "=") + std::size(target + "=");
                        size_t end = str.find(";", start);
                        
                        return stoi(str.substr(start, end - start));
                    }
                }
            }
        }
        
        return {};
    }

    u32 utilities::get_my_principal_id()
    {
        if (R_SUCCEEDED(frdInit()))
        {
            FriendKey key;

            if (R_SUCCEEDED(FRD_GetMyFriendKey(&key)))
            {
                frdExit();

                return key.principalId;
            }
            
            frdExit();
        }

        return {};
    }

    u32 utilities::get_player_amount(bool exclude_local_client)
    {
        u32 amount = (*g_pointers->m_network_engine)->station_buffer_mgr->peer_amount;

        return (exclude_local_client ? (amount - 1): amount);
    }

    bool utilities::is_local_client(u32 id, bool is_station)
    {
        return (id == (is_station ? (*g_pointers->m_network_engine)->local_station_id : (*g_pointers->m_network_engine)->local_player_id));
    }

    bool utilities::is_duplicate(std::vector<PlayerInfo> list, PlayerInfo player)
    {
        return (std::find(list.begin(), list.end(), player) != list.end());
    }

    bool utilities::is_connected(u8 player_id)
    {
        return !g_pointers->is_disconnected((*g_pointers->m_network_engine)->station_buffer_mgr, player_id);
    }
    
    Kart::Vehicle * utilities::get_kart(u8 player_id)
    {
        Kart::Vehicle *vehicle;
        
        g_pointers->kart_info_proxy(vehicle, player_id);

        return vehicle;
    }

    bool utilities::is_spectating()
    {
        auto race_check = *reinterpret_cast<RaceCheck **>(0x667470);

        if (race_check->state == RaceCheckState::InRace)
            if (auto race_info = g_pointers->get_race_info())
                return (race_info->master_id == UINT16_MAX);

        return false;
    }

    bool utilities::is_in_race(bool allow_spectate)
    {
        auto race_check = *reinterpret_cast<RaceCheck **>(0x667470);

        if (race_check->state == RaceCheckState::InRace)
            if (auto race_info = g_pointers->get_race_info())
                return (allow_spectate ? true : !is_spectating());  

        return false;
    }

    void utilities::get_next_player(u8 &index, bool backwards, bool exclude_local_client)
	{
        if (auto race_info = g_pointers->get_race_info())
        {
            auto max_amount = (race_info->player_amount - 1);

            do
            {
                if (!backwards)
                {
                    index++;
                    
                    if (index > max_amount)
                        index = 0;
                }
                else
                {
                    index--;
                    
                    if (index < 0 || index > max_amount)
                        index = max_amount;
                }
            }
            while (exclude_local_client && !is_spectating() && index == race_info->master_id);
        }
    }

    bool utilities::is_master(Kart::Vehicle *vehicle, bool allow_spectate)
    {
        if (allow_spectate)
            return vehicle->is_master;

        return (vehicle->is_master && !vehicle->is_net_recv);
    }

    bool utilities::is_online()
    {
        if (auto network_engine = (*g_pointers->m_network_engine))
            return (network_engine->online_check_1 && network_engine->online_check_2 && !network_engine->online_check_3);

        return false;
    }

    u8 utilities::get_my_player_id()
    {
        u8 player_id = UINT8_MAX;

        auto network_engine = (*g_pointers->m_network_engine);
        auto race_info = g_pointers->get_race_info();

        if (utilities::is_online())
        {
            if (utilities::is_spectating())
                player_id = race_info->detail_id;
            else
                player_id = network_engine->local_player_id;
        }
        else
            player_id = race_info->master_id;

        return player_id;
    }
}