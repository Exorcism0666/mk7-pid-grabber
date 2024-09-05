#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    bool features::block_item(u8 player_id)
    {
        if (g_menu->m_spectator_mode_entry->IsActivated())
        {
            if (g_pointers->get_race_info()->player_amount == 1)
                return false;

            if (auto vehicle = utilities::get_kart(player_id))
                return (vehicle->is_master && !vehicle->is_net_recv);
        }

        return false;
    }
}