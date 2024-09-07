#include <base/entries.hpp>

#include <base/patches.hpp>
#include <base/settings.hpp>

namespace base
{
    void entries::items_on_extended_map(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (!g_settings.m_options.items_on_extended_map)
                g_settings.m_options.items_on_extended_map = true;

            g_patches->m_items_on_extended_map_0.enable();
            g_patches->m_items_on_extended_map_1.enable();
        }
        
        if (!entry->IsActivated())
        {
            if (g_settings.m_options.items_on_extended_map)
                g_settings.m_options.items_on_extended_map = false;

            g_patches->m_items_on_extended_map_0.disable();
            g_patches->m_items_on_extended_map_1.disable();
        }
    }
}