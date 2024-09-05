#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    bool features::ignore_effect(Effect::KartEffect *_this)
    {
        if (g_menu->m_spectator_mode_entry->IsActivated())
        {
            if (g_pointers->get_race_info()->player_amount == 1)
               return false;

            return (_this->info_proxy->vehicle->is_master && !_this->info_proxy->vehicle->is_net_recv);
        }

        return false;
    }
}