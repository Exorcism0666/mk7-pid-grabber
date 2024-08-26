#pragma once

#include <base/types.hpp>

#include <CTRPluginFramework.hpp>

namespace base
{
    class utilities
    {
    public:
        static bool check_process(std::string);
        static std::string read_file(CTRPluginFramework::File);
        static void print_error(std::string, bool);
        static void pop_up(std::string, std::string, bool);
        static std::string format_output(std::string, std::string, bool);
        static std::string format_friendcode(u64);
        static u64 pid_to_fc(u32);
        static std::string parse_name(Net::NetworkPlayerData *);
        static std::string parse_name(System::OpponentData *);
        static Net::NetworkPlayerData * get_network_player_data(u8);
        static u32 get_station_id(u8, bool);
        static nn::nex::Station * get_station(u32);
        static std::vector<nn::nex::Station *> get_station_list();
        static nn::nex::Station * get_station_from_list(u32);
        static std::vector<OpponentInfo> get_opponent_list();
        static std::vector<PlayerInfo> get_player_list();
        static u32 get_principal_id(nn::nex::Station *);
        static u32 get_principal_id(u8);
        static u32 get_my_principal_id();
        static u32 get_player_amount(bool);
        static bool is_local_client(u32, bool);
        static bool is_duplicate(std::vector<PlayerInfo>, PlayerInfo);
        static bool is_connected(u8);
    };
}