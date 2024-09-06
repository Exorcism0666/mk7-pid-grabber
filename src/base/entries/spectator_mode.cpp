#include <base/entries.hpp>

#include <base/settings.hpp>
#include <base/patches.hpp>
#include <base/menu.hpp>

namespace base
{
    void entries::spectator_mode(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (!g_settings.m_options.spectator_mode)
                g_settings.m_options.spectator_mode = true;
        }
        
        if (entry->IsActivated())
        {
            if (utilities::is_in_race(true))
            {
                if (utilities::is_alone())
                    return;
                
                auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);

                if (!data->active)
                {
                    data->active = true;

                    g_patches->m_disable_oob_camera.enable();
                    g_patches->m_disable_fade_out_0.enable();
                    g_patches->m_disable_fade_out_1.enable();
                    g_patches->m_disable_goal_demo.enable();
                    g_patches->m_disable_title_demo.enable();
                }
            }
        }
        else
        {
            if (g_settings.m_options.spectator_mode)
                g_settings.m_options.spectator_mode = false;
        }
    }
}