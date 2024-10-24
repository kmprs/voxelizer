#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;

GUI::GUI( SDL_Window* window, SDL_GLContext glContext ) :
        m_window( window ), m_context( glContext )
{
    // style settings
    ImGuiStyle &style = ImGui::GetStyle();

}

void GUI::createFrame( float width, float height, int x, int y )
{
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Extra Window");

    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = {voxelColor.x, voxelColor.y, voxelColor.z};
    ImGui::Text("Voxel Color");
    ImGui::ColorPicker3("##hiddenLabel", rgb);
    ImGui::Spacing();
    dataHandler->setVoxelColor({rgb[0], rgb[1], rgb[2]});


    // camera and rotation speeds
    float speed = dataHandler->getCameraSpeed();
    ImGui::Text("Camera Speed");
    ImGui::InputFloat("##hiddenLabel", &speed, 1.f, 1.f, "%.1f");
    ImGui::Spacing();
    dataHandler->setCameraSpeed(speed);

    ImGui::End();
}


