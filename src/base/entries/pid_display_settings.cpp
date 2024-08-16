#include <base/entries.hpp>

#include <base/menu.hpp>
#include <base/files.hpp>
#include <base/settings.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::pid_display_settings(MenuEntry *entry)
    {
        auto keyboard = Keyboard(entry->Name());
        keyboard.DisplayTopScreen = true;
        keyboard.CanAbort(true);

        std::string description = Color::White << "\n\nChoose in which format the PID should display as.";

        description += Color::Yellow << "\n\nModes" << Color::White << ":\n";
        description += Color::White << "\n- " << Color::Turquoise << "Decimal" << Color::DeepSkyBlue << " (DEC)";
        description += Color::White << "\n- " << Color::Turquoise << "Hexadecimal" << Color::DeepSkyBlue << " (HEX)";
        description += Color::White << "\n- " << Color::Turquoise << "Decimal + Hexadecimal";

        keyboard.GetMessage() = description;

        auto &pid_display = g_settings.m_options.pid_display;

        int choice = UINT32_MAX;

        do
        {
            keyboard.Populate(std::vector<std::string>
            {
                std::format("Mode: {}", magic_enum::enum_name(pid_display.mode))
            });

            choice = keyboard.Open();

            switch (choice)
            {
                case 0:
                    pid_display.mode = magic_enum::enum_value<decltype(pid_display.mode)>((magic_enum::enum_underlying(pid_display.mode) + 1) % magic_enum::enum_count<decltype(pid_display.mode)>());
                break;
            }
        }
        while (choice >= 0);
    }
}