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

    BenchmarkMetric benchmarkMetric;
    benchmarkMetric.model.title = "dragon";
    benchmarkMetric.model.numberOfTriangles = -1;
    benchmarkMetric.algorithm = OPTIMIZED;
    PerformanceData d;
    d.resolution = 1;
    d.numberOfVoxels = 1;
    d.duration.s = 0;
    d.duration.ms = 23;
    benchmarkMetric.performanceData.push_back( d );
    d.resolution = 2;
    d.numberOfVoxels = 8;
    d.duration.s = 0;
    d.duration.ms = 40;
    benchmarkMetric.performanceData.push_back( d );
    d.resolution = 3;
    d.numberOfVoxels = 8;
    d.duration.s = 0;
    d.duration.ms = 80;
    benchmarkMetric.performanceData.push_back( d );
    d.resolution = 4;
    d.numberOfVoxels = 8;
    d.duration.s = 0;
    d.duration.ms = 233;
    benchmarkMetric.performanceData.push_back( d );
    d.resolution = 5;
    d.numberOfVoxels = 8;
    d.duration.s = 0;
    d.duration.ms = 401;
    benchmarkMetric.performanceData.push_back( d );


    ImGui::Text( "Model: %s (%d triangles)", benchmarkMetric.model.title.c_str(),
                 benchmarkMetric.model.numberOfTriangles );
    ImGui::Spacing();
    ImGui::Text( "Algorithm: %s", util::toString( benchmarkMetric.algorithm ).c_str());

    ImGui::End();


    ImGui::SetNextWindowPos( ImVec2( width, static_cast<float>(y)));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getBenchmarkWindowWidth()) - width,
                    static_cast<float>(dataHandler->getBenchmarkWindowHeight())));

    ImGui::Begin( "Plot##Plot", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar );

    plot( { benchmarkMetric } );

    ImGui::End();
}

void BenchmarkGUI::plot( const std::vector<BenchmarkMetric> &metrics )
{
    std::string title = "Algorithm Benchmarks (" + metrics[0].model.title + ")";
    if ( ImPlot::BeginPlot( title.c_str(), ImVec2( -1, -1 )))
    {
        ImPlot::SetupAxes( "Resolution Level", "Duration [ms]" );
        ImPlot::SetupAxisLimits( ImAxis_X1, 1, MAX_RESOLUTION );
        ImPlot::SetupAxisScale( ImAxis_Y1, ImPlotScale_Log10 );
        ImPlot::SetupLegend( ImPlotLocation_NorthEast );


        for ( const BenchmarkMetric &m: metrics ) addLine( m );

        ImPlot::EndPlot();
    }
}

void BenchmarkGUI::addLine( const BenchmarkMetric &metric )
{

    std::string titleString = util::toString( metric.algorithm )
                              + "##" +
                              util::toString( metric.algorithm );
    const char* title = titleString.c_str();

    std::vector<float> x, y;
    for ( const PerformanceData data: metric.performanceData )
    {
        x.push_back( static_cast<float>(data.resolution));
        y.push_back( static_cast<float>( util::time::toMS( data.duration )));
    }
    ImPlot::PlotLine( title, x.data(), y.data(), static_cast<int>( x.size()));
}



