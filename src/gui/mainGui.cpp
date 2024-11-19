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

    static bool modelFileSelected = false;
    buttonFileDialog( buttonWidth, "Import OBJ model##GUI_MODEL", "OBJFileSelector",
                      modelFileSelected, [this]( const std::string &filePath ) {
                dataHandler->setModelPath( filePath );
                dataHandler->setWindowFreeze( false );
            } );
    std::filesystem::path filePath( dataHandler->getCurrentModelPath());
    ImGui::Text( "current model: %s", filePath.filename().c_str());
    ImGui::Spacing();
    ImGui::Spacing();

    static bool addAlgorithmsCollapsed = false;
    collapseSelection( { "Optimized", "Octree", "BVH", "Naive" }, addAlgorithmsCollapsed,
                       -1, "Add algorithm to benchmark", [this]( int index ) {
                dataHandler->addToBenchmark( static_cast<VoxelizationAlgorithm>(index));
            } );
    ImGui::Spacing();

    std::vector<std::string> selectedAlgorithms;
    for ( VoxelizationAlgorithm a: dataHandler->getBenchmarkAlgorithms())
    {
        selectedAlgorithms.push_back( util::string::toString( a ));
    }
    float deleteButtonWidth = width / 5;
    showList( deleteButtonWidth, "Selected Voxelization Algorithms:", selectedAlgorithms,
              [this]( const std::string &item ) {
                  dataHandler->eraseFromBenchmark( util::string::toAlgorithm( item ));
              } );
    ImGui::Spacing();

    buttonBenchmarkDialog( buttonWidth );
    ImGui::Spacing();

    static bool benchmarkFileSelected = false;
    buttonFileDialog( buttonWidth, "Add to model to benchmark##BENCHMARK_MODEL",
                      "BenchmarkModelSelector", benchmarkFileSelected,
                      [this]( const std::string &filePath ) {
                          dataHandler->addToBenchmarkModelPaths( filePath );
                      } );
    ImGui::Spacing();

    std::set < std::string > modelPaths = dataHandler->getBenchmarkModelPaths();
    showList( deleteButtonWidth, "Selected models for benchmarks:",
              { modelPaths.begin(), modelPaths.end() },
              [this]( const std::string &item ) {
                  dataHandler->eraseFromBenchmarkModelPath( item );
              } );
    ImGui::Spacing();


    static std::chrono::steady_clock::time_point notificationStartTime;
    if ( buttonCreateBenchmarkCSV( "Create CSV", buttonWidth ))
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

void MainGUI::buttonFileDialog( float buttonWidth, const std::string &title,
                                const std::string &dialogID, bool &fileSelected,
                                const std::function<void(
                                        const std::string & )> &onFileSelected )
{
    IGFD::FileDialogConfig config;
    config.path = BINARY_PATH;

    if ( ImGui::Button( title.c_str(), ImVec2( buttonWidth, 0 )))
    {
        fileSelected = false;
        ImGuiFileDialog::Instance()->OpenDialog( dialogID, "Choose an OBJ-File", ".obj",
                                                 config );
    }

    ImVec2 minDialogSize = ImVec2(
            static_cast<float>(dataHandler->getWindowWidth()) * .7f,
            static_cast<float>(dataHandler->getWindowHeight()) * .7f );
    ImGuiFileDialog::Instance()->Display( dialogID, 0, minDialogSize );

    if ( ImGuiFileDialog::Instance()->IsOk() && !fileSelected )
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        onFileSelected( filePath );
        ImGuiFileDialog::Instance()->Close();
        fileSelected = true;
    } else if ( !ImGuiFileDialog::Instance()->IsOk() &&
                ImGuiFileDialog::Instance()->cancelPressed )
    {
        ImGuiFileDialog::Instance()->cancelPressed = false;
        ImGuiFileDialog::Instance()->Close();
    }
}

void MainGUI::buttonBenchmarkDialog( float buttonWidth )
{
    ImGui::PushStyleColor( ImGuiCol_Button, colors::BUTTON_SUBMIT_DEFAULT_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, colors::BUTTON_SUBMIT_HOVER_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, colors::BUTTON_SUBMIT_ACTIVE_COLOR );
    if ( ImGui::Button( "Create benchmark (current model)##BENCHMARKS",
                        ImVec2( buttonWidth, 0 )))
    {
        dataHandler->showBenchmarks( true );
        dataHandler->setBenchmarkUpdate( true );
    }
    ImGui::PopStyleColor( 3 );
}

void MainGUI::showList( float deleteButtonWidth, const std::string &caption,
                        const std::vector<std::string> &items,
                        const std::function<void( const std::string & )> &onDelete )
{
    ImGui::Text( "%s", caption.c_str());
    std::vector<std::string> displayItems = items;
    for ( std::string &item: displayItems )
    {
        std::string itemShort = util::string::getNameFromPath( item );
        ImGui::Text( "%s", itemShort.c_str());
        ImGui::SameLine();
        float rightAlignX = ImGui::GetContentRegionAvail().x - deleteButtonWidth;
        ImGui::SetCursorPosX( ImGui::GetCursorPosX() + rightAlignX );
        std::string label = u8"\u0013##" + item;

        ImGui::PushStyleColor( ImGuiCol_ButtonHovered,
                               colors::BUTTON_DELETE_HOVER_COLOR );
        ImGui::PushStyleColor( ImGuiCol_ButtonActive,
                               colors::BUTTON_DELETE_ACTIVE_COLOR );
        if ( ImGui::Button( label.c_str(), ImVec2( deleteButtonWidth, 0.f )))
        {
            onDelete( item );
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

bool MainGUI::buttonCreateBenchmarkCSV( const std::string &title, float width )
{
    ImGui::PushStyleColor( ImGuiCol_Button, colors::BUTTON_SUBMIT_DEFAULT_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, colors::BUTTON_SUBMIT_HOVER_COLOR );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, colors::BUTTON_SUBMIT_ACTIVE_COLOR );
    if ( ImGui::Button( title.c_str(), ImVec2( width, 0 )))
    {
        ImGui::PopStyleColor( 3 );
        vecBenchmarkMetricSharedPtr metrics;

        for ( const std::string &path: dataHandler->getBenchmarkModelPaths())
        {
            auto metric = createBenchmarks( path );
            metrics.insert( metrics.end(), metric.begin(), metric.end());
        }

        createCSV( "../benchmarks/example.csv", metrics);
        return true;
    }
    ImGui::PopStyleColor( 3 );
    return false;
}

void
MainGUI::createCSV( const std::string &path, const vecBenchmarkMetricSharedPtr &metrics,
                    const std::string &separator )
{
#ifdef DEBUG
    std::cout << "\nCREATING CSV: STARTING\n";
#endif

    std::ofstream file;
    try
    {
        file.open( path );

        // Check if the file is open
        if ( !file.is_open())
        {
            throw std::ios_base::failure( "Failed to open file at path: " + path );
        }

        // HEADER
        file << "model, algorithm, resolution, time [ms]\n";

        for ( const std::shared_ptr<BenchmarkMetric> &metric: metrics )
        {
            for ( const PerformanceData &performanceData: metric->performanceData )
            {
                file << metric->model.title;
                file << separator;
                file << util::string::toString( metric->algorithm );
                file << separator;
                file << performanceData.resolution;
                file << separator;
                file << util::time::toMS( performanceData.duration );
                file << "\n";
            }
        }
        file.close();

        if ( file.fail())
        {
            throw std::ios_base::failure( "Failed to close the file at path: " + path );
        }
    } catch ( const std::ios_base::failure &e )
    {
        std::cerr << "File operation error: " << e.what() << std::endl;
    } catch ( const std::exception &e )
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

#ifdef DEBUG
    std::cout << "CREATING CSV: FINISHED" << std::endl;
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
