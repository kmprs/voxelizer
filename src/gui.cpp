#include "gui.hpp"

float my_float;
float rgb[3] = {0.4, 0.3, 0.7};

GUI::GUI( SDL_Window* window, SDL_GLContext glContext ) :
        m_window( window ), m_context( glContext )
{

}

void GUI::createFrame( float width, float height, int x, int y )
{
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Extra Window");
    ImGui::Text("my label");
    ImGui::SliderFloat("My slider", &my_float, 10.f, 1000.f);
    ImGui::ColorPicker3("Voxel color", rgb);
    ImGui::End();
}


