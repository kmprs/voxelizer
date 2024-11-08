#include "benchmarkGui.hpp"


void
BenchmarkGUI::createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                           float height, int x,
                           int y )
{
    ImGui::SetCurrentContext(imGuiContext);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    float buttonWidth = width - 20;

    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGui::Begin( "BenchmarkGUI", nullptr, window_flags );

    ImGui::Text("Hello World!");

    ImGui::End();
}

