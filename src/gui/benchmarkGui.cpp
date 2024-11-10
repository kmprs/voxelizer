#include "benchmarkGui.hpp"


void
BenchmarkGUI::createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width,
                           float height, int x,
                           int y )
{
    ImGui::SetCurrentContext( imGuiContext );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Minimal window flags: No title bar, no resizing, no moving
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    float buttonWidth = width - 20;

    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGui::Begin( "BenchmarkGUI", nullptr, window_flags );

    static BenchmarkMetric benchmarkMetric;
    static Model model;
    model.title = "dragon";
    model.numberOfTriangles = -1;
    benchmarkMetric.model = model;
    benchmarkMetric.algorithm = OPTIMIZED;
    static PerformanceData d;
    d.resolution = 1;
    d.numberOfVoxels = 1;
    d.duration.s = 1;
    d.duration.ms = 23;
    benchmarkMetric.performanceData.push_back( d );
    d.resolution = 2;
    d.numberOfVoxels = 8;
    d.duration.s = 3;
    d.duration.ms = 124;
    benchmarkMetric.performanceData.push_back( d );


    ImGui::Text( "Model: %s (%d triangles)", benchmarkMetric.model.title.c_str(),
                 benchmarkMetric.model.numberOfTriangles );
    ImGui::Spacing();
    ImGui::Text( "Algorithm: %s", util::toString( benchmarkMetric.algorithm ).c_str());
    ImGui::End();
}

