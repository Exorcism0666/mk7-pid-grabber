#include <base/patches.hpp>

#include <base/memory/handle.hpp>
#include <base/pointers.hpp>

namespace base
{
    patches::patches()
    :
        m_disable_right_eye_rendering(reinterpret_cast<void *>((u32)g_pointers->m_System_ProjectGameFramework_procDraw + 0xC8), { 0xEA000007 }),
        m_uncap_bottom_screen_frames(reinterpret_cast<void *>((u32)g_pointers->m_System_ProjectGameFramework_procFrame + 0xE4), { 0xE3A00001 }),
        m_disable_3d_slider(memory::handles::ctrpf_shared_hid_mem.add(0x84).as<void *>(), { 0x01 }),
        m_render_mii_head_0(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x128), { 0xE3A00009 }),
        m_render_mii_head_1(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x168), { 0xE3A00009 }),
        m_render_mii_head_2(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x6D0), { 0xEA00000B }),
        m_mii_head_on_votes_0(reinterpret_cast<void *>((u32)g_pointers->m_CourseVoteListSetTexture + 0x18), { 0xEA000004 }),
        m_mii_head_on_votes_1(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_Menu_UpBarController_setTex + 0x30), { 0xE3A01009 }),
        m_mii_head_on_minimap(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_BaseRacePage_initMapIcon + 0x584), { 0xE3A00009 })
    {
        g_patches = this;
    }

    patches::~patches()
    {
        g_patches = nullptr;
    }
}