#pragma once


#include "gui.hpp"


class BenchmarkGUI : public GUI
{
public:
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x,
                 int y ) override;

private:

};