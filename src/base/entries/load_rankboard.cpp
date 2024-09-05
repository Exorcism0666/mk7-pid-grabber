#include <base/entries.hpp>

#include <base/settings.hpp>

namespace base
{
    void entries::load_rankboard(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            if (!g_settings.m_options.spectator_rankboard)
                g_settings.m_options.spectator_rankboard = true;
        
        if (!entry->IsActivated())
            if (g_settings.m_options.spectator_rankboard)
                g_settings.m_options.spectator_rankboard = false;
    }
}