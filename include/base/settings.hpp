#pragma once

#include <base/types.hpp>

namespace base
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		bool load();
		bool store();
		bool reset();

		struct options
		{
			struct session_logger
			{
				bool enabled{ true };
				bool notify{ true };
			}
			session_logger;

			bool spectator_mode{ false };
			bool render_optimizations{ false };
			bool spectator_rankboard{ false };
			bool show_mii_heads{ false };
			bool items_on_extended_map{ false };

			struct pid_display
			{
				enum class mode : u8
				{
					Decimal,
					Hexadecimal,
					Both
				}
				mode{ mode::Both };
			}
			pid_display;
		}
		m_options{};

	private:
		bool load_impl();
	};

	inline settings g_settings;
}
