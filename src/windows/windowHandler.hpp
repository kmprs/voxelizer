#pragma once

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_opengl3.h"
#include "../../dependencies/imgui/imgui_impl_sdl2.h"
#include "../gui/gui.hpp"


class WindowHandler
{
public:
    WindowHandler(const std::string& title, int width, int height);
    ~WindowHandler();

    [[nodiscard]] bool isClosed() const;
    void close();
    void swapWindow();
    void toggleFullscreen();
    void makeCurrent();

    virtual void updateWindowSize();
    virtual void loadGUIFrame() = 0;

    [[nodiscard]] SDL_Window* getWindow() const;

protected:
    int m_width = -1;
    int m_height = -1;
    bool m_isFullscreen = false;
    bool m_closed = false;
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    ImGuiContext* m_imGuiContext = nullptr;

    void initWindow( const std::string& title );
    void initGLContext();
    void initGui();
};
