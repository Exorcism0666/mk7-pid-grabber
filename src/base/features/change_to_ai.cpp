#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::change_to_ai(Kart::Vehicle *_this)
    {
        if (g_menu->m_force_cpu_mode_entry->IsActivated())
            if (_this->is_master && !_this->is_net_recv && !_this->is_ai)
                if (auto race_info = g_pointers->get_race_info())
                    if (race_info->master_id == _this->player_id)
                        g_pointers->change_to_ai(_this->director, _this->player_id, true);
    }
}