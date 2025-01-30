#include "gui.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


void GUI::setStyles()
{
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF((( "../" + FONTS_DIR + "arial.ttf" ).c_str()), 16.0f );
    ImFontConfig config;

    // merge default font with symbol font
    config.MergeMode = true;
    io.FontDefault = io.Fonts->Fonts.back();

    // trash bin icon
    static const ImWchar icons_ranges[] = { 0x0013, 0x0013, 0 };
    io.Fonts->AddFontFromFileTTF((( "../" + FONTS_DIR + "FONTAWESOME.ttf" ).c_str()),
                                 16.0f, &config, icons_ranges );
    io.FontDefault = io.Fonts->Fonts[0];


    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowPadding = distances::WINDOW_PADDING;
    style.FramePadding = distances::FRAME_PADDING;
    style.ItemSpacing = distances::ITEM_SPACING;
    style.ItemInnerSpacing = distances::ITEM_INNER_SPACING;
    style.ScrollbarSize = distances::SCROLLBAR_SIZE;
    style.FrameRounding = distances::FRAME_ROUNDING;
    style.GrabRounding = distances::GRAB_ROUNDING;

    style.Colors[ImGuiCol_WindowBg] = colors::WINDOW_BG;
    style.Colors[ImGuiCol_TitleBg] = colors::TITLE_BG;
    style.Colors[ImGuiCol_TitleBgActive] = colors::TITLE_BG_ACTIVE;
    style.Colors[ImGuiCol_FrameBg] = colors::FRAME_BG;
    style.Colors[ImGuiCol_FrameBgHovered] = colors::FRAME_BG_HOVERED;
    style.Colors[ImGuiCol_FrameBgActive] = colors::FRAME_BG_ACTIVE;
    style.Colors[ImGuiCol_Button] = colors::BUTTON;
    style.Colors[ImGuiCol_ButtonHovered] = colors::BUTTON_HOVERED;
    style.Colors[ImGuiCol_ButtonActive] = colors::BUTTON_ACTIVE;
    style.Colors[ImGuiCol_Header] = colors::HEADER;
    style.Colors[ImGuiCol_HeaderHovered] = colors::HEADER_HOVERED;
    style.Colors[ImGuiCol_HeaderActive] = colors::HEADER_ACTIVE;
    style.Colors[ImGuiCol_SliderGrab] = colors::SLIDER_GRAB;
    style.Colors[ImGuiCol_SliderGrabActive] = colors::SLIDER_GRAB_ACTIVE;

    ImGui::GetIO().FontGlobalScale = 1.f;
}


vecBenchmarkMetricSharedPtr
GUI::createBenchmarks( const std::string &modelPath, int numberOfSamples )
{
    if ( dataHandler->getBenchmarkAlgorithms().empty()) return {};

    std::unique_ptr<Parser> parser = std::make_unique<OBJParser>();
    vecTriangleFaceSharedPtr triangleFaces = parser->parse( modelPath );
    Benchmark benchmark = { dataHandler->getBenchmarkAlgorithms(),
                            util::string::getNameFromPath<std::string>( modelPath ),
                            triangleFaces };
    benchmark.create( numberOfSamples );
    return benchmark.get();
}
