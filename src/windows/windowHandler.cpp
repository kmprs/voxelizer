#include "windowHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


WindowHandler::WindowHandler( const std::string &title, int width, int height )
        :
        m_width( width ), m_height( height )
{
    if ( SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL\n";
        exit( EXIT_FAILURE );
    }

    m_window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width,
            m_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );


    if ( m_window == nullptr )
    {
        std::cerr << "Failed to create window\n";
        exit( EXIT_FAILURE );
    }
}

WindowHandler::~WindowHandler()
{
    SDL_DestroyWindow( m_window );
}

bool WindowHandler::isClosed() const
{
    return m_closed;
}

void WindowHandler::close()
{
    m_closed = true;
}

void WindowHandler::swapWindow()
{
    SDL_GL_SwapWindow( m_window );
}



void WindowHandler::updateWindowSize()
{
    SDL_GetWindowSize( m_window, &m_width, &m_height );
}

void WindowHandler::loadGUIFrame() const
{
    GUI::createFrame( static_cast<float>(GUI_WIDTH), static_cast<float>(m_height),
                          0, 0 );
}

void WindowHandler::toggleFullscreen()
{
    if ( m_isFullscreen ) SDL_SetWindowFullscreen( m_window, 0 );
    else SDL_SetWindowFullscreen( m_window, SDL_WINDOW_FULLSCREEN );
    m_isFullscreen = !m_isFullscreen;
}

SDL_Window* WindowHandler::getWindow() const
{
    return m_window;
}
