#include "benchmarkWindowHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


BenchmarkWindowHandler::BenchmarkWindowHandler( const std::string &title, int width,
                                                int height ) :
        WindowHandler( title, width, height )
{}


void BenchmarkWindowHandler::updateWindowSize()
{
    SDL_GetWindowSize( m_window, &m_width, &m_height );
    dataHandler->setBenchmarkWindowWidth( m_width );
    dataHandler->setBenchmarkWindowHeight( m_height );
}

void BenchmarkWindowHandler::loadGUIFrame()
{
    m_benchmarkGUI.createFrame( m_window, m_imGuiContext,
                                static_cast<float>(dataHandler->getBenchmarkWindowWidth()),
                                static_cast<float>(dataHandler->getBenchmarkWindowHeight()),
                                0, 0 );
}

