#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

namespace base
{
    void features::load_rankboard(void *race_page)
    {
        if (g_menu->m_load_rankboard_entry->IsActivated())
            g_pointers->init_rankBoard(race_page);
    }
}