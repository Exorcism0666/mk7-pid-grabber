#include <base/entries.hpp>

#include <base/settings.hpp>
#include <base/menu.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::spectator_mode(MenuEntry *entry)
    {
        auto keyboard = Keyboard(entry->Name());
        keyboard.DisplayTopScreen = true;
        keyboard.CanAbort(true);

        int choice = UINT32_MAX;

        auto &spectator_mode = g_settings.m_options.spectator_mode;

        do
        {
            keyboard.Populate(std::vector<std::string>
            {
                std::format("Toggle: {}", menu::s_toggles[spectator_mode.toggle]),
                std::format("Disable After Race: {}", menu::s_toggles[spectator_mode.reset])
            });

            choice = keyboard.Open();

            switch (choice)
            {
                case 0:
                    spectator_mode.toggle ^= true;
                break;

                case 1:
                    spectator_mode.reset ^= true;
                break;
            }
        }
        while (choice >= 0);
    }
}