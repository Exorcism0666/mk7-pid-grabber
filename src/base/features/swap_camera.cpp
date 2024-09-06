#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::swap_camera(Kart::Camera *_this)
    {
        if (!_this->available)
            return;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (g_menu->m_spectator_mode_entry->IsActivated() || data->active)
        {
            if (utilities::is_alone())
                return;

            if (data->is_set && data->pending)
            {
                if (_this->info_proxy->vehicle->player_id != data->target_id)
                {
                    if (auto target = utilities::get_kart(data->target_id))
                    {
                        _this->info_proxy->vehicle->director->camera_target_id = data->target_id;

                        _this->info_proxy->vehicle = target;

                        if (utilities::is_spectating())
                            if (auto race_info = g_pointers->get_race_info())
                                race_info->detail_id = data->target_id;
                    }
                }
                
                data->pending = false;
            }
        }
    }
}