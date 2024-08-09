#pragma once

#include <CTRPluginFramework.hpp>

#include <format>

namespace base
{
	class logger
	{
	public:
		explicit logger() = default;
		~logger() = default;
		
		template <typename ...args_t>
		void info(std::format_string<args_t ...>, args_t &&...);

		void dump(std::string);

		static std::string get_current_date_time_string(bool human_readable);

	private:
		void log(std::string);
		
		CTRPluginFramework::Mutex m_mutex;
	};

	template <typename ...args_t>
    inline void logger::info(std::format_string<args_t ...> fmt, args_t &&...args)
    {
        auto str = std::format(fmt, std::forward<args_t>(args)...);
        log(str);
    }
	
	inline logger g_logger;
}