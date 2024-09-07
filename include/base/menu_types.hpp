#pragma once

#include <ctrpf/MenuEntryHelpers.hpp>
#include <base/types.hpp>

namespace base::menu_types
{
    struct spectator_mode
    {
        bool active;
        bool reset;
        bool pending;
        u8 target_id;
    };
}