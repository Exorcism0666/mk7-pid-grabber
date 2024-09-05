#include <hooking.hpp>

#include <base/features.hpp>

namespace base
{
    void    hooks::Item_ItemDirector_slot_StartSlot(void *_this, u8 player_id, u8 unk0)
    {
        if (features::block_item(player_id))
            return;
        
        g_hooking->m_Item_ItemDirector_slot_StartSlot_hook.call_original<void>(_this, player_id, unk0);
    }
}