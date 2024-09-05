#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::change_to_ai(Kart::Vehicle *_this)
    {
        if (g_menu->m_spectator_mode_entry->IsActivated())
        {
            if (g_pointers->get_race_info()->player_amount == 1)
                return;

            if (_this->is_master && !_this->is_net_recv && !_this->is_ai)
                _this->is_goal = true;
        }
    }
}