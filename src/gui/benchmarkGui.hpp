#pragma once


#include "gui.hpp"
#include "../util.hpp"


class BenchmarkGUI : public GUI
{
public:
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x,
                 int y ) override;
};