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
                           float height, int x, int y )
{
    ImGui::SetCurrentContext( imGuiContext );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowPos( ImVec2( static_cast<float>(x), static_cast<float>(y)));
    ImGui::SetNextWindowSize( ImVec2( width, height ));

    ImGui::Begin( "Plot##Plot", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar );

    static std::string title;
    static vecBenchmarkMetricSharedPtr benchmarks = {
            std::make_shared<BenchmarkMetric>() };
    if ( dataHandler->benchmarkChanged())
    {
        dataHandler->setBenchmarkMetrics(
                createBenchmarks( dataHandler->getCurrentModelPath(), 1 ));
        benchmarks = dataHandler->getBenchmarkMetrics();
        // title must get a new unique id, otherwise the automatic rescaling fails

        title = ( !benchmarks.empty()) ? "Algorithm Benchmarks (" +
                                         benchmarks[0]->model.title + ")" + "##" +
                                         util::string::generateRandomString( 3 )
                                       : "No algorithm selected";
        dataHandler->setBenchmarkChanged( false );
        dataHandler->setBenchmarkUpdate( false );
    }

    plot( benchmarks, title );
    ImGui::End();
}


void
BenchmarkGUI::plot( const vecBenchmarkMetricSharedPtr &metrics, const std::string &title )
{
    ImPlot::PushStyleVar( ImPlotStyleVar_LineWeight, 2.0f );
    if ( ImPlot::BeginPlot( title.c_str(), ImVec2( -1, -1 )))
    {
        ImPlot::SetupAxes( "Resolution Level", "Duration [ms]" );
        ImPlot::SetupAxisLimits( ImAxis_X1, 1, MAX_RESOLUTION_BENCHMARK );
        ImPlot::SetupAxisScale( ImAxis_Y1, plot::SCALE_TYPE );
        ImPlot::SetupLegend( plot::LEGEND_LOCATION );

        for ( const std::shared_ptr<BenchmarkMetric> &m: metrics ) addLine( m );

        ImPlot::EndPlot();
    }
    ImPlot::PopStyleVar();
}

void BenchmarkGUI::addLine( const std::shared_ptr<BenchmarkMetric> &metric )
{
    std::string algorithmName = util::string::toString( metric->algorithm );
    std::string titleString = algorithmName + "##" + algorithmName;
    const char* title = titleString.c_str();

    std::vector<float> x, y;
    for ( const PerformanceData &data: metric->performanceData )
    {
        x.push_back( static_cast<float>(data.resolution));
        y.push_back( static_cast<float>( util::time::toMS( data.duration )));
    }
    ImPlot::PlotLine( title, x.data(), y.data(), static_cast<int>( x.size()));
}

