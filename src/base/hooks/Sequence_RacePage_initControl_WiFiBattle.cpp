#include <base/hooking.hpp>

namespace base
{
    void hooks::Sequence_RacePage_initControl_WiFiBattle(void *_this)
    {
        g_hooking->m_Sequence_RacePage_initControl_WiFiBattle_hook.call_original<void>(_this);

        features::spectator_rankboard(_this);
    }
}