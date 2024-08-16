#include <base/entries.hpp>

#include <base/patches.hpp>
#include <base/settings.hpp>

namespace base
{
    void entries::show_mii_heads(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (!g_settings.m_options.show_mii_heads)
                g_settings.m_options.show_mii_heads = true;

            g_patches->m_render_mii_head_0.enable();
            g_patches->m_render_mii_head_1.enable();
            g_patches->m_render_mii_head_2.enable();
            g_patches->m_mii_head_on_votes_0.enable();
            g_patches->m_mii_head_on_votes_1.enable();
            g_patches->m_mii_head_on_minimap.enable();
        }
        
        if (!entry->IsActivated())
        {
            if (g_settings.m_options.show_mii_heads)
                g_settings.m_options.show_mii_heads = false;

            g_patches->m_render_mii_head_0.disable();
            g_patches->m_render_mii_head_1.disable();
            g_patches->m_render_mii_head_2.disable();
            g_patches->m_mii_head_on_votes_0.disable();
            g_patches->m_mii_head_on_votes_1.disable();
            g_patches->m_mii_head_on_minimap.disable();
        }
    }
}