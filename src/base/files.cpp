#include <base/files.hpp>

#include <base/logger.hpp>

namespace base
{
	using namespace CTRPluginFramework;

	files::files()
	{
#ifdef _DEBUG   
        if (File::Open(m_logger, "debug.log", File::Mode::READ | File::Mode::WRITE | File::Mode::CREATE | File::Mode::SYNC) != File::OPResult::SUCCESS)
            abort();
#endif

        if (Directory::Open(m_error_dir, "errors", true) != Directory::OPResult::SUCCESS)
            abort();

        if (File::Open(m_session, "mk7_session.log", File::Mode::READ | File::Mode::WRITE | File::Mode::CREATE | File::Mode::SYNC) != File::OPResult::SUCCESS)
            abort();
        
        if (File::Open(m_settings, "settings.json", File::Mode::READ | File::Mode::WRITE | File::Mode::CREATE | File::Mode::SYNC) != File::OPResult::SUCCESS)
            abort();

        g_files = this;
	}

	files::~files()
	{
        g_files = nullptr;

        m_settings.Close();
        m_session.Close();
        m_error_dir.Close();

#ifdef _DEBUG
        m_logger.Close();
#endif
	}

    void files::set_working_directory()
    {
        auto path = std::string("/luma/plugins");

        // Start from the root
        Directory::ChangeWorkingDirectory("");

        // https://gitlab.com/thepixellizeross/ctrpluginframework/-/blob/develop/Library/source/pluginInit.cpp#L157
        if (FwkSettings::Header->isDefaultPlugin)
        {
            path += "/ActionReplay";

            if (!Directory::IsExists(path))
                Directory::Create(path);

            path += Utils::Format("/%016llX", Process::GetTitleID());

            if (!Directory::IsExists(path))
                Directory::Create(path);
        }
        else
        {
            // Exists already to run the plugin
            path += Utils::Format("/%016llX", Process::GetTitleID());
        }

        path += "/" NAME;

        if (!Directory::IsExists(path))
            Directory::Create(path);

        Directory::ChangeWorkingDirectory(path + "/");
    }

    void files::create_file(std::string path)
    {
        if (File::Create(path) != File::OPResult::SUCCESS)
            abort();
    }
}