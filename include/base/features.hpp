#pragma once

#include <base/utilities.hpp>
#include <base/types.hpp>

namespace base
{
	struct features
	{
		static void load_rankboard(void *);
		static void clean_principal_id();
		static void dump_session();
		static void change_to_ai(Kart::Vehicle *);
		static void swap_camera(Kart::Camera *);
		static bool block_item(u8);
		static bool ignore_effect(Effect::KartEffect *);
		static void change_target(Kart::Camera *);
		static bool ignore_vehicle(Kart::Vehicle *);
		static bool check_item_event(Net::NetworkItemEventDataMgr::SlotData *);
		static void lag_elimination(Kart::NetData *);
	};
}