#include <base/hooking.hpp>

namespace base
{
    void hooks::Sequence_RacePage_initControl_WiFiVS(void *_this)
    {
        g_hooking->m_Sequence_RacePage_initControl_WiFiVS_hook.call_original<void>(_this);

        features::load_rankboard(_this);
    }
}