#include <base/features.hpp>

#include <base/menu.hpp>

namespace base
{
    void features::swap_camera(Kart::Camera *_this)
    {
        if (!_this->is_master || !utilities::is_online())
            return;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (data->active && data->pending && data->target_id != UINT8_MAX)
        {
            if (_this->info_proxy->vehicle->player_id != data->target_id)
            {
                if (auto target = utilities::get_kart(data->target_id))
                {
                    _this->info_proxy->vehicle->director->camera_target_id = data->target_id;

                    _this->info_proxy->vehicle = target;
                }
            }
            
            data->pending = false;
        }
    }
}