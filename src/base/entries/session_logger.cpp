#include <base/entries.hpp>

#include <base/menu.hpp>
#include <base/files.hpp>
#include <base/settings.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::session_logger(MenuEntry *entry)
    {
        auto keyboard = Keyboard(entry->Name());
        keyboard.DisplayTopScreen = true;
        keyboard.CanAbort(true);

        keyboard.GetMessage() = Color::SkyBlue << "\n\nFile Location:\n\n" << Color::DodgerBlue << std::format("sd:\\luma\\plugins\\{:016X}\\", Process::GetTitleID()) << "\n" << NAME << "\\" << g_files->m_session.GetName();

        auto &session_logger = g_settings.m_options.session_logger;

        int choice = UINT32_MAX;

        do
        {
            keyboard.Populate(std::vector<std::string>
            {
                std::format("Toggle: {}", menu::s_toggles[session_logger.enabled]),
                std::format("Notify: {}", menu::s_toggles[session_logger.notify])
            });

            choice = keyboard.Open();

            switch (choice)
            {
                case 0:
                    session_logger.enabled ^= true;
                break;

                case 1:
                    session_logger.notify ^= true;
                break;
            }
        }
        while (choice >= 0);
    }
}