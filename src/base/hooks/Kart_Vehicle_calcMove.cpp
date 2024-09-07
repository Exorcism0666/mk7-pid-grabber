#include <hooking.hpp>

namespace base
{
    void    hooks::Kart_Vehicle_calcMove(Kart::Vehicle *_this, bool unk0, bool unk1)
    {
        features::change_to_ai(_this);

        g_hooking->m_Kart_Vehicle_calcMove_hook.call_original<void>(_this, unk0, unk1);
    }
}