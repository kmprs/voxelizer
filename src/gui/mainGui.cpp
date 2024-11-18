#include "mainGui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


void MainGUI::createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                           float height, int x, int y )
{
    ImGui::SetCurrentContext( imGuiContext );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    float buttonWidth = width - 20;

    // LEFT GUI
    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    createLeftFrame( windowFlags, buttonWidth );


    // RIGHT GUI
    ImGui::SetNextWindowPos(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - width,
                    static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    createRightFrame( width, windowFlags, buttonWidth );


    // BOTTOM BAR - PERFORMANCE DATA
    float performanceHeight = 30.f;
    ImGui::SetNextWindowPos( ImVec2( width,
                                     static_cast<float>(dataHandler->getWindowHeight()) -
                                     performanceHeight ));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getWindowWidth()) - 2 * width,
                    performanceHeight ));
    createBottomFrame( windowFlags );
}

void MainGUI::createLeftFrame( ImGuiWindowFlags windowFlags, float buttonWidth )
{
    ImGui::Begin( "Left GUI", nullptr, windowFlags );

    buttonRepresentation( buttonWidth );
    ImGui::Spacing();

    ImGui::Text( "Voxelization Method" );
    static bool algorithmSelectionCollapsed = false;
    collapseSelection( { "Optimized", "Octree", "BVH", "Naive" },
                       algorithmSelectionCollapsed,
                       static_cast<int>(dataHandler->getVoxelizationAlgorithm()),
                       "Algorithm", [this]( int index ) {
                dataHandler->setAlgorithm( static_cast<VoxelizationAlgorithm>(index));
            } );
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
}

void
MainGUI::createRightFrame( float width, ImGuiWindowFlags windowFlags, float buttonWidth )
{
    ImGui::Begin( "Right GUI", nullptr, windowFlags );

    buttonFileDialog( buttonWidth );
    ImGui::Spacing();
    ImGui::Spacing();

    static bool addAlgorithmsCollapsed = false;
    collapseSelection( { "Optimized", "Octree", "BVH", "Naive" }, addAlgorithmsCollapsed,
                       -1, "Add algorithm to benchmark", [this]( int index ) {
                dataHandler->addToBenchmark( static_cast<VoxelizationAlgorithm>(index));
            } );
    ImGui::Spacing();

    float deleteButtonWidth = width / 5;
    showSelectedAlgorithmsBenchmark( deleteButtonWidth );
    ImGui::Spacing();

    buttonBenchmarkDialog( buttonWidth );
    ImGui::Spacing();

    static std::chrono::steady_clock::time_point notificationStartTime;
    if ( buttonCreateBenchmarkCSV( {}, "Create CSV", buttonWidth ))
    {
        notificationStartTime = std::chrono::steady_clock::now();
    }
    ImGui::Spacing();

    ImGui::End();

    auto elapsedNotificationTime =
            std::chrono::steady_clock::now() - notificationStartTime;
    if ( std::chrono::duration_cast<std::chrono::seconds>(
            elapsedNotificationTime ).count() < 2 )
    {
        showNotification( "CSV created!",
                          static_cast<float>(dataHandler->getWindowWidth()) - 2 * width,
                          distances::ITEM_SPACING.y, width - distances::ITEM_SPACING.x,
                          60.f );
    }
}

void MainGUI::createBottomFrame( ImGuiWindowFlags windowFlags )
{
    // Bug in ImGui causes trembling effects if noBackgroundOption is used
    ImGui::PushStyleColor( ImGuiCol_WindowBg,
                           ImVec4( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y,
                                   BACKGROUND_COLOR.z, 1.0f ));
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );

    ImGui::Begin( "Performance stats", nullptr,
                  windowFlags | ImGuiWindowFlags_NoScrollbar );
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

void
MainGUI::collapseSelection( const std::vector<std::string> &labels, bool &collapseStatus,
                            int selectedIndex, std::string defaultTitle,
                            const std::function<void( int )> &onSelect )
{
    std::string title = ( selectedIndex >= 0 ) ? labels[selectedIndex] + " " : std::move(
            defaultTitle );

    ImGui::SetNextItemOpen( collapseStatus );

    if ( ImGui::CollapsingHeader( title.c_str()))
    {
        collapseStatus = true;
        for ( int i = 0; i < labels.size(); i++ )
        {
            if ( ImGui::Selectable( labels[i].c_str(), selectedIndex == i ))
            {
                onSelect( i );
                collapseStatus = false;
                break;
            }
        }
    } else
    {
        collapseStatus = false;
    }
}

void MainGUI::sliderVoxelResolution( float buttonWidth )
{
    static int resolution = INIT_RESOLUTION;
    // VOXEL RESOLUTION
    ImGui::Text( "Voxel Resolution" );
    ImGui::PushItemWidth( buttonWidth );
    if ( ImGui::SliderInt( "##SLIDERRESOLUTION", &resolution, 1, MAX_RESOLUTION_VIEWER ))
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
        ImGuiFileDialog::Instance()->OpenDialog( "OBJFileDialog", "Choose an OBJ-File",
                                                 ".obj", config );
    }

    ImVec2 minDialogSize = ImVec2(
            static_cast<float>(dataHandler->getWindowWidth()) * .7f,
            static_cast<float>(dataHandler->getWindowHeight()) * .7f );
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
    ImGui::PushStyleColor( ImGuiCol_Button, colors::BUTTON_SUBMIT_DEFAULT_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, colors::BUTTON_SUBMIT_HOVER_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, colors::BUTTON_SUBMIT_ACTIVE_COLOR );
    if ( ImGui::Button( "Create benchmark##BENCHMARKS", ImVec2( buttonWidth, 0 )))
    {
        dataHandler->showBenchmarks( true );
        dataHandler->setBenchmarkUpdate( true );
    }
    ImGui::PopStyleColor( 3 );
}

void MainGUI::showSelectedAlgorithmsBenchmark( float deleteButtonWidth )
{
    ImGui::Text( "Selected Voxelization Algorithms:" );
    for ( VoxelizationAlgorithm a: dataHandler->getBenchmarkAlgorithms())
    {
        ImGui::Text( "%s", util::string::toString( a ).c_str());
        ImGui::SameLine();
        float rightAlignX = ImGui::GetContentRegionAvail().x - deleteButtonWidth;
        ImGui::SetCursorPosX( ImGui::GetCursorPosX() + rightAlignX );
        std::string label = u8"\u0013##" + util::string::toString( a );

        ImGui::PushStyleColor( ImGuiCol_ButtonHovered,
                               colors::BUTTON_DELETE_HOVER_COLOR );
        ImGui::PushStyleColor( ImGuiCol_ButtonActive,
                               colors::BUTTON_DELETE_ACTIVE_COLOR );
        if ( ImGui::Button( label.c_str(), ImVec2( deleteButtonWidth, 0.f )))
        {
            dataHandler->eraseFromBenchmark( a );
        }
        ImGui::PopStyleColor( 2 );
    }
}

void MainGUI::showPerformanceData()
{
    ImGui::Text( "%d FPS", dataHandler->getCurrentFPS());
    ImGui::SameLine();
    ImGui::Text( "%d voxels", dataHandler->getNumberOfVoxels());
    ImGui::SameLine();
}

bool MainGUI::buttonCreateBenchmarkCSV( const std::vector<BenchmarkMetric> &metrics,
                                        const std::string &title, float width )
{


    if ( ImGui::Button( title.c_str(), ImVec2( width, 0 )))
    {
        createCSV( "../benchmarks/example.csv", metrics );
        return true;
    }
    return false;
}

void
MainGUI::createCSV( const std::string &path, const std::vector<BenchmarkMetric> &metrics,
                    const std::string &separator )
{
#ifdef DEBUG
    std::cout << "\nCREATING CSV: STARTING";
#endif

    std::ofstream file;
    file.open( path );
    // HEADER
    file << "model, algorithm, resolution, time in ms\n";

    for ( const BenchmarkMetric &metric: metrics )
    {
        for ( const PerformanceData &performanceData: metric.performanceData )
        {
            file << metric.model.title;
            file << separator;
            file << util::string::toString( metric.algorithm );
            file << separator;
            file << performanceData.resolution;
            file << separator;
            file << util::time::toMS( performanceData.duration );
            file << "\n";
        }
    }
    file.close();

#ifdef DEBUG
    std::cout << "\nCREATING CSV: FINISHED" << std::endl;
#endif
}


void MainGUI::showNotification( const std::string &message, float x, float y, float width,
                                float height )
{
    ImGui::SetNextWindowPos( ImVec2( x, y ));
    ImGui::SetNextWindowSize( ImVec2( width, height ));
    ImGui::SetNextWindowBgAlpha( 0.5f );
    ImGui::PushStyleColor( ImGuiCol_WindowBg, colors::BUTTON_SUBMIT_ACTIVE_COLOR );
    if ( ImGui::Begin( "Notification", nullptr,
                       ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration |
                       ImGuiWindowFlags_NoMove ))
    {
        centeredText( message );
        ImGui::End();
    }
    ImGui::PopStyleColor();
}


void MainGUI::centeredText( const std::string &input )
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    ImVec2 textSize = ImGui::CalcTextSize( input.c_str());

    ImVec2 offset = ImVec2(( windowSize.x - textSize.x ) / 2.0f,
                           ( windowSize.y - textSize.y ) / 2.0f );
    ImVec2 cursorPosition = ImGui::GetCursorPos();
    ImVec2 newCursorPosition = { cursorPosition.x + offset.x,
                                 cursorPosition.y + offset.y };
    ImGui::SetCursorPos( newCursorPosition );
    ImGui::Text( "%s", input.c_str());
}
