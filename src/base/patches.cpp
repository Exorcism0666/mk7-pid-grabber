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
        m_mii_head_on_minimap(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_BaseRacePage_initMapIcon + 0x584), { 0xE3A00009 }),
        m_items_on_extended_map_0(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_BaseRacePage_drawItemIcon + 0x44), { 0 }),
        m_items_on_extended_map_1(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_BaseRacePage_drawItemIcon + 0x28C), { 0 }),
        m_disable_oob_camera(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcApply + 0x11B4), { 0xE3A01000 }),
        m_disable_fade_out_0(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Vehicle_calcMove + 0x310), { 0 }),
        m_disable_fade_out_1(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Vehicle_startFadeOut), { 0xE12FFF1E }),
        m_disable_goal_demo(reinterpret_cast<void *>((u32)g_pointers->m_Demo_DemoCameraDirector_startGoalDemo), { 0xE12FFF1E }),
        m_disable_title_demo(reinterpret_cast<void *>((u32)g_pointers->m_Sequence_MenuTitle_onPageEnter + 0x98), { 0xE3A00000 }),
        m_disable_fpv(reinterpret_cast<void *>((u32)g_pointers->m_System_KDPadDirector_calc + 0xEC), { 0xE3A01000 }),
        m_disable_fog(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcApply + 0x770), { 0xE3A01000 }),
        m_fix_camera_draw_0(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcDraw + 0x8A4), { 0xE3A01000 }),
        m_fix_camera_draw_1(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcDraw + 0xC04), { 0xE3A00000 }),
        m_disable_blooper_0(reinterpret_cast<void *>((u32)g_pointers->m_Item_ItemObjGesso_stateAttacked + 0x148), { 0xE3A00000 }),
        m_disable_blooper_1(reinterpret_cast<void *>((u32)g_pointers->m_Item_ItemObjGesso_stateInitAttacked + 0xC), { 0xE3A00001 }),
        m_load_course_model(reinterpret_cast<void *>((u32)g_pointers->m_nw_gfx_RenderContext_RenderPrimitive + 0xD0), { 0xE3A01001 }),
        m_disable_item_on_x(reinterpret_cast<void *>((u32)g_pointers->m_Item_ItemDirector_calcKeyInput_EachPlayer + 0x80), { 0 }),
        m_disable_camera_fade(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcGndEvade + 0xFB8), { 0 }),
        m_force_default_camera(reinterpret_cast<void *>((u32)g_pointers->m_Kart_Camera_calcApply + 0x240), { 0xE3A01000 })
    {
        g_patches = this;
    }

    patches::~patches()
    {
        g_patches = nullptr;
    }
}