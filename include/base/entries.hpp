#pragma once

#include <CTRPluginFramework.hpp>
#include <base/utilities.hpp>

namespace base
{
	struct entries
	{
		static void game_session(CTRPluginFramework::MenuEntry *);
		static void opponent_list(CTRPluginFramework::MenuEntry *);
		static void session_logger(CTRPluginFramework::MenuEntry *);
		static void spectator_mode(CTRPluginFramework::MenuEntry *);
		static void render_optimizations(CTRPluginFramework::MenuEntry *);
		static void toggle_rankboard(CTRPluginFramework::MenuEntry *);
		static void show_mii_heads(CTRPluginFramework::MenuEntry *);
		static void items_on_extended_map(CTRPluginFramework::MenuEntry *);
		static void pid_display_settings(CTRPluginFramework::MenuEntry *);
	};
}