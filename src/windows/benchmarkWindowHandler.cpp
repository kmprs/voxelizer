#include "benchmarkWindowHandler.hpp"


BenchmarkWindowHandler::BenchmarkWindowHandler( const std::string &title, int width,
                                                int height ) :
        WindowHandler( title, width, height )
{
}

void BenchmarkWindowHandler::loadGUIFrame()
{
    m_benchmarkGUI.createFrame( m_window, m_imGuiContext,
                                200, static_cast<float>(m_height), 200, 0 );
}

