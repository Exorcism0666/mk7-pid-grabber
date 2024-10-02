#include <base/hooking.hpp>

#include <base/pointers.hpp>

namespace base
{
    hooking::hooking()
	:
		m_Sequence_RacePage_initControl_WiFiVS_hook("Sequence::RacePage::initControl_WiFiVS", g_pointers->m_Sequence_RacePage_initControl_WiFiVS, reinterpret_cast<void *>(&hooks::Sequence_RacePage_initControl_WiFiVS)),
		m_Sequence_RacePage_initControl_WiFiBattle_hook("Sequence::RacePage::initControl_WiFiVS", g_pointers->m_Sequence_RacePage_initControl_WiFiBattle, reinterpret_cast<void *>(&hooks::Sequence_RacePage_initControl_WiFiBattle)),
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook("Sequence::MenuWiFi_Confirm::onPageEnter", g_pointers->m_Sequence_MenuWiFi_Confirm_onPageEnter, reinterpret_cast<void *>(&hooks::Sequence_MenuWiFi_Confirm_onPageEnter)),
		m_Kart_Vehicle_calcMove_hook("Kart::Vehicle::calcMove", g_pointers->m_Kart_Vehicle_calcMove, reinterpret_cast<void *>(&hooks::Kart_Vehicle_calcMove)),
		m_Kart_Camera_calcApply_hook("Kart::Camera::calcApply", g_pointers->m_Kart_Camera_calcApply, reinterpret_cast<void *>(&hooks::Kart_Camera_calcApply)),
		m_Item_ItemDirector_slot_StartSlot_hook("Item::ItemDirector::slot_StartSlot", g_pointers->m_Item_ItemDirector_slot_StartSlot, reinterpret_cast<void *>(&hooks::Item_ItemDirector_slot_StartSlot)),
		m_Effect_KartEffect_calcCameraEffectImpl_hook("Effect::KartEffect::_calcCameraEffectImpl", g_pointers->m_Effect_KartEffect_calcCameraEffectImpl, reinterpret_cast<void *>(&hooks::Effect_KartEffect_calcCameraEffectImpl)),
		m_Effect_KartEffect_calcEnvEffect_hook("Effect::KartEffect::_calcEnvEffect", g_pointers->m_Effect_KartEffect_calcEnvEffect, reinterpret_cast<void *>(&hooks::Effect_KartEffect_calcEnvEffect)),
		m_Effect_KartEffect_createWaterOutTrig_hook("Effect::KartEffect::createWaterOutTrig", g_pointers->m_Effect_KartEffect_createWaterOutTrig, reinterpret_cast<void *>(&hooks::Effect_KartEffect_createWaterOutTrig)),
		m_Item_ItemDirector_itemEventRecvHandler_hook("Item::ItemDirector::_itemEventRecvHandler", g_pointers->m_Item_ItemDirector_itemEventRecvHandler, reinterpret_cast<void *>(&hooks::Item_ItemDirector_itemEventRecvHandler)),
		m_Kart_NetData_read_hook("Kart::NetData::read", g_pointers->m_Kart_NetData_read, reinterpret_cast<void *>(hooks::Kart_NetData_read))
	{
		g_hooking = this;
	}

	hooking::~hooking()
	{
		g_hooking = nullptr;

		if (m_enabled)
			disable();
	}

    void hooking::enable()
	{
		m_Sequence_RacePage_initControl_WiFiVS_hook.enable();
		m_Sequence_RacePage_initControl_WiFiBattle_hook.enable();
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.enable();
		m_Kart_Vehicle_calcMove_hook.enable();
		m_Kart_Camera_calcApply_hook.enable();
		m_Item_ItemDirector_slot_StartSlot_hook.enable();
		m_Effect_KartEffect_calcCameraEffectImpl_hook.enable();
		m_Effect_KartEffect_calcEnvEffect_hook.enable();
		m_Effect_KartEffect_createWaterOutTrig_hook.enable();
		m_Item_ItemDirector_itemEventRecvHandler_hook.enable();
		m_Kart_NetData_read_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_Sequence_RacePage_initControl_WiFiVS_hook.disable();
		m_Sequence_RacePage_initControl_WiFiBattle_hook.disable();
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.disable();
		m_Kart_Vehicle_calcMove_hook.disable();
		m_Kart_Camera_calcApply_hook.disable();
		m_Item_ItemDirector_slot_StartSlot_hook.disable();
		m_Effect_KartEffect_calcCameraEffectImpl_hook.disable();
		m_Effect_KartEffect_calcEnvEffect_hook.disable();
		m_Effect_KartEffect_createWaterOutTrig_hook.disable();
		m_Item_ItemDirector_itemEventRecvHandler_hook.disable();
		m_Kart_NetData_read_hook.disable();

		m_enabled = false;
	}
}