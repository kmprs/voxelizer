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
    GUI();
    static void createFrame( float width, float height, int x, int y );
    static void setStyles();


private:
};