#include <hooking.hpp>

#include <base/features.hpp>

namespace base
{
    void    hooks::Kart_Camera_calcApply(Kart::Camera *_this, float unk0, bool unk1, float unk2, float unk3)
    {
        features::change_target(_this);

        features::swap_camera(_this);

        features::change_camera(_this);

        g_hooking->m_Kart_Camera_calcApply_hook.call_original<void>(_this, unk0, unk1, unk2, unk3);
    }
}