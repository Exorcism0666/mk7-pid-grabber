#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::swap_camera(Kart::Camera *_this)
    {
        if (g_menu->m_spectator_mode_entry->IsActivated())
        {
            if (g_pointers->get_race_info()->player_amount == 1)
                return;

            auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

            auto vehicle = _this->info_proxy->vehicle;

            if (data->set || !data->set && vehicle->is_master && !vehicle->is_net_recv)
            {
                if (data->pending)
                {
                    if (auto target = utilities::get_kart(data->target_id))
                    {
                        _this->info_proxy->vehicle = target;

                        data->pending = false;
                    }
                }   
            }
        }
    }
}