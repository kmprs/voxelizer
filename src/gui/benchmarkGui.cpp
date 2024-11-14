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
    float buttonWidth = width - 20.f;

    ImGui::SetCurrentContext( imGuiContext );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    static bool newBenchmark = true;
    ImGui::SetNextWindowPos( ImVec2( x, static_cast<float>(y)));
    ImGui::SetNextWindowSize(
            ImVec2( static_cast<float>(dataHandler->getBenchmarkWindowWidth()),
                    static_cast<float>(dataHandler->getBenchmarkWindowHeight())));

    ImGui::Begin( "Plot##Plot", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar );


    static std::vector<BenchmarkMetric> benchmarks = { BenchmarkMetric() };
    if ( newBenchmark )
    {
        benchmarks.clear();
        std::unique_ptr<Parser> parser = std::make_unique<OBJParser>();
        std::vector<std::shared_ptr<TriangleFace>> triangleFaces = parser->parse(
                dataHandler->getCurrentModelPath());
        auto benchmarkAlgorithmsSet = dataHandler->getBenchmarkAlgorithms();
        Benchmark benchmark = { dataHandler->getBenchmarkAlgorithms(), "bunny",
                                triangleFaces };
        benchmark.create();
        benchmarks = benchmark.get();
        newBenchmark = false;
    }
    plot( benchmarks );
    ImGui::End();
}

void BenchmarkGUI::plot( const std::vector<BenchmarkMetric> &metrics )
{
    std::string title = "Algorithm Benchmarks (" + metrics[0].model.title + ")";
    ImPlot::PushStyleVar( ImPlotStyleVar_LineWeight, 2.0f );
    if ( ImPlot::BeginPlot( title.c_str(), ImVec2( -1, -1 )))
    {
        ImPlot::SetupAxes( "Resolution Level", "Duration [ms]" );
        ImPlot::SetupAxisLimits( ImAxis_X1, 1, MAX_RESOLUTION );
        ImPlot::SetupAxisScale( ImAxis_Y1, ImPlotScale_Log10 );
        ImPlot::SetupLegend( ImPlotLocation_NorthWest );

        for ( const BenchmarkMetric &m: metrics ) addLine( m );

        ImPlot::EndPlot();
    }
    ImPlot::PopStyleVar();
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