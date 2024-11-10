#pragma once


#include "../../dependencies/implot/implot.h"
#include "gui.hpp"
#include "../util.hpp"
#include "../dataHandler.hpp"


class BenchmarkGUI : public GUI
{
public:
    BenchmarkGUI();
    ~BenchmarkGUI();
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x,
                 int y ) override;

private:
    static void plot(const float x[], const float y[], size_t size);
};