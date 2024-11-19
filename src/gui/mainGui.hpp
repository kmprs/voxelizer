#pragma once


#include <fstream>
#include "gui.hpp"
#include "../util.hpp"


class MainGUI : public GUI
{
public:
    void createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                      float height, int x, int y ) override;

private:
    void createLeftFrame( ImGuiWindowFlags windowFlags, float buttonWidth );
    void createRightFrame( float width, ImGuiWindowFlags windowFlags, float buttonWidth );
    static void createBottomFrame( ImGuiWindowFlags windowFlags );
    static void buttonRepresentation( float buttonWidth );
    static void
    collapseSelection( const std::vector<std::string> &labels, bool &collapseStatus,
                       int selectedIndex, std::string defaultTitle,
                       const std::function<void( int )> &onSelect );
    static void sliderVoxelResolution( float buttonWidth );
    static void colorPickerVoxel();
    static void buttonCameraMode( float buttonWidth );
    static void numberInputCameraSpeed();
    static void numberInputRotationSpeed();
    static void buttonFileDialog( float buttonWidth, const std::string &title,
                                  const std::string &dialogID, bool &fileSelected,
                                  const std::function<void(
                                          const std::string & )> &onFileSelected );
    static void buttonBenchmarkDialog( float buttonWidth );
    static void showList( float deleteButtonWidth, const std::string &caption,
                          const std::vector<std::string> &items,
                          const std::function<void( const std::string & )> &onDelete );
    static bool buttonCreateBenchmarkCSV( const std::string &title, float width );
    static void
    createCSV( const std::string &path, const vecBenchmarkMetricSharedPtr &metrics,
               const std::string &separator = "," );
    static void
    showNotification( const std::string &message, float x, float y, float width,
                      float height );
    static void showPerformanceData();
    static void centeredText( const std::string &input );
};