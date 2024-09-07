#include <base/features.hpp>

#include <base/menu.hpp>

namespace base
{
    void features::lag_elimination(Kart::NetData *_this)
    {
        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

        if (data->active)
            _this->kart_data.warp ^= true;
    };
};