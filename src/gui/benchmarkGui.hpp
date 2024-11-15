#pragma once


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
                 float height, int x, int y ) override;

private:
    static std::vector<BenchmarkMetric> createBenchmarks();
    static void
    plot( const std::vector<BenchmarkMetric> &metrics, const std::string &title );
    static void addLine( const BenchmarkMetric &metric );
};