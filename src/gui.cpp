#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;
static int resolution = INIT_RESOLUTION;

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

void GUI::createFrame( float width, float height, int x, int y )
{
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    float buttonWidth = width - 20;

    // LEFT FRAME
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Left GUI", nullptr, window_flags );

    buttonRepresentation( buttonWidth );
    ImGui::Spacing();

    collapseAlgorithmSelection();
    ImGui::Spacing();

    sliderVoxelResolution( buttonWidth );
    ImGui::Spacing();

    colorPickerVoxel();
    ImGui::Spacing();

    buttonCameraMode( buttonWidth );
    ImGui::Spacing();

    numberInputCameraSpeed();
    ImGui::Spacing();

    numberInputRotationSpeed();
    ImGui::Spacing();

    ImGui::End();

    // RIGHT FRAME
    ImGui::SetNextWindowPos(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width,
                    static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Right GUI", nullptr, window_flags );



    ImGui::End();

//     BOTTOM BAR - PERFORMANCE DATA
    float performanceHeight = 30.f;
    ImGui::SetNextWindowPos( ImVec2( width,
                                     static_cast<float>(dataHandler->getWindowHeight()) -
                                     performanceHeight ));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - 2 * width,
                    performanceHeight ));

    // Bug in ImGui causes trembling effects if noBackgroundOption is used
    ImGui::PushStyleColor(ImGuiCol_WindowBg,
                          ImVec4(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y,
                                 BACKGROUND_COLOR.z, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin( "Performance stats", nullptr,
                  window_flags | ImGuiWindowFlags_NoScrollbar);
    if ( !dataHandler->isWindowFreezed()) showPerformanceData();
    else ImGui::Text("-- HOLD --");
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void GUI::buttonRepresentation( float buttonWidth )
{
    const char* currentRepresentation = ( dataHandler->getModelRepresentation() == VOXEL )
                                        ? "Voxel" : "Triangle";
    ImGui::Text( "Triangle/Voxel" );
    if ( ImGui::Button( currentRepresentation, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleModelRepresentation();
    }
}

void GUI::collapseAlgorithmSelection()
{
// ALGORITHM SELECTION
    static bool isVoxelizationMenuOpen = false;
    const char* labels[] = { "Optimized Voxelizer", "Naive Voxelizer", "Octree Voxelizer",
                             "BVH Voxelizer" };

    int selectedIndex = static_cast<int>(dataHandler->getVoxelizationAlgorithm());
    std::string title = std::string( labels[selectedIndex] ) + " ";

    ImGui::Text( "Voxelization Method" );
    ImGui::SetNextItemOpen( isVoxelizationMenuOpen );

    if ( ImGui::CollapsingHeader( title.c_str()))
    {
        isVoxelizationMenuOpen = true;

        for ( int i = 0; i < 4; ++i )
        {
            if ( ImGui::Selectable( labels[i], selectedIndex == i ))
            {
                dataHandler->setAlgorithm( static_cast<VoxelizationAlgorithm>(i));
                isVoxelizationMenuOpen = false;
                break;
            }
        }
    }
}

void GUI::sliderVoxelResolution( float buttonWidth )
{
    // VOXEL RESOLUTION
    ImGui::Text( "Voxel Resolution" );
    ImGui::PushItemWidth( buttonWidth );
    if ( ImGui::SliderInt( "", &resolution, 1, 10 ))
    {};
    if ( ImGui::IsItemDeactivatedAfterEdit())
    {
        dataHandler->setVoxelResolution( resolution );
    }
}

void GUI::colorPickerVoxel()
{
    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = { voxelColor.x, voxelColor.y, voxelColor.z };
    ImGui::Text( "Voxel Color" );
    ImGui::ColorEdit3( "", rgb );
    dataHandler->setVoxelColor( { rgb[0], rgb[1], rgb[2] } );
}

void GUI::buttonCameraMode( float buttonWidth )
{
    const char* cameraMode = ( dataHandler->getCameraMode() == CENTERED )
                             ? "centered" : "free";
    ImGui::Text( "Camera Mode" );
    if ( ImGui::Button( cameraMode, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleCameraMode();
    }
}

void GUI::numberInputCameraSpeed()
{
    float speed = dataHandler->getCameraSpeed();
    ImGui::Text( "Camera Speed" );
    ImGui::InputFloat( "##camera speed", &speed, 1.f, 1.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setCameraSpeed( speed );
}

void GUI::numberInputRotationSpeed()
{
    static float speed = dataHandler->getRotationSpeed();
    ImGui::Text( "Rotation Speed" );
    ImGui::InputFloat( "##rotation_speed", &speed, 10.f, 10.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setRotationSpeed( speed );
}

void GUI::showPerformanceData()
{
    ImGui::Text( "%d FPS", dataHandler->getCurrentFPS());
    ImGui::SameLine();
    ImGui::Text( "%d voxels", dataHandler->getNumberOfVoxels());
    ImGui::SameLine();
}



