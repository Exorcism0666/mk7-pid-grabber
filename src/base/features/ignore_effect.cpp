#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    bool features::ignore_effect(Effect::KartEffect *_this)
    {
        if (!utilities::is_online())
            return false;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (data->active)
            return utilities::is_master(_this->info_proxy->vehicle, true);

        return false;
    }
}