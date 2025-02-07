#pragma once


#include <filesystem>
#include <SDL.h>
#include "guiConfig.hpp"
#include "../../dependencies/imgui/imgui_impl_opengl3.h"
#include "../../dependencies/imgui/imgui_impl_sdl2.h"
#include "../../dependencies/file_dialog/ImGuiFileDialog.h"
#include "../util.hpp"
#include "../dataHandler.hpp"
#include "../objParser.hpp"
#include "../benchmark.hpp"


class GUI
{
public:
    GUI() = default;
    virtual void
    createFrame( SDL_Window* window, ImGuiContext* imGuiContext, float width, float height,
                 int x, int y ) = 0;
    static void setStyles();

protected:
    static vecBenchmarkMetricSharedPtr
    createBenchmarks( const std::string &modelPath, unsigned int numberOfSamples,
                      unsigned int minResolution, unsigned int maxResolution );

};