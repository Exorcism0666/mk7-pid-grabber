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
		
		inline CTRPluginFramework::File get_error_log() { return m_error; };
	private:
		friend class menu;
		friend class logger;
		friend class settings;
		friend struct entries;
		friend struct features;
		
		CTRPluginFramework::File m_logger;
		CTRPluginFramework::File m_settings;
		CTRPluginFramework::File m_session;
		CTRPluginFramework::File m_error;
	};

	inline files *g_files{};
}