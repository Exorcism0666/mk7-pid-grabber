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
		CameraMatrix **m_camera_matrix;

		void *m_Sequence_RacePage_initControl_WiFiVS;
		void *m_Sequence_RacePage_initControl_WiFiBattle;
		void *m_System_ProjectGameFramework_procDraw;
		void *m_System_ProjectGameFramework_procFrame;
		void *m_Mii_MiiEngine_createMiiFace;
		void *m_Sequence_Menu_UpBarController_setTex;
		void *m_Sequence_BaseRacePage_initMapIcon;
		void *m_CourseVoteListSetTexture;
		void *m_Sequence_MenuWiFi_Confirm_onPageEnter;
		void *m_Kart_Vehicle_calcMove;
		void *m_Effect_KartEffect_calcAfterCameraUpdate;
		void *m_Kart_Camera_calcApply;
		void *m_Item_ItemDirector_slot_StartSlot;
		void *m_Effect_KartEffect_calcCameraEffectImpl;
		void *m_Effect_KartEffect_calcEnvEffect;
		void *m_Effect_KartEffect_createWaterOutTrig;
		void *m_Sequence_BaseRacePage_drawItemIcon;
		void *m_Kart_Vehicle_startFadeOut;
		void *m_Demo_DemoCameraDirector_startGoalDemo;
		void *m_Sequence_MenuTitle_onPageEnter;
		void *m_Item_ItemDirector_itemEventRecvHandler;
		void *m_System_KDPadDirector_calc;
		void *m_Kart_NetData_read;
		void *m_Kart_Camera_calcDraw;
		void *m_Item_ItemObjGesso_stateAttacked;
		void *m_Item_ItemObjGesso_stateInitAttacked;
		void *m_nw_gfx_RenderContext_RenderPrimitive;
		void *m_Item_ItemDirector_calcKeyInput_EachPlayer;
		void *m_Kart_Camera_calcGndEvade;
	};

	inline pointers *g_pointers{};
}