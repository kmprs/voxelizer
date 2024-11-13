#include "mainGui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


void MainGUI::createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                           float height, int x,
                           int y )
{
    ImGui::SetCurrentContext( imGuiContext );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    float buttonWidth = width - 20;

    // LEFT GUI
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

    // RIGHT GUI
    ImGui::SetNextWindowPos(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width,
                    static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::Begin( "Right GUI", nullptr, window_flags );

    buttonFileDialog( buttonWidth );
    ImGui::Spacing();

    ImGui::Text("Selected Voxelization Algorithms");
    for ( VoxelizationAlgorithm a : dataHandler->getBenchmarkAlgorithms() )
    {
        ImGui::Text( "%s", util::toString( a ).c_str() );
    }
    ImGui::Spacing();
    buttonBenchmarkDialog( buttonWidth );
    ImGui::Spacing();

    ImGui::End();

    // BOTTOM BAR - PERFORMANCE DATA
    float performanceHeight = 30.f;
    ImGui::SetNextWindowPos( ImVec2( width,
                                     static_cast<float>(dataHandler->getWindowHeight()) -
                                     performanceHeight ));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - 2 * width,
                    performanceHeight ));

    // Bug in ImGui causes trembling effects if noBackgroundOption is used
    ImGui::PushStyleColor( ImGuiCol_WindowBg,
                           ImVec4( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y,
                                   BACKGROUND_COLOR.z, 1.0f ));
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );

    ImGui::Begin( "Performance stats", nullptr,
                  window_flags | ImGuiWindowFlags_NoScrollbar );
    if ( !dataHandler->isWindowFreezed()) showPerformanceData();
    else ImGui::Text( "-- HOLD --" );
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}


void MainGUI::buttonRepresentation( float buttonWidth )
{
    const char* currentRepresentation = ( dataHandler->getModelRepresentation() == VOXEL )
                                        ? "Voxel##REPRESENTATION"
                                        : "Triangle##REPRESENTATION";
    ImGui::Text( "Triangle/Voxel" );
    if ( ImGui::Button( currentRepresentation, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleModelRepresentation();
    }
}

void MainGUI::collapseAlgorithmSelection()
{
    static bool isCollapsed = false;
    const char* labels[] = { "Optimized Voxelizer",
                             "Naive Voxelizer",
                             "Octree Voxelizer",
                             "BVH Voxelizer" };

    int selectedIndex = static_cast<int>(dataHandler->getVoxelizationAlgorithm());
    std::string title = std::string( labels[selectedIndex] ) + " ";

    ImGui::Text( "Voxelization Method" );
    ImGui::SetNextItemOpen( isCollapsed );

    if ( ImGui::CollapsingHeader( title.c_str()))
    {
        isCollapsed = true;
        for ( int i = 0; i < 4; i++ )
        {
            if ( ImGui::Selectable( labels[i], selectedIndex == i ))
            {
                switch ( i )
                {
                    case 0:
                        dataHandler->setAlgorithm( OPTIMIZED );
                        break;
                    case 1:
                        dataHandler->setAlgorithm( NAIVE );
                        break;
                    case 2:
                        dataHandler->setAlgorithm( OCTREE );
                        break;
                    case 3:
                        dataHandler->setAlgorithm( BVH );
                        break;
                    default:
                        break;
                }
                dataHandler->setAlgorithm( static_cast<VoxelizationAlgorithm>(i));
                isCollapsed = false;
                break;
            }
        }
    } else
    {
        isCollapsed = false;
    }
}

void MainGUI::sliderVoxelResolution( float buttonWidth )
{
    static int resolution = INIT_RESOLUTION;
    // VOXEL RESOLUTION
    ImGui::Text( "Voxel Resolution" );
    ImGui::PushItemWidth( buttonWidth );
    if ( ImGui::SliderInt( "##SLIDERRESOLUTION", &resolution, 1, MAX_RESOLUTION ))
    {};
    if ( ImGui::IsItemDeactivatedAfterEdit())
    {
        dataHandler->setVoxelResolution( resolution );
    }
}

void MainGUI::colorPickerVoxel()
{
    glm::vec3 voxelColor = dataHandler->getVoxelColor();
    float rgb[3] = { voxelColor.x, voxelColor.y, voxelColor.z };
    ImGui::Text( "Voxel Color" );
    ImGui::ColorEdit3( "##COLORPICKER", rgb );
    dataHandler->setVoxelColor( { rgb[0], rgb[1], rgb[2] } );
}

void MainGUI::buttonCameraMode( float buttonWidth )
{
    const char* cameraMode = ( dataHandler->getCameraMode() == CENTERED )
                             ? "centered##CAMERAMODE" : "free##CAMERAMODE";
    ImGui::Text( "Camera Mode" );
    if ( ImGui::Button( cameraMode, ImVec2( buttonWidth, 0 )))
    {
        dataHandler->toggleCameraMode();
    }
}

void MainGUI::numberInputCameraSpeed()
{
    float speed = dataHandler->getCameraSpeed();
    ImGui::Text( "Camera Speed" );
    ImGui::InputFloat( "##CAMERASPEED", &speed, 1.f, 1.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setCameraSpeed( speed );
}

void MainGUI::numberInputRotationSpeed()
{
    static float speed = dataHandler->getRotationSpeed();
    ImGui::Text( "Rotation Speed" );
    ImGui::InputFloat( "##rotation_speed", &speed, 10.f, 10.f, "%.1f" );
    ImGui::Spacing();
    dataHandler->setRotationSpeed( speed );
}

void MainGUI::buttonFileDialog( float buttonWidth )
{
    static bool fileSelected = false;
    IGFD::FileDialogConfig config;
    config.path = BINARY_PATH;

    if ( ImGui::Button( "Import OBJ model##GUI_MODEL", ImVec2( buttonWidth, 0 )))
    {
        fileSelected = false;
        ImGuiFileDialog::Instance()->OpenDialog(
                "OBJFileDialog",
                "Choose an OBJ-File",
                ".obj",
                config );
    }

    ImVec2 minDialogSize = ImVec2(
            static_cast<float>(dataHandler->getWindowWidth()) * .7f,
            static_cast<float>(dataHandler->getWindowHeight()) * .7f
    );
    ImGuiFileDialog::Instance()->Display( "OBJFileDialog", 0, minDialogSize );

    if ( ImGuiFileDialog::Instance()->IsOk() && !fileSelected )
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        dataHandler->setModelPath( filePath );
        fileSelected = true;

        // reset dataHandler members
        dataHandler->setWindowFreeze( false );

        ImGuiFileDialog::Instance()->Close();
    } else if ( !ImGuiFileDialog::Instance()->IsOk() &&
                ImGuiFileDialog::Instance()->cancelPressed )
    {
        ImGuiFileDialog::Instance()->cancelPressed = false;
        ImGuiFileDialog::Instance()->Close();
    }

    std::filesystem::path filePath( dataHandler->getCurrentModelPath());

    ImGui::Text( "current model: %s", filePath.filename().c_str());
}

void MainGUI::buttonBenchmarkDialog( float buttonWidth )
{
    ImGui::Text( "Create Benchmarks" );
    if ( ImGui::Button( "Benchmarks##BENCHMARKS", ImVec2( buttonWidth, 0 )))
    {
        dataHandler->showBenchmarks( true );
    }
}

void MainGUI::showPerformanceData()
{
    ImGui::Text( "%d FPS", dataHandler->getCurrentFPS());
    ImGui::SameLine();
    ImGui::Text( "%d voxels", dataHandler->getNumberOfVoxels());
    ImGui::SameLine();
}


