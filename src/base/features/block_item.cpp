#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    bool features::block_item(u8 player_id)
    {
        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (g_menu->m_spectator_mode_entry->IsActivated() || data->active)
        {
            if (utilities::is_alone())
                return false;

            if (auto vehicle = utilities::get_kart(player_id))
                return utilities::is_master(vehicle, false);
        }

        return false;
    }
}