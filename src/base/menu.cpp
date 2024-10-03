#include <base/menu.hpp>

#include <base/entries.hpp>
#include <base/hooking.hpp>
#include <base/settings.hpp>
#include <base/patches.hpp>
#include <base/files.hpp>
#include <base/logger.hpp>
#include <base/pointers.hpp>
#include <base/services/rainbow_service.hpp>

#include "error_handler.cpp"

using namespace CTRPluginFramework;

#define DEFAULT_ENTRY [](MenuEntry *) {}

#ifdef _DEBUG
    #define MENU_TYPE 0
#else
    #define MENU_TYPE 1
#endif

#define FEATURES_FOLDER_NOTE Color::SkyBlue << "This folder contains additional features."

#define GAME_SESSION_NOTE Color::SkyBlue << "This fetches the current players inside an active game session or current lobby.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define OPPONENT_LIST_NOTE Color::SkyBlue << "This fetches only the opponent list from your save data, excluding the friend list.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define RENDER_OPTIMIZATIONS_NOTE Color::SkyBlue << "This entry disables the 3D and uncaps the FPS on the bottom screen during races."
#define LIVE_RANKBOARD_NOTE Color::SkyBlue << "This entry loads the player rankboard during the live view spectate."
#define MII_HEADS_NOTE Color::SkyBlue << "This entry replaces the character with the Mii heads during the course vote list and on the bottom screen during races."
#define SESSION_LOGGER_NOTE Color::SkyBlue << "This entry creates a detailed dump of the latest game session you played in.\n\n" << Color::DodgerBlue << "Press \uE000 for more info and options."
#define PID_SETTINGS_NOTE Color::SkyBlue << "This entry allows changing how the Principal ID gets displayed.\n\n" << Color::DodgerBlue << "Press \uE000 for more info and options."
#define SPECTATOR_NOTE Color::SkyBlue << "This entry puts you into spectator mode.\nPress \uE07C / \uE07B to swap, \uE079 to reset it.\n\n" << Color::Orange << "You can't undo it until the next race."
#define ITEMS_ON_MAP_NOTE Color::SkyBlue << "This entry displays people's items on the extended minimap."
#define BACKWARDS_CAM_NOTE Color::SkyBlue << "This entry allows you to look backwards.\nPress \uE002 to trigger it.\n\n" << Color::Orange << "This disables item usage on \uE002."

namespace base
{
    menu::menu()
    :
        m_plugin_menu(new PluginMenu(NAME, std::stoi(MAJOR), std::stoi(MINOR), std::stoi(REV), ABOUT, MENU_TYPE)),

        m_game_session_entry(new MenuEntry("Game Session", nullptr, entries::game_session, GAME_SESSION_NOTE)),
        m_opponent_list_entry(new MenuEntry("Opponent List", nullptr, entries::opponent_list, OPPONENT_LIST_NOTE)),
        m_session_logger_entry(new MenuEntry("Session Logger", nullptr, entries::session_logger, SESSION_LOGGER_NOTE)),
        m_spectator_mode_entry(new MenuEntry("Spectator Mode", nullptr, entries::spectator_mode, SPECTATOR_NOTE)),
        m_backwards_camera_entry(new MenuEntry("Backwards Camera", entries::backwards_camera, BACKWARDS_CAM_NOTE)),
        m_render_optimizations_entry(new MenuEntry("Render Optimizations", entries::render_optimizations, RENDER_OPTIMIZATIONS_NOTE)),
        m_load_rankboard_entry(new MenuEntry("Load Live View Rankboard", entries::toggle_rankboard, LIVE_RANKBOARD_NOTE)),
        m_show_mii_heads_entry(new MenuEntry("Mii Heads On Vote/Bottom Screen", entries::show_mii_heads, MII_HEADS_NOTE)),
        m_items_on_extended_map_entry(new MenuEntry("Show Items On Extended Mini Map", entries::items_on_extended_map, ITEMS_ON_MAP_NOTE)),
        m_pid_display_settings_entry(new MenuEntry("PID Display Settings", nullptr, entries::pid_display_settings, PID_SETTINGS_NOTE))
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
#ifdef _DEBUG
            return true;
#endif

            Sleep(Milliseconds(100));

            if (utilities::is_online() && utilities::is_in_race(true))
            {
                auto entry = g_menu->m_game_session_entry;

                entry->GetMenuFunc()(entry);

                return false;
            }
            
            return true;
        };

        m_plugin_menu->Callback(manage_data);

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
        
        if (auto folder = new MenuFolder("Additional Features", FEATURES_FOLDER_NOTE))
        {
            *folder += m_spectator_mode_entry;
            *folder += m_backwards_camera_entry;
            *folder += m_render_optimizations_entry;
            *folder += m_load_rankboard_entry;
            *folder += m_show_mii_heads_entry;
            *folder += m_items_on_extended_map_entry;

            *m_plugin_menu += folder;
        }

        *m_plugin_menu += m_pid_display_settings_entry;
    }

    void menu::finalize()
    {
        *GetArg<menu_types::spectator_mode>(m_spectator_mode_entry) = { false, false, false, UINT8_MAX };

        g_patches->m_disable_title_demo.enable();

        if (g_settings.m_options.backwards_camera)
            m_backwards_camera_entry->Enable();
        
        if (g_settings.m_options.render_optimizations)
            m_render_optimizations_entry->Enable();
        
        if (g_settings.m_options.load_rankboard)
            m_load_rankboard_entry->Enable();

        if (g_settings.m_options.show_mii_heads)
            m_show_mii_heads_entry->Enable();
        
        if (g_settings.m_options.items_on_extended_map)
            m_items_on_extended_map_entry->Enable();
    }

    void menu::manage_data()
    {
        if (!g_menu)
            return;
        
        auto data = GetArg<menu_types::spectator_mode>(g_menu->m_spectator_mode_entry);
        auto &spectator_mode = g_settings.m_options.spectator_mode;

        if (utilities::is_in_race(true))
        {
            if (spectator_mode.toggle && utilities::is_online())
            {
                if (!g_patches->m_force_default_camera.is_enabled())
                    g_patches->m_force_default_camera.enable();

                if (spectator_mode.reset && !utilities::is_spectating())
                    data->reset = true;

                if (!data->active)
                {
                    g_patches->m_disable_oob_camera.enable();
                    g_patches->m_disable_fade_out_0.enable();
                    g_patches->m_disable_fade_out_1.enable();
                    g_patches->m_disable_goal_demo.enable();
                    g_patches->m_disable_fpv.enable();
                    g_patches->m_disable_fog.enable();
                    g_patches->m_fix_camera_draw_0.enable();
                    g_patches->m_fix_camera_draw_1.enable();
                    g_patches->m_disable_blooper_0.enable();
                    g_patches->m_disable_blooper_1.enable();

                    data->active = true;
                }
            }
        }
        else
        {
            if ((*g_pointers->m_camera_matrix)->orientation != +50.f)
                (*g_pointers->m_camera_matrix)->orientation = +50.f;

            if (spectator_mode.toggle && data->reset)
            {
                spectator_mode.toggle = false;

                data->reset = false;
            }

            if (!spectator_mode.toggle && data->active)
            {
                if (!g_menu->m_backwards_camera_entry->IsActivated())
                    g_patches->m_force_default_camera.disable();

                g_patches->m_disable_oob_camera.disable();
                g_patches->m_disable_fade_out_0.disable();
                g_patches->m_disable_fade_out_1.disable();
                g_patches->m_disable_goal_demo.disable();
                g_patches->m_disable_fpv.disable();
                g_patches->m_disable_fog.disable();
                g_patches->m_fix_camera_draw_0.disable();
                g_patches->m_fix_camera_draw_1.disable();
                g_patches->m_disable_blooper_0.disable();
                g_patches->m_disable_blooper_1.disable();

                *data = { false, false, false, UINT8_MAX };
            }

            if (data->pending || data->target_id != UINT8_MAX)
            {
                data->pending = false;

                data->target_id = UINT8_MAX;
            }
        }
    }
}