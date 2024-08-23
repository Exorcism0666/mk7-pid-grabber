#pragma once

#include <base/utilities.hpp>
#include <base/types.hpp>

namespace base
{
	struct features
	{
		static void spectator_rankboard(void *);
		static void clean_principal_id();
		static void dump_session();
		static void change_to_ai(Kart::Vehicle *);
	};
}