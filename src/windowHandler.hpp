#pragma once

#include <iostream>
#include <SDL.h>

class WindowHandler
{
public:
    WindowHandler(const std::string& title, int width, int height);
    ~WindowHandler();

    bool isClosed();
    void close();
    void swapWindow();


private:
    const int m_width;
    const int m_height;
    bool m_closed = false;
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_context = nullptr;
};
