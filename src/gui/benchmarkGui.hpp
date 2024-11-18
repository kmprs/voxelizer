#pragma once


#include "gui.hpp"



class BenchmarkGUI : public GUI
{
public:
    BenchmarkGUI();
    ~BenchmarkGUI();
    void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                 float height, int x, int y ) override;

private:
    static void
    plot( const vecBenchmarkMetricSharedPtr &metrics, const std::string &title );
    static void addLine( const std::shared_ptr<BenchmarkMetric> &metric );
};