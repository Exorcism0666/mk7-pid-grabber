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
			bool session_logger{ false };
			bool render_optimizations{ false };
			bool spectator_rankboard{ false };
			bool show_mii_heads{ false };

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
