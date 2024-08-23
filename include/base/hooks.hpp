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
	};
}