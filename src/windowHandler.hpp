#pragma once

#include <iostream>
#include <SDL.h>
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_opengl3.h"
#include "../dependencies/imgui/imgui_impl_sdl2.h"
#include "gui.hpp"


class WindowHandler
{
public:
    WindowHandler(const std::string& title, int width, int height);
    ~WindowHandler();

    bool isClosed();
    void close();
    void swapWindow();
    void makeCurrent();
    void loadGUIFrame();
    int getHeight() const;


private:
    int m_width;
    int m_height;
    bool m_closed = false;
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    GUI m_gui;
};
