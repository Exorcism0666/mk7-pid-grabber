#pragma once

#include <base/memory/patch.hpp>
#include <base/types.hpp>

namespace base
{
    class patches
    {
    public:
        explicit patches();
        ~patches();

        memory::patch<u32> m_disable_right_eye_rendering;
        memory::patch<u32> m_uncap_bottom_screen_frames;
        memory::patch<u8> m_disable_3d_slider;

        memory::patch<u32> m_render_mii_head_0;
        memory::patch<u32> m_render_mii_head_1;
        memory::patch<u32> m_render_mii_head_2;
        memory::patch<u32> m_mii_head_on_votes_0;
        memory::patch<u32> m_mii_head_on_votes_1;
        memory::patch<u32> m_mii_head_on_minimap;

        memory::patch<u32> m_items_on_extended_map_0;
        memory::patch<u32> m_items_on_extended_map_1;
        
        memory::patch<u32> m_disable_oob_camera;
        memory::patch<u32> m_disable_fade_out_0;
        memory::patch<u32> m_disable_fade_out_1;
        memory::patch<u32> m_disable_goal_demo;
        memory::patch<u32> m_disable_title_demo;
    };

    inline patches *g_patches{};
}