#include <base/logger.hpp>

namespace CTRPluginFramework
{
    using namespace base;

    static bool dumped = false;

    static Process::ExceptionCallbackState error_handler(ERRF_ExceptionInfo *excep, CpuRegisters *regs)
    {
        if (!dumped)
        {
            g_files->get_error_log().Clear();

            std::string name;

            Process::GetName(name);

            std::string log = std::format("Update: {}", DATE);
            log += std::format("\nLog Date Time: {}", g_logger.get_current_date_time_string(true));

            log += std::format("\nProcess: {} ({:016X})\n", name, Process::GetTitleID());

            log += "\nCPU Registers:\n";

            for (size_t i = 0; i < std::size(regs->r); i++)
            {
                if (i < 10)
                    log += std::format("\nR{:d} : {:08X}", i, regs->r[i]);
                else
                    log += std::format("\nR{:d}: {:08X}", i, regs->r[i]);
            }
            
            log += std::format("\n\nSP: {:08X}", regs->sp);
            log += std::format("\nLR: {:08X}", regs->lr);
            log += std::format("\nPC: {:08X}", regs->pc);
            
            g_logger.error("{}", log);

            dumped = true;
        }

        OSD::Lock();
        
        Screen top = OSD::GetTopScreen(), btm = OSD::GetBottomScreen();

        top.DrawRect(0, 0, 400, 240, Color());
        top.DrawSysfont("An error has occured", 8, 4, Color::Red);
        top.DrawSysfont(Color::Orange << "Error was logged inside " + g_files->get_error_log().GetName(), 8, 40);
        top.DrawSysfont("File Location:", 8, 80, Color::SkyBlue);
        top.DrawSysfont(std::format("sd:\\luma\\plugins\\{:016X}\\", Process::GetTitleID()), 8, 100, Color::DodgerBlue);
        top.DrawSysfont(std::format("{}\\{}", NAME, g_files->get_error_log().GetName()), 8, 120, Color::DodgerBlue);
        top.DrawSysfont(std::format("Please send it to {}" , CREATOR), 8, 140, Color::Silver);
        top.DrawSysfont("Press any button to return to the \uE073 HOME-Menu", 8, 180, Color::Turquoise);

        btm.DrawRect(0, 0, 320, 240, Color());

        OSD::SwapBuffers();

        OSD::Unlock();

        Controller::Update();

        if (Controller::GetKeysPressed())
            return Process::EXCB_RETURN_HOME;
        
        return Process::EXCB_LOOP;
    }
}