#include "windowHandler.hpp"

WindowHandler::WindowHandler( const std::string &title, int width, int height )
        :
        m_width( width ), m_height( height )
{
    if ( SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL\n";
        exit( EXIT_FAILURE );
    }
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );

    m_window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width,
            m_height,
            SDL_WINDOW_OPENGL
    );


    if ( m_window == nullptr )
    {
        std::cerr << "Failed to create window\n";
        exit( EXIT_FAILURE );
    }

    m_context = SDL_GL_CreateContext( m_window );
    if ( !m_context )
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit( EXIT_FAILURE );
    }
}

WindowHandler::~WindowHandler()
{
    SDL_GL_DeleteContext( m_context );
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

bool WindowHandler::isClosed()
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
