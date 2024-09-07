#include <base/features.hpp>

#include <base/pointers.hpp>

namespace base
{
    bool features::check_item_event(Net::NetworkItemEventDataMgr::SlotData *data)
    {
        auto race_info = g_pointers->get_race_info();

        if (data->player_id >= race_info->player_amount)
            return true;
        
        if (data->event_type == Net::NetworkItemEventDataMgr::EventType::SelfMove)
            if (data->item_type == Item::ItemType::Star)
                return !data->is_dropped;

        return false;
    }
}