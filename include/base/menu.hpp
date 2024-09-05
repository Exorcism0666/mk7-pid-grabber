#pragma once

#include <base/menu_types.hpp>

#include <CTRPluginFramework.hpp>

#include <map>

namespace base
{
    class menu
    {
    private:
        friend struct entries;
        friend class features;
        
        void create();
        void finalize();
        static void reset_data();

        inline static std::map<bool, std::string> s_toggles =
        {
            { false, (CTRPluginFramework::Color(255, 0, 0) << "OFF") + (CTRPluginFramework::Color::White << "") },
            { true, (CTRPluginFramework::Color(0, 255, 0) << "ON") + (CTRPluginFramework::Color::White << "") }
        };
    public:
		explicit menu();
		~menu();

        void run();

        std::vector<nn::nex::Station *> station_list;

        CTRPluginFramework::PluginMenu *m_plugin_menu;

        CTRPluginFramework::MenuEntry *m_game_session_entry;
        CTRPluginFramework::MenuEntry *m_opponent_list_entry;
        CTRPluginFramework::MenuEntry *m_session_logger_entry;
        CTRPluginFramework::MenuEntry *m_spectator_mode_entry;
        CTRPluginFramework::MenuEntry *m_render_optimizations_entry;
        CTRPluginFramework::MenuEntry *m_spectator_rankboard_entry;
        CTRPluginFramework::MenuEntry *m_show_mii_heads_entry;
        CTRPluginFramework::MenuEntry *m_items_on_extended_map_entry;
        CTRPluginFramework::MenuEntry *m_pid_display_settings_entry;
    };

    inline menu *g_menu{};
}