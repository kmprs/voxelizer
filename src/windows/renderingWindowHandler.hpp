#pragma once


#include "windowHandler.hpp"
#include "../gui/mainGui.hpp"


class RenderingWindowHandler : public WindowHandler
{
public:
    RenderingWindowHandler(const std::string& title, int width, int height);
    ~RenderingWindowHandler();
    void updateWindowSize() override;
    void loadGUIFrame() override;

private:
    MainGUI m_gui = {};
};