#include <base/hooking.hpp>

#include <base/features.hpp>

namespace base
{
    bool    hooks::Kart_NetData_read(void *_this, void *buffer, Kart::NetData **data, Kart::NetData **swap)
    {
        auto result = g_hooking->m_Kart_NetData_read_hook.call_original<bool>(_this, buffer, data, swap);

        if (result)
            features::lag_elimination(*data);

        return result;
    }
}