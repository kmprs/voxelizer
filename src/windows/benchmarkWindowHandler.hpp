#pragma once


#include "windowHandler.hpp"
#include "../gui/benchmarkGui.hpp"


class BenchmarkWindowHandler : public WindowHandler
{
public:
    BenchmarkWindowHandler(const std::string& title, int width, int height);
    void updateWindowSize() override;
    void loadGUIFrame() override;

private:
    BenchmarkGUI m_benchmarkGUI = {};
};