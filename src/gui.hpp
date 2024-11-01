#pragma once


#include <SDL.h>
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_opengl3.h"
#include "../dependencies/imgui/imgui_impl_sdl2.h"
#include "constants.hpp"
#include "dataHandler.hpp"


class GUI
{
public:
    GUI() = default;
    static void createFrame( float width, float height, int x, int y );
    static void setStyles();


private:
    static void buttonRepresentation( float buttonWidth );
    static void collapseAlgorithmSelection();
    static void sliderVoxelResolution( float buttonWidth );
    static void colorPickerVoxel();
    static void buttonCameraMode( float buttonWidth );
    static void numberInputCameraSpeed();
    static void numberInputRotationSpeed();
    static void buttonFileDialog( float buttonWidth );
    static void showPerformanceData();

};