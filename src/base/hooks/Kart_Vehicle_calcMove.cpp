#include <hooking.hpp>

namespace base
{
    void    hooks::Kart_Vehicle_calcMove(Kart::Vehicle *_this, bool unk1, bool unk2)
    {
        features::change_to_ai(_this);

        g_hooking->m_Kart_Vehicle_calcMove_hook.call_original<void>(_this, unk1, unk2);
    }
}