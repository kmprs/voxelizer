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
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImGui::Begin( "Left GUI", nullptr, window_flags );

    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = { voxelColor.x, voxelColor.y, voxelColor.z };
    ImGui::Text( "Voxel Color" );
    ImGui::ColorPicker3( "##hiddenLabel", rgb );
    ImGui::Spacing();
    dataHandler->setVoxelColor( { rgb[0], rgb[1], rgb[2] } );


    // camera and rotation speeds
    float speed = dataHandler->getCameraSpeed();
    ImGui::Text( "Camera Speed" );
    ImGui::InputFloat( "##camera speed", &speed, 1.f, 1.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setCameraSpeed( speed );

    speed = dataHandler->getRotationSpeed();
    ImGui::Text( "Rotation Speed" );
    ImGui::InputFloat( "##rotation speed", &speed, 10.f, 10.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setRotationSpeed( speed );

    ImGui::End();


    // left frame
    ImGui::SetNextWindowPos(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width,
                    static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Right GUI", nullptr, window_flags );
    ImGui::End();

    // bottom bar for performance data
    float performanceHeight = 30.f;
    ImGui::SetNextWindowPos(
            ImVec2( width, static_cast<float>(dataHandler->getWindowHeight()) - performanceHeight ));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - 2 * width, performanceHeight ));
    ImGui::Begin( "Performance stats", nullptr, window_flags | ImGuiWindowFlags_NoBackground );
    ImGui::Text("FPS: %d", dataHandler->getCurrentFPS());
    ImGui::End();
}


