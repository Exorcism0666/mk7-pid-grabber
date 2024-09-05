#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::change_target(Kart::Camera *_this)
    {
        if (g_menu->m_spectator_mode_entry->IsActivated())
        {
            if (g_pointers->get_race_info()->player_amount == 1)
                return;

            auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

            auto vehicle = _this->info_proxy->vehicle;

            if (!data->set && vehicle->is_master && !vehicle->is_net_recv)
            {
                if (!data->pending)
                {
                    utilities::get_next_player(data->target_id, false);

                    data->pending = true;
                }

                if (!data->set)
                    data->set = true;
            }

            if (data->set)
            {
                if (Controller::IsKeyPressed(DPadRight))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, false);

                        data->pending = true;
                    }
                }
                else if (Controller::IsKeyPressed(DPadLeft))
                {
                    if (!data->pending)
                    {
                        utilities::get_next_player(data->target_id, true);

                        data->pending = true;
                    }
                }
            }
        }
    }
}