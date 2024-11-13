#pragma once


#include "gui.hpp"
#include "../util.hpp"


class MainGUI : public GUI
{
public:
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x,
                 int y ) override;

private:
    static void buttonRepresentation( float buttonWidth );
    static void collapseAlgorithmSelection();
    static void sliderVoxelResolution( float buttonWidth );
    static void colorPickerVoxel();
    static void buttonCameraMode( float buttonWidth );
    static void numberInputCameraSpeed();
    static void numberInputRotationSpeed();
    static void buttonFileDialog( float buttonWidth );
    static void buttonBenchmarkDialog( float buttonWidth );
    static void showPerformanceData();
};