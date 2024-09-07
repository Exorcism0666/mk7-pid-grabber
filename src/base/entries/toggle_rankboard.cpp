#include <base/entries.hpp>

#include <base/settings.hpp>

namespace base
{
    void entries::toggle_rankboard(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            if (!g_settings.m_options.load_rankboard)
                g_settings.m_options.load_rankboard = true;
        
        if (!entry->IsActivated())
            if (g_settings.m_options.load_rankboard)
                g_settings.m_options.load_rankboard = false;
    }
}