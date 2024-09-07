#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::change_to_ai(Kart::Vehicle *_this)
    {
        if (!utilities::is_online())
            return;

        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (data->active)
            if (utilities::is_master(_this, false) && !_this->is_ai)
                _this->is_goal = true;
    }
}