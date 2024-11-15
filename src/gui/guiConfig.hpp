#pragma once

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/implot/implot.h"


namespace colors
{
    constexpr ImVec4 WINDOW_BG                   = { .110f, .110f, .110f, 1.f };
    constexpr ImVec4 TITLE_BG                    = { .130f, .140f, .130f, 1.f };
    constexpr ImVec4 TITLE_BG_ACTIVE             = { .160f, .170f, .160f, 1.f };
    constexpr ImVec4 FRAME_BG                    = { .190f, .200f, .190f, 1.f };
    constexpr ImVec4 FRAME_BG_HOVERED            = { .230f, .240f, .230f, 1.f };
    constexpr ImVec4 FRAME_BG_ACTIVE             = { .280f, .300f, .280f, 1.f };
    constexpr ImVec4 BUTTON                      = { .160f, .170f, .160f, 1.f };
    constexpr ImVec4 BUTTON_HOVERED              = { .210f, .220f, .210f, 1.f };
    constexpr ImVec4 BUTTON_ACTIVE               = { .260f, .270f, .260f, 1.f };
    constexpr ImVec4 HEADER                      = { .130f, .140f, .130f, 1.f };
    constexpr ImVec4 HEADER_HOVERED              = { .190f, .200f, .190f, 1.f };
    constexpr ImVec4 HEADER_ACTIVE               = { .250f, .270f, .250f, 1.f };
    constexpr ImVec4 SLIDER_GRAB                 = { .550f, .600f, .550f, 1.f };
    constexpr ImVec4 SLIDER_GRAB_ACTIVE          = { .650f, .700f, .650f, 1.f };
    constexpr ImVec4 BUTTON_SUBMIT_DEFAULT_COLOR = { .040f, .230f, .140f, 1.f };
    constexpr ImVec4 BUTTON_SUBMIT_HOVER_COLOR   = { .060f, .320f, .200f, 1.f };
    constexpr ImVec4 BUTTON_SUBMIT_ACTIVE_COLOR  = { .080f, .400f, .260f, 1.f };
    constexpr ImVec4 BUTTON_DELETE_HOVER_COLOR   = { .430f, .120f, .100f, 1.f };
    constexpr ImVec4 BUTTON_DELETE_ACTIVE_COLOR  = { .620f, .160f, .130f, 1.f };
}

namespace distances
{
    constexpr ImVec2 WINDOW_PADDING     = { 10.f, 10.f };
    constexpr ImVec2 FRAME_PADDING      = {  5.f,  5.f };
    constexpr ImVec2 ITEM_SPACING       = { 10.f, 10.f };
    constexpr ImVec2 ITEM_INNER_SPACING = {  8.f,  6.f };
    constexpr float SCROLLBAR_SIZE      = 12.f;
    constexpr float FRAME_ROUNDING      = 8.f;
    constexpr float GRAB_ROUNDING       = 4.f;
}

namespace plot
{
    constexpr ImPlotScale_ SCALE_TYPE         = ImPlotScale_Log10;
    constexpr ImPlotLocation_ LEGEND_LOCATION = ImPlotLocation_NorthWest;
    constexpr float LINE_WEIGHT               = 2.f;
}
