#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


void GUI::setStyles()
{
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF( "../binaries/arial.ttf", 16.0f );
    io.FontDefault = io.Fonts->Fonts.back();

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowPadding = ImVec2( 10, 10 );
    style.FramePadding = ImVec2( 5, 5 );
    style.ItemSpacing = ImVec2( 10, 10 );
    style.ItemInnerSpacing = ImVec2( 8, 6 );
    style.ScrollbarSize = 12;

    style.FrameRounding = 8.0f;
    style.GrabRounding = 4.0f;

    style.Colors[ImGuiCol_WindowBg] = ImVec4( 0.1f, 0.1f, 0.1f, 1.0f ); // Dark background
    style.Colors[ImGuiCol_TitleBg] = ImVec4( 0.16f, 0.16f, 0.16f, 1.0f );
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4( 0.2f, 0.2f, 0.2f, 1.0f );
    style.Colors[ImGuiCol_FrameBg] = ImVec4( 0.2f, 0.2f, 0.2f, 1.0f );
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4( 0.25f, 0.25f, 0.25f, 1.0f );
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4( 0.35f, 0.35f, 0.35f, 1.0f );
    style.Colors[ImGuiCol_Button] = ImVec4( 0.15f, 0.15f, 0.15f, 1.0f );
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4( 0.25f, 0.25f, 0.25f, 1.0f );
    style.Colors[ImGuiCol_ButtonActive] = ImVec4( 0.35f, 0.35f, 0.35f, 1.0f );
    style.Colors[ImGuiCol_Header] = ImVec4( 0.15f, 0.15f, 0.15f, 1.0f );
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4( 0.25f, 0.25f, 0.25f, 1.0f );
    style.Colors[ImGuiCol_HeaderActive] = ImVec4( 0.35f, 0.35f, 0.35f, 1.0f );
    style.Colors[ImGuiCol_SliderGrab] = ImVec4( 0.7f, 0.7f, 0.7f, 1.0f );
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4( 0.8f, 0.8f, 0.8f, 1.0f );

    ImGui::GetIO().FontGlobalScale = 1.f;
}

