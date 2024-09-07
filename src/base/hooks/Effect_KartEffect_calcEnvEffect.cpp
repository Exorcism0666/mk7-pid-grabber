#include <hooking.hpp>

#include <base/features.hpp>

namespace base
{
    void    hooks::Effect_KartEffect_calcEnvEffect(Effect::KartEffect *_this)
    {
        if (features::ignore_effect(_this))
            return;
        
        g_hooking->m_Effect_KartEffect_calcEnvEffect_hook.call_original<void>(_this);
    }
}