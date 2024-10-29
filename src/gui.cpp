#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;
static int resolution = INIT_RESOLUTION;

GUI::GUI()
{
}



void GUI::createFrame( float width, float height, int x, int y )
{
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    // LEFT FRAME
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGui::Begin( "Left GUI", nullptr, window_flags );

    const char* currentRepresentation = ( dataHandler->getModelRepresentation() == VOXEL )
                                        ? "Voxel" : "Triangle";
    float buttonWidth = width - 20.f;

    ImGui::Text( "Triangle/Voxel" );
    if ( ImGui::Button( currentRepresentation, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleModelRepresentation();
    }
    ImGui::Spacing();

    // VOXEL RESOLUTION
    ImGui::Text( "Voxel Resolution" );
    int temp = resolution;
    ImGui::PushItemWidth( buttonWidth );
    if ( ImGui::SliderInt( "", &resolution, 1, 10 )) {};
    if ( ImGui::IsItemDeactivatedAfterEdit())
    {
        dataHandler->setVoxelResolution( resolution );
    }
    ImGui::Spacing();

    // VOXEL COLOR
    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = { voxelColor.x, voxelColor.y, voxelColor.z };
    ImGui::Text( "Voxel Color" );
    ImGui::ColorEdit3( "##hiddenLabel", rgb );  // Simplified color picker
    dataHandler->setVoxelColor( { rgb[0], rgb[1], rgb[2] });

    // CAMERA MODE
    const char* cameraMode = ( dataHandler->getCameraMode() == CENTERED )
                             ? "centered" : "free";
    ImGui::Text( "Camera Mode" );
    if ( ImGui::Button( cameraMode, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleCameraMode();
    }
    ImGui::Spacing();

    // CAMERA SPEED
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
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width, static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Right GUI", nullptr, window_flags );
    ImGui::End();

    // BOTTOM BAR - PERFORMANCE DATA
    if ( !dataHandler->isWindowFreezed() )
    {
        float performanceHeight = 30.f;
        ImGui::SetNextWindowPos( ImVec2( width,
                                         static_cast<float>(dataHandler->getWindowHeight()) -
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
}

void GUI::setStyles()
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../binaries/arial_narrow.ttf", 16.0f);
    io.FontDefault = io.Fonts->Fonts.back();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(5, 5);
    style.ItemSpacing = ImVec2(10, 10);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.ScrollbarSize = 12;

    style.WindowRounding = 6.0f;
    style.FrameRounding = 8.0f;
    style.GrabRounding = 4.0f;

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);

    ImGui::GetIO().FontGlobalScale = 1.f;
}
