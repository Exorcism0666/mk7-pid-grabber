#pragma once

#include <CTRPluginFramework.hpp>

namespace base
{
	class files
	{
	public:
		explicit files();
		~files();

		static void set_working_directory();
		static void create_file(std::string);

		inline std::string err_dir_name() { return m_error_dir.GetName(); };
	private:
		friend class menu;
		friend class logger;
		friend class settings;
		friend struct entries;
		friend struct features;

		CTRPluginFramework::File m_logger;
		CTRPluginFramework::File m_settings;
		CTRPluginFramework::File m_session;
		CTRPluginFramework::Directory m_error_dir;
	};

	inline files *g_files{};
}