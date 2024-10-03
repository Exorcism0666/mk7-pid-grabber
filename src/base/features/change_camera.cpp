#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::change_camera(Kart::Camera *_this)
    {
        if (_this->is_master && g_menu->m_backwards_camera_entry->IsActivated());
            (*g_pointers->m_camera_matrix)->orientation = Controller::IsKeyDown(X) ? -50.f : +50.f;
    }
}