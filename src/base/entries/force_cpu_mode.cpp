#include <base/entries.hpp>

#include <base/settings.hpp>

namespace base
{
    void entries::force_cpu_mode(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            if (!g_settings.m_options.force_cpu_mode)
                g_settings.m_options.force_cpu_mode = true;
        
        if (!entry->IsActivated())
            if (g_settings.m_options.force_cpu_mode)
                g_settings.m_options.force_cpu_mode = false;
    }
}