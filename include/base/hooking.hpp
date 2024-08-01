#pragma once

#include "hook_types/all.hpp"

#include "hooks.hpp"

#include <base/features.hpp>
#include <base/types.hpp>

namespace base
{
    class hooking
    {
	public:
		explicit hooking();
		~hooking();

        inline bool is_enabled() const { return m_enabled; }

        void enable();
		void disable();

    private:
        friend hooks;

        bool m_enabled{};

        hook_types::detour_hook m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData_hook;
    };

    inline hooking *g_hooking{};
}