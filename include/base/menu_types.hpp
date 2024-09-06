#pragma once

#include <ctrpf/MenuEntryHelpers.hpp>
#include <base/types.hpp>

namespace base::menu_types
{
    struct spectator_mode
    {
        bool active;
        bool is_set;
        bool pending;
        u8 target_id;
    };
}