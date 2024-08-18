#pragma once

#include <CTRPluginFramework.hpp>

#include <base/types.hpp>
#include <base/files.hpp>

namespace base
{
	class logger
	{
	public:
		explicit logger() = default;
		~logger() = default;

		template <typename ...args_t>
		void debug(std::format_string<args_t ...>, args_t &&...);

		template <typename ...args_t>
		void error(std::format_string<args_t ...>, args_t &&...);

		void dump_session(std::string);

		static std::string get_current_date_time_string(bool human_readable);

	private:
		void log(std::string, CTRPluginFramework::File, bool);
		
		CTRPluginFramework::Mutex m_mutex;
	};

	template <typename ...args_t>
    inline void logger::debug(std::format_string<args_t ...> fmt, args_t &&...args)
    {
#ifdef _DEBUG
        auto str = std::format(fmt, std::forward<args_t>(args)...);
        log(str, g_files->m_logger, true);
#endif
    }

	template <typename ...args_t>
    inline void logger::error(std::format_string<args_t ...> fmt, args_t &&...args)
    {
        auto str = std::format(fmt, std::forward<args_t>(args)...);
        log(str, g_files->m_error, false);
    }

	inline void logger::dump_session(std::string str)
    {
        log(str, g_files->m_session, false);
    }
	
	inline logger g_logger;
}