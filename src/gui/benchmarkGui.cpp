#include "benchmarkGui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


BenchmarkGUI::BenchmarkGUI()
{
    ImPlot::CreateContext();
}

BenchmarkGUI::~BenchmarkGUI()
{
    ImPlot::DestroyContext();
}

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

    // plot
    ImGui::SetNextWindowPos( ImVec2( width, static_cast<float>(y)));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getBenchmarkWindowWidth()) - width,
                    static_cast<float>(dataHandler->getBenchmarkWindowHeight())));

    ImGui::Begin( "Plot##Plot", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar );

    // Wave simulation setup
    static float x_data[100];  // Number of points in the wave
    static float y_data[100];
    static float wave_frequency = 1.0f;
    static float wave_amplitude = 5.0f;

    // Calculate elapsed time
    static auto start_time = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::high_resolution_clock::now();
    float elapsed_time = std::chrono::duration<float>(
            current_time - start_time ).count();

    // Update x_data and y_data to simulate a moving wave
    for ( size_t i = 0; i < 100; ++i )
    {
        x_data[i] = i * 0.1f;  // Uniformly spaced points along x-axis
        y_data[i] =
                wave_amplitude * std::sin( wave_frequency * x_data[i] + elapsed_time );
    }

    plot( x_data, y_data, 100 );

    ImGui::End();
}

void BenchmarkGUI::plot( const float* x, const float* y, int size )
{
    if ( ImPlot::BeginPlot( "Performance Metrics", ImVec2( -1, -1 )))
    {
        ImPlot::SetupAxes( "Duration (s)", "Value y" );
        ImPlot::SetupAxisLimits( .1f, 0, 6.28 ); // Set Y-axis limit
        ImPlot::SetupLegend( ImPlotLocation_NorthEast );


        ImPlot::PlotLine( "Random Sin Wave##plot2", x, x, size );
        ImPlot::PushStyleColor( ImPlotCol_Line, ImVec4( 1.0f, 0.0f, 0.0f, 1.0f ));
        ImPlot::PlotLine( "Time##plot1", x, y, size );
        ImPlot::PopStyleColor();

        ImPlot::EndPlot();
    }
}

