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

        keyboard.GetMessage() = Color::SkyBlue << "\n\nFile Location:\n\n" << Color::DodgerBlue << "sd:\\luma\\plugins\\00040000" << Utils::ToHex(Process::GetTitleID()) << "\\\n" << NAME << "\\" << g_files->m_session_log.GetName();

        int choice = UINT32_MAX;

        do
        {
            keyboard.Populate(std::vector<std::string>
            {
                std::format("Toggle: {}", menu::s_toggles[g_settings.m_options.session_logger]),
                std::format("View {}", g_files->m_session_log.GetName())
            });

            choice = keyboard.Open();

            switch (choice)
            {
                case 0:
                    g_settings.m_options.session_logger ^= true;
                break;

                case 1:
                {
                    auto file = g_files->m_session_log;

                    if (!file.GetSize())
                    {
                        utilities::print_error(Color::DodgerBlue << file.GetName() << Color::White << " is empty", false);

                        return;
                    }

                    auto text = utilities::read_file(file);

                    MessageBox(Color::DodgerBlue << file.GetName(), text, DialogType::DialogOk, ClearScreen::Both)();
                }
                break;
            }
        }
        while (choice >= 0);
    }
}