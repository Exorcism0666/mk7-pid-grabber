#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    bool features::ignore_vehicle(Kart::Vehicle *_this)
    {
        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (g_menu->m_spectator_mode_entry->IsActivated() || data->active)
        {
            if (utilities::is_alone())
               return false;

            return utilities::is_master(_this, true);
        }

        return false;
    }
}