#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::change_target(Kart::Camera *_this)
    {
        if (!_this->is_master || !utilities::is_online())
            return;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (data->active)
        {
            if (data->target_id == UINT8_MAX && utilities::is_master(_this->info_proxy->vehicle, true))
            {
                if (!data->pending)
                {
                    data->target_id = utilities::get_my_player_id();

                    data->pending = true;
                }
            }
            else if (data->target_id != UINT8_MAX)
            {
                if (Controller::IsKeyPressed(DPadUp))
                {
                    if (!data->pending)
                    {
                        data->target_id = utilities::get_my_player_id();
                        
                        data->pending = true;
                    }
                }
                else if (Controller::IsKeyPressed(DPadRight))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, false, false);
                        
                        data->pending = true;
                    }
                }
                else if (Controller::IsKeyPressed(DPadLeft))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, true, false);
                        
                        data->pending = true;
                    }
                }
            }
        }
    }
}