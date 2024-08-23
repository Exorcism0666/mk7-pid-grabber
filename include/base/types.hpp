#pragma once

#include <Unicode.h>
#include <plgldr.h>
#include <types.h>
#include <3ds.h>

#include <magic_enum/magic_enum.hpp>

#include <string>
#include <vector>
#include <format>
#include <map>
#include <set>

#define DEFAULT_NAME "Player"
#define GUEST_NAME "no name"

namespace nn::nex
{
    struct StationInfo
    {
        u32 magic;
        u32 unkn0;
        u32 station_id;
        u32 padded_station_id; // 0x00C0XXXX padded, used as the station's station id
        u32 unkn1;
    };
    static_assert(sizeof(StationInfo) == 0x14);

    struct StationListEntry
    {
        StationInfo *station_info;
        u32 player_id;
        u32 index;
    };
    static_assert(sizeof(StationListEntry) == 0xC);

    struct StationList
    {
        StationListEntry entries[0x11];
    };

    struct Station
    {
        u8 gap0[0x58];
        u32 station_id;
        u8 gap1[0x30];
        u32 station_url;
    };
    static_assert(sizeof(Station) == 0x90);

    struct Selection
    {
        u8 gap0[0x21];
    };
    static_assert(sizeof(Selection) == 0x21);

    struct DOSelections
    {
        void *vmt;
        Selection selections[3];
    };
    static_assert(sizeof(DOSelections) == 0x68);

    struct DOFilter
    {
        u8 gap0[4];
        u16 count;
    };
    static_assert(sizeof(DOFilter) == 6);

    struct DORef
    {
        void *vmt;
        Station *station;
        void *do_handle;
        bool is_hard;
        DOFilter *filter;
        u8 gap0[0xD];
    };
    static_assert(sizeof(DORef) == 0x24);

    struct IteratorOverDOs
    {
        void *vmt;
        DOSelections *do_selections;
        DORef do_ref;
    };
    static_assert(sizeof(IteratorOverDOs) == 0x2C);

    struct SelectionIteratorTemplate_Station : IteratorOverDOs
    {
    };
}

namespace Net
{
    struct SessionNetZ
    {
        u8 gap0[0x44];
        u32 room_id;
    };
    static_assert(sizeof(SessionNetZ) == 0x48);

    struct NetworkPlayerData
    {
        u8 gap0[0x30];
        u32 principal_id;
        u8 gap1[0x22];
        u16 name[0x14];
        u16 null_terminator;
        u8 gap2[0x20];
        bool check;
        u8 gap3[3];
        bool loaded;
    };
    static_assert(sizeof(NetworkPlayerData) == 0xA8);

    struct NetworkPlayerDataManager
    {
        NetworkPlayerData players[8];
    };
    static_assert(sizeof(NetworkPlayerDataManager) == 0x540);

    struct StationBufferManager
    {
        u8 gap0[0x80];
        nn::nex::StationList *racers;
        u8 gap1[0x4C];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD4);

    struct NetworkEngine
    {
        u8 gap0[0x13C];
        SessionNetZ *session_net_z;
        u8 gap1[0x11C];
        StationBufferManager *station_buffer_mgr;
        u8 gap2[4];
        u32 local_station_id;
        u32 local_player_id;
        u8 gap3[0x4C];
        NetworkPlayerDataManager *network_player_data_mgr;
    };
    static_assert(sizeof(NetworkEngine) == 0x2BC);
}

namespace RaceSys
{
    struct CRaceInfo
    {
        u8 gap0[0x184];
        u16 master_id;
    };
    static_assert(sizeof(CRaceInfo) == 0x186);
}

namespace Kart
{
    struct Vehicle
    {
        u8 gap0[0x78];
        void *director;
        u8 gap1[8];
        u16 player_id;
        u8 gap2[0x12];
        bool is_master;
        u8 gap3;
        bool is_ai;
        u8 gap4[3];
        bool is_net_recv;
    };
    static_assert(sizeof(Vehicle) == 0xA0);
}

struct OpponentList
{
    u8 gap0[0x9F0];
    Net::NetworkPlayerData opponents[100];
};

struct OpponentInfo
{
    std::string name;
    u32 principal_id;
};

struct PlayerInfo
{
    size_t id;
    bool loaded;
    OpponentInfo info;
    Net::NetworkPlayerData *instance;

    constexpr bool operator==(PlayerInfo const &player) const
    {
        return (player.info.name == info.name && player.info.principal_id == info.principal_id);
    }
};