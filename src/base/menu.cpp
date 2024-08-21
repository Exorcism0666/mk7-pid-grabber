#include <base/menu.hpp>

#include <base/entries.hpp>
#include <base/hooking.hpp>
#include <base/settings.hpp>
#include <base/patches.hpp>
#include <base/files.hpp>
#include <base/logger.hpp>

#include <base/services/rainbow_service.hpp>

#include "error_handler.cpp"

using namespace CTRPluginFramework;

#define DEFAULT_ENTRY [](MenuEntry *) {}

#ifdef _DEBUG
    #define MENU_TYPE 0
#else
    #define MENU_TYPE 1
#endif

#define GAME_SESSION_NOTE Color::SkyBlue << "This fetches the current players inside an active game session or current lobby.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define OPPONENT_LIST_NOTE Color::SkyBlue << "This fetches only the opponent list from your save data, excluding the friend list.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define RENDER_OPTIMIZATIONS_NOTE Color::SkyBlue << "This entry disables the 3D and uncaps the FPS on the bottom screen during races."
#define LIVE_RANKBOARD_NOTE Color::SkyBlue << "This entry loads the player rankboard during the live view spectate."
#define MII_HEADS_NOTE Color::SkyBlue << "This entry replaces the character with the Mii heads during the course vote list and on the bottom screen during races."
#define SESSION_LOGGER_NOTE Color::SkyBlue << "This entry creates a detailed dump of the latest game session you played in.\n\n" << Color::DodgerBlue << "Press \uE000 for more info and options."
#define PID_SETTINGS_NOTE Color::SkyBlue << "This entry allows changing how the Principal ID gets displayed.\n\n" << Color::DodgerBlue << "Press \uE000 for more info and options."

namespace base
{
    menu::menu()
    :
        m_plugin_menu(new PluginMenu(NAME, std::stoi(MAJOR), std::stoi(MINOR), std::stoi(REV), ABOUT, MENU_TYPE)),

        m_game_session_entry(new MenuEntry("Game Session", nullptr, entries::game_session, GAME_SESSION_NOTE)),
        m_opponent_list_entry(new MenuEntry("Opponent List", nullptr, entries::opponent_list, OPPONENT_LIST_NOTE)),
        m_session_logger_entry(new MenuEntry("Session Logger", nullptr, entries::session_logger, SESSION_LOGGER_NOTE)),
        m_render_optimizations_entry(new MenuEntry("Render Optimizations", entries::render_optimizations, RENDER_OPTIMIZATIONS_NOTE)),
        m_spectator_rankboard_entry(new MenuEntry("Spectator Mode Rankboard", entries::load_rankboard, LIVE_RANKBOARD_NOTE)),
        m_show_mii_heads_entry(new MenuEntry("Mii Heads On Vote/Bottom Screen", entries::show_mii_heads, MII_HEADS_NOTE)),
        m_pid_display_settings_entry(new MenuEntry("Principal ID Display Settings", nullptr, entries::pid_display_settings, PID_SETTINGS_NOTE))
    {
        m_plugin_menu->SynchronizeWithFrame(true);
        m_plugin_menu->ShowWelcomeMessage(false);
        
#ifndef _DEBUG
        m_plugin_menu->SetHexEditorState(false);

        auto settings = FwkSettings::Get();

        settings.AllowActionReplay = false;
		settings.AllowSearchEngine = false;
#endif

        m_plugin_menu->OnNewFrame = [](Time)
        {
            g_rainbow_service->run();

            auto const color = g_rainbow_service->get_ctrpf_color();

            g_menu->m_plugin_menu->Title() = color << NAME;
        };

        m_plugin_menu->OnClosing = []() { g_settings.store(); };

        m_plugin_menu->OnOpening = []()
        {
            Sleep(Milliseconds(100));
            
            return true;
        };

        create();
        
        finalize();

        station_list.clear();

#ifndef _DEBUG
        Process::exceptionCallback = error_handler;
#endif

        g_menu = this;
    }

    menu::~menu()
    {
        g_menu = nullptr;

        delete m_plugin_menu;
    }

    void menu::run()
    {
        m_plugin_menu->Run();
    }

    void menu::create()
    {
        *m_plugin_menu += m_game_session_entry;
        *m_plugin_menu += m_opponent_list_entry;
        *m_plugin_menu += m_session_logger_entry;

        m_render_optimizations_entry->UseTopSeparator();

        *m_plugin_menu += m_render_optimizations_entry;
        *m_plugin_menu += m_spectator_rankboard_entry;
        *m_plugin_menu += m_show_mii_heads_entry;

        m_pid_display_settings_entry->UseTopSeparator();

        *m_plugin_menu += m_pid_display_settings_entry;
    }

    void menu::finalize()
    {
        if (g_settings.m_options.render_optimizations)
            m_render_optimizations_entry->Enable();
        
        if (g_settings.m_options.spectator_rankboard)
            m_spectator_rankboard_entry->Enable();

        if (g_settings.m_options.show_mii_heads)
            m_show_mii_heads_entry->Enable();
    }
}