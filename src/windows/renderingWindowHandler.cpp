#include "renderingWindowHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


RenderingWindowHandler::RenderingWindowHandler(const std::string& title, int width, int height)
        : WindowHandler(title, width, height)
{}


RenderingWindowHandler::~RenderingWindowHandler()
{
    SDL_GL_DeleteContext(m_context);
}


void RenderingWindowHandler::updateWindowSize()
{
    SDL_GetWindowSize( m_window, &m_width, &m_height );
    glViewport(GUI_WIDTH, 0, m_width -  2 * GUI_WIDTH, m_height);
    dataHandler->setWindowWidth( m_width );
    dataHandler->setWindowHeight( m_height );
}

void RenderingWindowHandler::loadGUIFrame()
{
    m_gui.createFrame( m_window, m_imGuiContext,
                       static_cast<float>(GUI_WIDTH), static_cast<float>(m_height),
                       0, 0);
}