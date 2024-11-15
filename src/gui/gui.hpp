#pragma once


#include <filesystem>
#include <SDL.h>
#include "guiConfig.hpp"
#include "../../dependencies/imgui/imgui_impl_opengl3.h"
#include "../../dependencies/imgui/imgui_impl_sdl2.h"
#include "../../dependencies/file_dialog/ImGuiFileDialog.h"
#include "../dataHandler.hpp"


class GUI
{
public:
    GUI() = default;
    virtual void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x,
                 int y ) = 0;
    static void setStyles();


private:

};