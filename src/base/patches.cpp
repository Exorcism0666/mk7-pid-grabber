#include <base/patches.hpp>

#include <base/memory/handle.hpp>
#include <base/pointers.hpp>

namespace base
{
    patches::patches()
    :
        m_disable_right_eye_rendering(reinterpret_cast<void *>((u32)g_pointers->m_System_ProjectGameFramework_procDraw + 0xC8), { 0x07, 0x00, 0x00, 0xEA }),
        m_uncap_bottom_screen_frames(reinterpret_cast<void *>((u32)g_pointers->m_System_ProjectGameFramework_procFrame + 0xE4), { 0x01, 0x00, 0xA0, 0xE3 }),
        m_disable_3d_slider_effect(memory::handles::ctrpf_shared_hid_mem.add(0x84).as<void *>(), { 0x01 }),
        m_render_mii_face_0(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x128), { 0x09, 0x00, 0xA0, 0xE3 }),
        m_render_mii_face_1(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x168), { 0x09, 0x00, 0xA0, 0xE3 }),
        m_render_mii_face_2(reinterpret_cast<void *>((u32)g_pointers->m_Mii_MiiEngine_createMiiFace + 0x6D0), { 0x0B, 0x00, 0x00, 0xEA }),
        m_mii_face_on_votes_0(reinterpret_cast<void *>((u32)g_pointers->m_CourseVoteListSetTexture + 0x18), { 0x04, 0x00, 0x00, 0xEA }),
        m_mii_face_on_votes_1(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_Menu_UpBarController_setTex + 0x30), { 0x09, 0x10, 0xA0, 0xE3 }),
        m_mii_face_on_minimap(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_BaseRacePage_initMapIcon + 0x584), { 0x09, 0x00, 0xA0, 0xE3 })
    {
        g_patches = this;
    }

    patches::~patches()
    {
        g_patches = nullptr;
    }
}