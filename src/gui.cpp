#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;
static int resolution = INIT_RESOLUTION;

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
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;


    // LEFT FRAME
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGui::Begin( "Left GUI", nullptr, window_flags );
    // TRIANGLE/ VOXEL REPRESENTATION
    const char* currentRepresentation = ( dataHandler->getModelRepresentation() == VOXEL )
                                        ? "Voxel" : "Triangle";
    float buttonWidth = width - 20.f;
    ImGui::Text( "Triangle/Voxel" );
    if ( ImGui::Button( currentRepresentation, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleModelRepresentation();
    }
    ImGui::Spacing();

    // VOXEL RESOlUTION
    ImGui::Text( "Voxel Resolution" );
    int temp = resolution;
    ImGui::PushItemWidth( buttonWidth );
    if ( ImGui::SliderInt( "", &resolution, 1, 10 ))
    {};
    if ( ImGui::IsItemDeactivatedAfterEdit())
    {
        dataHandler->setVoxelResolution( resolution );
    }
    ImGui::Spacing();

    // VOXEL COLOR
    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = { voxelColor.x, voxelColor.y, voxelColor.z };
    ImGui::Text( "Voxel Color" );
    ImGui::ColorPicker3( "##hiddenLabel", rgb );
    ImGui::Spacing();
    dataHandler->setVoxelColor( { rgb[0], rgb[1], rgb[2] } );

    // CAMERA MODE
    const char* cameraMode = ( dataHandler->getCameraMode() == CENTERED )
                                        ? "centered" : "free";
    ImGui::Text( "Camera Mode" );
    if ( ImGui::Button( cameraMode, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleCameraMode();
    }
    ImGui::Spacing();

    // CAMERA AND ROTATION SPEED
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


    // RIGHT FRAME
    ImGui::SetNextWindowPos(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width,
                    static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Right GUI", nullptr, window_flags );
    ImGui::End();

    // bottom bar for performance data
    float performanceHeight = 30.f;
    ImGui::SetNextWindowPos(
            ImVec2( width, static_cast<float>(dataHandler->getWindowHeight()) -
                           performanceHeight ));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - 2 * width,
                    performanceHeight ));
    ImGui::Begin( "Performance stats", nullptr,
                  window_flags | ImGuiWindowFlags_NoBackground );
    ImGui::Text( "%d FPS", dataHandler->getCurrentFPS());
    ImGui::SameLine();
    ImGui::Text( "%d voxels", dataHandler->getNumberOfVoxels());
    ImGui::End();
}


