#pragma once

#include <base/types.hpp>

namespace base
{
	struct hooks
	{
		static void Sequence_RacePage_initControl_WiFiVS(void *);
		static void Sequence_RacePage_initControl_WiFiBattle(void *);
		static void Sequence_MenuWiFi_Confirm_onPageEnter(void *);
		static void Kart_Vehicle_calcMove(Kart::Vehicle *, bool, bool);
		static void Kart_Camera_calcApply(Kart::Camera *, float, bool, float, float);
		static void Item_ItemDirector_slot_StartSlot(void *, u8, u8);
		static void Effect_KartEffect_calcCameraEffectImpl(Effect::KartEffect *);
		static void Effect_KartEffect_calcEnvEffect(Effect::KartEffect *);
		static void Effect_KartEffect_createWaterOutTrig(Effect::KartEffect *);
		static bool Item_ItemDirector_itemEventRecvHandler(void *, Net::NetworkItemEventDataMgr::SlotData *);
		static bool Kart_NetData_read(Kart::NetData *, void *, Kart::NetData **, Kart::NetData **);
	};
}