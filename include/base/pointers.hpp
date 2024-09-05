#pragma once

#include <base/types.hpp>

using GetNetworkPlayerData_t = Net::NetworkPlayerData * (*)(Net::NetworkPlayerDataManager *, u8);
using StationSelectionIteratorTemplate_t = void (*)(nn::nex::SelectionIteratorTemplate_Station *);
using IteratorOverDOsAdvanceToValidItem_t = void (*)(nn::nex::SelectionIteratorTemplate_Station *, bool);
using IteratorOverDOsDestructor_t = void (*)(nn::nex::SelectionIteratorTemplate_Station *);
using InitRankboard_t = void (*)(void *);
using IsDisconnected_t = bool (*)(Net::StationBufferManager *, u8);
using GetRaceInfo_t = RaceSys::CRaceInfo * (*)(void);
using KartInfoProxy_t = void (*)(Kart::Vehicle * &, u8);

namespace base
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		GetNetworkPlayerData_t get_network_player_data;
        StationSelectionIteratorTemplate_t station_selection_iterator_template;
        IteratorOverDOsAdvanceToValidItem_t iterator_over_DOs_advance_to_valid_item;
		IteratorOverDOsDestructor_t iterator_over_DOs_destructor;
		InitRankboard_t init_rankBoard;
		IsDisconnected_t is_disconnected;
		GetRaceInfo_t get_race_info;
		KartInfoProxy_t kart_info_proxy;

        Net::NetworkEngine **m_network_engine;
		void *m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData;
		void *m_Sequence_RacePage_initControl_WiFiVS;
		void *m_Sequence_RacePage_initControl_WiFiBattle;
		void *m_System_ProjectGameFramework_procDraw;
		void *m_System_ProjectGameFramework_procFrame;
		void *m_Mii_MiiEngine_createMiiFace;
		void *m_Sequence_Menu_UpBarController_setTex;
		void *m_Sequence_BaseRacePage_initMapIcon;
		void *m_CourseVoteListSetTexture; // unknown symbol
		void *m_Sequence_MenuWiFi_Confirm_onPageEnter;
		void *m_Kart_Vehicle_calcMove;
		void *m_Effect_KartEffect_calcAfterCameraUpdate;
		void *m_Kart_Camera_calcApply;
		void *m_Item_ItemDirector_slot_StartSlot;
		void *m_Effect_KartEffect_calcCameraEffectImpl;
		void *m_Effect_KartEffect_calcEnvEffect;
		void *m_Effect_KartEffect_createGessoTrig;
		void *m_Effect_KartEffect_createWaterOutTrig;
		void *m_Sequence_BaseRacePage_drawItemIcon;
	};

	inline pointers *g_pointers{};
}