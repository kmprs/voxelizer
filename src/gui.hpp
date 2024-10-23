#pragma once


#include <SDL.h>
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_opengl3.h"
#include "../dependencies/imgui/imgui_impl_sdl2.h"
#include "constants.hpp"


class GUI
{
public:
    GUI( SDL_Window* window, SDL_GLContext glContext );
    GUI() = default;
    void createFrame( float width, float height, int x, int y );

private:
    SDL_Window* m_window;
    SDL_GLContext m_context;
};