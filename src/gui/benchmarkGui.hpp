#pragma once


#include "../../dependencies/implot/implot.h"
#include "gui.hpp"
#include "../util.hpp"
#include "../dataHandler.hpp"
#include "../objParser.hpp"
#include "../benchmark.hpp"


class BenchmarkGUI : public GUI
{
public:
    BenchmarkGUI();
    ~BenchmarkGUI();
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                 float height,
                 int x,
                 int y ) override;

private:
    static void plot( const std::vector<BenchmarkMetric> &metrics );
    static void addLine( const BenchmarkMetric& metric );
    static void buttonTriggerBenchmark( float width, bool &flag );
};