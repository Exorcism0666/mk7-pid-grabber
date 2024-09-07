#include <base/hooking.hpp>

#include <base/features.hpp>

namespace base
{
    bool hooks::Item_ItemDirector_itemEventRecvHandler(void *_this, Net::NetworkItemEventDataMgr::SlotData *data)
    {
        if (features::check_item_event(data))
            return true;

        return g_hooking->m_Item_ItemDirector_itemEventRecvHandler_hook.call_original<bool>(_this, data);
    }
}