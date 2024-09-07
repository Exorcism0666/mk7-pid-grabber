#include <base/pointers.hpp>

#include <base/memory/all.hpp>

namespace base
{
	pointers::pointers()
	{
		auto batch = memory::batch();

		batch.add("Net::NetworkPlayerDataManager::getNetworkPlayerData", "A0 20 9F E5 04 40 2D E5 10 20 92 E5 1E 2E 82 E2", [this](memory::handle handle)
		{
			get_network_player_data = handle.as<decltype(get_network_player_data)>();
        });

		batch.add("nn::nex::SelectionIteratorTemplate<nn::nex::Station>::SelectionIteratorTemplate", "F0 47 2D E9 01 20 A0 E3 02 10 A0 E1", [this](memory::handle handle)
		{
            station_selection_iterator_template = handle.as<decltype(station_selection_iterator_template)>();
        });

        batch.add("nn::nex::IteratorOverDOs::AdvanceToValidItem", "F0 47 2D E9 00 40 A0 E1 01 80 A0 E1 00 10 A0 E3 98 02 9F E5", [this](memory::handle handle)
		{
			iterator_over_DOs_advance_to_valid_item = handle.as<decltype(iterator_over_DOs_advance_to_valid_item)>();
        });

		batch.add("nn::nex::IteratorOverDOs::~IteratorOverDOs", "38 40 2D E9 00 40 A0 E1 30 00 9F E5 00 10 A0 E3", [this](memory::handle handle)
		{
            iterator_over_DOs_destructor = handle.as<decltype(iterator_over_DOs_destructor)>();
        });
		
		batch.add("Net::NetworkEngine", "B4 29 00 00 D4 27 00 00 78 78 00 00 F8 05 00 00", [this](memory::handle handle)
		{
			m_network_engine = *handle.add(0x1C).as<decltype(m_network_engine) *>();
		});

		batch.add("Sequence::RacePage::initControl_WiFiVS", "70 40 2D E9 00 40 A0 E1 ? ? ? EB ? ? ? EB 00 00 50 E3 04 00 A0 E1 01 00 00 0A ? ? ? EB ", [this](memory::handle handle)
		{
			m_Sequence_RacePage_initControl_WiFiVS = handle.as<decltype(m_Sequence_RacePage_initControl_WiFiVS)>();
		});

		batch.add("Sequence::RacePage::initControl_WiFiBattle", "70 40 2D E9 00 40 A0 E1 74 02 90 E5 00 00 50 E3 03 00 00 0A 01 00 50 E3 04 00 A0 01", [this](memory::handle handle)
		{
			m_Sequence_RacePage_initControl_WiFiBattle = handle.as<decltype(m_Sequence_RacePage_initControl_WiFiBattle)>();
		});

		batch.add("Sequence::BaseRacePage::initRankBoard", "F0 4F 2D E9 F4 D0 4D E2 00 40 A0 E1 ? ? ? EB D0 00 8D E5 ? ? ? ? 10 00 90 E5 1E 0E 80 E2 38 10 D0 E5", [this](memory::handle handle)
		{
			init_rankBoard = handle.as<decltype(init_rankBoard)>();
		});

		batch.add("System::ProjectGameFramework::procDraw_", "44 01 9F E5 20 60 94 E5 00 00 90 E5 06 50 A0 E1", [this](memory::handle handle)
		{
			m_System_ProjectGameFramework_procDraw = handle.sub(0x10).as<decltype(m_System_ProjectGameFramework_procDraw)>();
		});

		batch.add("System::ProjectGameFramework::procFrame_", "00 60 90 E5 00 00 99 E5 ? ? ? EB 02 4A 85 E2 78 00 94 E5 00 01 85 E0", [this](memory::handle handle)
		{
			m_System_ProjectGameFramework_procFrame = handle.sub(0x14).as<decltype(m_System_ProjectGameFramework_procFrame)>();
		});

		batch.add("Mii::MiiEngine::createMiiFace", "00 20 A0 E1 ? ? ? E2 00 50 A0 E3 58 30 8D E5 5C 00 8D E5 58 10 8D E2 00 30 E0 E3", [this](memory::handle handle)
		{
			m_Mii_MiiEngine_createMiiFace = handle.sub(0x24).as<decltype(m_Mii_MiiEngine_createMiiFace)>();
		});

		batch.add("Sequence::Menu_UpBarController::setTex", "00 C3 B0 E5 1C 00 80 E2 03 00 5C E3 0C 01 80 30 00 00 90 E5 00 C0 90 E5 01 00 5C E1", [this](memory::handle handle)
		{
			m_Sequence_Menu_UpBarController_setTex = handle.as<decltype(m_Sequence_Menu_UpBarController_setTex)>();
		});

		batch.add("Sequence::BaseRacePage::initMapIcon", "4C 16 90 E5 00 00 91 E5 10 30 90 E5 4D 0F 8D E2 33 FF 2F E1 03 0A 88 E2 4D 1F 8D E2", [this](memory::handle handle)
		{
			m_Sequence_BaseRacePage_initMapIcon = handle.sub(0x4C).as<decltype(m_Sequence_BaseRacePage_initMapIcon)>();
		});
		
		batch.add("Course Vote List Set Texture", "F8 40 2D E9 00 50 A0 E1 09 00 51 E3 01 00 A0 E1 0A 00 50 13 02 40 A0 E1 04 00 00 0A 00 00 8D E5", [this](memory::handle handle)
		{
			m_CourseVoteListSetTexture = handle.as<decltype(m_CourseVoteListSetTexture)>();
		});

		batch.add("Sequence::MenuWiFi_Confirm::onPageEnter", "F0 4F 2D E9 00 50 A0 E1 94 D0 4D E2 ? ? ? E5 10 00 94 E5 1E 0E 80 E2", [this](memory::handle handle)
		{
			m_Sequence_MenuWiFi_Confirm_onPageEnter = handle.as<decltype(m_Sequence_MenuWiFi_Confirm_onPageEnter)>();
		});

		batch.add("Net::NetworkStationBufferManager::isDisconnected", "01 00 71 E3 09 00 00 0A 7C 20 90 E5 80 00 90 E5 01 00 52 E1 81 10 81 80 01 01 80 80 00 00 90 E5", [this](memory::handle handle)
		{
			is_disconnected = handle.as<decltype(is_disconnected)>();
		});

		batch.add("Kart::Vehicle::calcMove", "F8 4F 2D E9 00 40 A0 E1 01 50 A0 E1 02 60 A0 E1 30 0C 90 E5 01 02 10 E3", [this](memory::handle handle)
		{
			m_Kart_Vehicle_calcMove = handle.as<decltype(m_Kart_Vehicle_calcMove)>();
		});

		batch.add("RaceSys::GetRaceInfo", "1C 00 90 E5 1C 00 90 E5 BC 01 90 E5 64 00 80 E2 1E FF 2F E1", [this](memory::handle handle)
        {
            get_race_info = handle.sub(0x28).as<decltype(get_race_info)>();
        });

		batch.add("Kart::Camera::calcApply", "F0 41 2D E9 00 40 A0 E1 01 70 A0 E1 06 8B 2D ED 50 D0 4D E2 D4 00 D0 E5 00 00 50 E3", [this](memory::handle handle)
		{
			m_Kart_Camera_calcApply = handle.as<decltype(m_Kart_Camera_calcApply)>();
		});

		batch.add("Kart::InfoProxy::InfoProxy", "1C 00 90 E5 10 00 90 E5 ? ? ? EB 00 00 84 E5 04 00 A0 E1 10 80 BD E8", [this](memory::handle handle)
		{
			kart_info_proxy = handle.sub(0x30).as<decltype(kart_info_proxy)>();
		});

		batch.add("Item::ItemDirector::slot_StartSlot", "F0 47 2D E9 00 40 A0 E1 01 50 A0 E1 02 70 A0 E1", [this](memory::handle handle)
		{
			m_Item_ItemDirector_slot_StartSlot = handle.as<decltype(m_Item_ItemDirector_slot_StartSlot)>();
		});

		batch.add("Effect::KartEffect::_calcCameraEffectImpl", "FC 01 94 E5 00 00 90 E5 9C 2F 90 E5 00 00 52 E3 03 00 00 DA", [this](memory::handle handle)
		{
			m_Effect_KartEffect_calcCameraEffectImpl = handle.sub(0x24).as<decltype(m_Effect_KartEffect_calcCameraEffectImpl)>();
		});

		batch.add("Effect::KartEffect::_calcEnvEffect", "F0 4F 2D E9 00 60 A0 E1 34 D0 4D E2 FC 01 90 E5 00 00 90 E5 A1 10 D0 E5", [this](memory::handle handle)
		{
			m_Effect_KartEffect_calcEnvEffect = handle.as<decltype(m_Effect_KartEffect_calcEnvEffect)>();
		});

		batch.add("Effect::KartEffect::createGessoTrig", "10 40 2D E9 00 40 A0 E1 14 00 90 E5 10 D0 4D E2 23 00 50 E3", [this](memory::handle handle)
		{
			m_Effect_KartEffect_createGessoTrig = handle.as<decltype(m_Effect_KartEffect_createGessoTrig)>();
		});

		batch.add("Effect::KartEffect::createWaterOutTrig", "10 40 2D E9 FC 11 90 E5 ? ? 9F E5 00 10 91 E5 16 0A 92 ED", [this](memory::handle handle)
		{
			m_Effect_KartEffect_createWaterOutTrig = handle.as<decltype(m_Effect_KartEffect_createWaterOutTrig)>();
		});

		batch.add("Sequence::BaseRacePage::drawItemIcon", "9C 12 94 E5 1C 00 90 E5 02 00 51 E1 20 80 90 E5 0E 00 00 1A", [this](memory::handle handle)
		{
			m_Sequence_BaseRacePage_drawItemIcon = handle.sub(0x34).as<decltype(m_Sequence_BaseRacePage_drawItemIcon)>();
		});

		batch.add("Kart::Vehicle::startFadeOut", "10 40 2D E9 00 40 A0 E1 ? ? ? EB ? ? 9F E5 10 00 90 E5 1E 0E 80 E2 50 10 D0 E5 00 00 51 E3 4C 00 90 15", [this](memory::handle handle)
		{
			m_Kart_Vehicle_startFadeOut = handle.as<decltype(m_Kart_Vehicle_startFadeOut)>();
		});

		batch.add("RaceSys::ModeManagerBase::calc", "00 50 A0 E3 94 50 84 E5 18 20 D4 E5 04 00 A0 E3 01 10 A0 E3 19 20 C4 E5 18 00 C4 E5", [this](memory::handle handle)
		{
			m_Demo_DemoCameraDirector_startGoalDemo = handle.sub(0x14).as<decltype(m_Demo_DemoCameraDirector_startGoalDemo)>();
		});

		batch.add("Sequence::MenuTitle::onPageEnter", "F0 47 2D E9 00 40 A0 E1 28 D0 4D E2 E4 72 9F E5", [this](memory::handle handle)
		{
			m_Sequence_MenuTitle_onPageEnter = handle.as<decltype(m_Sequence_MenuTitle_onPageEnter)>();
		});

		batch.add("Item::ItemDirector::_itemEventRecvHandler", "F0 4F 2D E9 00 40 A0 E1 01 80 A0 E1 00 90 A0 E3", [this](memory::handle handle)
		{
			m_Item_ItemDirector_itemEventRecvHandler = handle.as<decltype(m_Item_ItemDirector_itemEventRecvHandler)>();
		});

		batch.add("System::KDPadDirector::calc", "F0 41 2D E9 84 10 D0 E5 00 00 51 E3 02 00 00 0A 86 10 D0 E5 00 00 51 E3", [this](memory::handle handle)
		{
			m_System_KDPadDirector_calc = handle.as<decltype(m_System_KDPadDirector_calc)>();
		});

		batch.add("Kart::NetData::read", "70 40 2D E9 00 00 51 E3 02 50 A0 E1 0C 20 91 15 03 40 A0 E1 00 00 52 13", [this](memory::handle handle)
		{
			m_Kart_NetData_read = handle.as<decltype(m_Kart_NetData_read)>();
		});
		
		batch.run(memory::ranges::c_text);
		
		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}