#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::change_target(Kart::Camera *_this)
    {
        if (!_this->available)
            return;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (g_menu->m_spectator_mode_entry->IsActivated() || data->active)
        {
            if (utilities::is_alone())
                return;

            if (!data->is_set && utilities::is_master(_this->info_proxy->vehicle, true))
            {
                if (!data->pending)
                {
                    utilities::get_next_player(data->target_id, false, !utilities::is_spectating());

                    data->pending = true;
                }

                if (!data->is_set)
                    data->is_set = true;
            }

            if (data->is_set)
            {
                if (Controller::IsKeyPressed(DPadRight))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, false, !utilities::is_spectating());
                        
                        data->pending = true;
                    }
                }
                else if (Controller::IsKeyPressed(DPadLeft))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, true, !utilities::is_spectating());
                        
                        data->pending = true;
                    }
                }
            }
        }
    }
}