#include <base/entries.hpp>

#include <base/pointers.hpp>
#include <base/settings.hpp>
#include <base/patches.hpp>

namespace base
{
    void entries::backwards_camera(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (!g_settings.m_options.backwards_camera)
                g_settings.m_options.backwards_camera = true;

            g_patches->m_disable_item_on_x.enable();
            g_patches->m_load_course_model.enable();
            g_patches->m_disable_camera_fade.enable();
        }
        
        if (!entry->IsActivated())
        {
            if (g_settings.m_options.backwards_camera)
                g_settings.m_options.backwards_camera = false;

            g_patches->m_disable_item_on_x.disable();
            g_patches->m_load_course_model.disable();
            g_patches->m_disable_camera_fade.disable();

            (*g_pointers->m_camera_matrix)->orientation = +50.f;
        }
    }
}