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
    struct Station
    {
        u8 gap0[0x58];
        u32 station_id;
        u8 gap1[0x2C];
        u32 url_length;
        u32 station_url;
    };

    struct Selection // credits to Anto726
    {
        u8 gap0[0x21];
    };
    static_assert(sizeof(Selection) == 0x21);

    struct DOSelections // credits to Anto726
    {
        void *vmt;
        Selection selections[3];
    };
    static_assert(sizeof(DOSelections) == 0x68);

    struct DOFilter // credits to Anto726
    {
        u8 gap0[4];
        u16 count;
    };
    static_assert(sizeof(DOFilter) == 6);

    struct DORef // credits to Anto726
    {
        void *vmt;
        Station *station;
        void *do_handle;
        bool is_hard;
        DOFilter *filter;
        u8 gap0[0xD];
    };
    static_assert(sizeof(DORef) == 0x24);

    struct IteratorOverDOs // credits to Anto726
    {
        void *vmt;
        DOSelections *do_selections;
        DORef do_ref;
    };
    static_assert(sizeof(IteratorOverDOs) == 0x2C);

    struct SelectionIteratorTemplate_Station : IteratorOverDOs // credits to Anto726
    {
    };
}

namespace System
{
    struct PlayerData
    {
        u8 gap0[0x30];
        u32 principal_id;
        u8 gap1[0x22];
        u16 name[0x14];
        u16 null_terminator;
        u8 gap2[0x1C];
        bool loaded;
    };
    static_assert(sizeof(PlayerData) == 0xA0);

    struct OpponentData
    {
        u8 gap0[8];
        PlayerData data;
    };
    static_assert(sizeof(OpponentData) == 0xA8);

    struct OpponentList
    {
        u8 gap0[0x2494];
        OpponentData opponents[100];
    };
}

namespace Item
{
    enum class ItemSlot : u8
    {
        Banana = 0,
        GreenShell = 1,
        RedShell = 2,
        Mushroom = 3,
        BobOmb = 4,
        Blooper = 5,
        BlueShell = 6,
        TripleMushroom = 7,
        Star = 8,
        BulletBill = 9,
        Lightning = 10,
        GoldenMushroom = 11,
        FireFlower = 12,
        TanookiTail = 13,
        LuckySeven = 14,
        FakeItemBox = 15,
        MegaMushroom = 16,
        TripleBanana = 17,
        TripleGreenShell = 18,
        TripleRedShell = 19
    };

    enum class ItemType : u8
    {
        GreenShell = 0,
        RedShell = 1,
        Banana = 2,
        Mushroom = 3,
        Star = 4,
        BlueShell = 5,
        Lightning = 6,
        FakeItemBox = 7,
        GoldenMushroom = 8,
        BobOmb = 9,
        Blooper = 10,
        MegaMushroom = 11,
        BulletBill = 12,
        FireFlower = 13,
        TanookiTail = 14,
        LuckySeven = 15
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

    struct NetworkPlayerData : System::PlayerData
    {
        u8 gap0[4];
        bool created;
    };
    static_assert(sizeof(NetworkPlayerData) == 0xA8);

    struct NetworkPlayerDataManager
    {
        NetworkPlayerData players[8];
    };
    static_assert(sizeof(NetworkPlayerDataManager) == 0x540);

    struct StationBufferManager
    {
        struct StationInfo // credits to Anto726
        {
            u32 status;
            bool is_ai;
            u32 station_id;
            u32 do_handle;
            u32 player_id;
        };
        static_assert(sizeof(StationInfo) == 0x14);

        struct ConnectorInfo // credits to Anto726
        {
            StationInfo *station_info;
            u32 player_id;
            u32 aid;
        };
        static_assert(sizeof(ConnectorInfo) == 0xC);

        struct StationList
        {
            ConnectorInfo entries[0x11];
        };

        u8 gap0[0x80];
        StationList *racers;
        u8 gap1[0x4C];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD4);

    struct NetworkEngine
    {
        u8 gap0[0x13C];
        SessionNetZ *session_net_z;
        u8 gap1[0xC];
        u32 online_check_1;
        u8 gap2[0x10C];
        StationBufferManager *station_buffer_mgr;
        bool online_check_2;
        u32 local_station_id;
        u32 local_player_id;
        u8 gap3[0x4C];
        NetworkPlayerDataManager *network_player_data_mgr;
        u8 gap4[0x247];
        bool online_check_3;
    };
    static_assert(sizeof(NetworkEngine) == 0x504);

    struct NetworkItemEventDataMgr // credits to Anto726
    {
        enum class EventType : u8
        {
            SelfMove = 2
        };

        struct SlotData
        {
            u8 gap0[4];
            Item::ItemType item_type;
            EventType event_type;
            u8 gap1[2];
            u8 player_id;
            u8 gap2;
            bool is_dropped;
        };
    };
}

namespace RaceSys
{
    struct CRaceInfo
    {
        u8 gap0[0x180];
        u32 player_amount;
        u16 master_id;
        u16 detail_id;
    };
}

namespace Kart
{
    struct Director
    {
        u8 gap0[0x30];
        u16 camera_target_id;
    };

    struct Camera
    {
        u8 gap0[0xD4];
        bool is_master;
        struct InfoProxy *info_proxy;
        u8 gap1[0x180];
        float evade;
    };

    struct InfoProxy
    {
        struct Vehicle *vehicle;
    };

    struct Vehicle
    {
        u8 gap0[0x78];
        Director *director;
        u8 gap1[4];
        Camera *camera;
        u16 player_id;
        u8 gap2[0x12];
        bool is_master;
        bool is_cpu;
        bool is_ai;
        u8 gap4[3];
        bool is_net_recv;
        u8 gap5[7];
        bool is_goal;
    };

    struct VehicleReact : Vehicle
    {
    };

    struct KartData // credits to Anto726
    {
        u32 _0x1 : 1;
        u32 _0x2 : 1;
        u32 _0x4 : 1;
        u32 _0x8 : 1;
        u32 _0x10 : 1;
        u32 _0x20 : 1;
        u32 _0x40 : 1;
        u32 _0x80 : 1;
        u32 _0x100 : 1;
        u32 _0x200 : 1;
        u32 _0x400 : 1;
        u32 _0x800 : 1;
        u32 _0x1000 : 1;
        u32 _0x2000 : 1;
        u32 _0x4000 : 1;
        u32 _0x8000 : 1;
        u32 _0x10000 : 1;
        u32 warp : 1;
    };

    struct NetData
    {
        u8 gap0[4];
        KartData kart_data;
    };
}

namespace Effect
{
    struct KartEffect // credits to Anto726
    {
        u8 gap[0x1FC];
        Kart::InfoProxy *info_proxy;
    };
}

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

enum class RaceCheckState : u8
{
    NotInRace = 7,
    InRace = 8
};

struct RaceCheck
{
    u8 gap0[0x18];
    RaceCheckState state;
};

struct CameraMatrix
{
    u8 gap0[0xC];
    float orientation;
};