#include <base/entries.hpp>

#include <base/settings.hpp>
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
        
        if (!entry->IsActivated())
        {
            if (g_settings.m_options.spectator_mode)
                g_settings.m_options.spectator_mode = false;
        }
    }
}