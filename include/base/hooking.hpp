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
        
        hook_types::detour_hook m_Sequence_RacePage_initControl_WiFiVS_hook;
        hook_types::detour_hook m_Sequence_RacePage_initControl_WiFiBattle_hook;
        hook_types::detour_hook m_Sequence_MenuWiFi_Confirm_onPageEnter_hook;
        hook_types::detour_hook m_Kart_Vehicle_calcMove_hook;
        hook_types::detour_hook m_Kart_Camera_calcApply_hook;
        hook_types::detour_hook m_Item_ItemDirector_slot_StartSlot_hook;
        hook_types::detour_hook m_Effect_KartEffect_calcCameraEffectImpl_hook;
        hook_types::detour_hook m_Effect_KartEffect_calcEnvEffect_hook;
        hook_types::detour_hook m_Effect_KartEffect_createWaterOutTrig_hook;
        hook_types::detour_hook m_Item_ItemDirector_itemEventRecvHandler_hook;
        hook_types::detour_hook m_Kart_NetData_read_hook;
    };

    inline hooking *g_hooking{};
}