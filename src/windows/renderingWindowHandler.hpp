#pragma once


#include "windowHandler.hpp"
#include "../gui/mainGui.hpp"


class RenderingWindowHandler : public WindowHandler
{
public:
    RenderingWindowHandler(const std::string& title, int width, int height);
    ~RenderingWindowHandler();
    void initGLContext();
    void initGui();
    void makeCurrent();
    void updateWindowSize() override;
    void loadGUIFrame() override;

private:
    SDL_GLContext m_context = nullptr;
    MainGUI m_gui = {};
};