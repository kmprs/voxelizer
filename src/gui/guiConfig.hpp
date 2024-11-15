#pragma once

#include "../../dependencies/imgui/imgui.h"

namespace colors
{
    constexpr ImVec4 WINDOW_BG                   = { 0.10f, 0.10f, 0.10f, 1.0f };
    constexpr ImVec4 TITLE_BG                    = { 0.16f, 0.16f, 0.16f, 1.0f };
    constexpr ImVec4 TITLE_BG_ACTIVE             = { 0.2f, 0.2f, 0.2f, 1.0f };
    constexpr ImVec4 FRAME_BG                    = { 0.2f, 0.2f, 0.2f, 1.0f };
    constexpr ImVec4 FRAME_BG_HOVERED            = { 0.25f, 0.25f, 0.25f, 1.0f };
    constexpr ImVec4 FRAME_BG_ACTIVE             = { 0.35f, 0.35f, 0.35f, 1.0f };
    constexpr ImVec4 BUTTON                      = { 0.15f, 0.15f, 0.15f, 1.0f };
    constexpr ImVec4 BUTTON_HOVERED              = { 0.25f, 0.25f, 0.25f, 1.0f };
    constexpr ImVec4 BUTTON_ACTIVE               = { 0.35f, 0.35f, 0.35f, 1.0f };
    constexpr ImVec4 HEADER                      = { 0.15f, 0.15f, 0.15f, 1.0f };
    constexpr ImVec4 HEADER_HOVERED              = { 0.25f, 0.25f, 0.25f, 1.0f };
    constexpr ImVec4 HEADER_ACTIVE               = { 0.35f, 0.35f, 0.35f, 1.0f };
    constexpr ImVec4 SLIDER_GRAB                 = { 0.7f, 0.7f, 0.7f, 1.0f };
    constexpr ImVec4 SLIDER_GRAB_ACTIVE          = { 0.8f, 0.8f, 0.8f, 1.0f };
    constexpr ImVec4 BUTTON_SUBMIT_DEFAULT_COLOR = { .035f, .239f, .165f, 1.f };
    constexpr ImVec4 BUTTON_SUBMIT_HOVER_COLOR   = { .047f, .349f, .239f, 1.f };
    constexpr ImVec4 BUTTON_SUBMIT_ACTIVE_COLOR  = { .059f, .439f, .302f, 1.f };
    constexpr ImVec4 BUTTON_DELETE_HOVER_COLOR   = { .420f, .071f, .059f, 1.f };
    constexpr ImVec4 BUTTON_DELETE_ACTIVE_COLOR  = { .612f, .102f, .086f, 1.f };
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
