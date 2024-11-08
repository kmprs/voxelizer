#include "windowHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


WindowHandler::WindowHandler( const std::string &title, int width, int height )
        :
        m_width( width ), m_height( height )
{
    initWindow( title );
    initGLContext();
    initGui();
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


void WindowHandler::toggleFullscreen()
{
    if ( m_isFullscreen ) SDL_SetWindowFullscreen( m_window, 0 );
    else SDL_SetWindowFullscreen( m_window, SDL_WINDOW_FULLSCREEN );
    m_isFullscreen = !m_isFullscreen;
}


void WindowHandler::makeCurrent()
{
    SDL_GL_MakeCurrent( m_window, m_context );
}


SDL_Window* WindowHandler::getWindow() const
{
    return m_window;
}


void WindowHandler::initWindow( const std::string& title )
{
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


void WindowHandler::initGLContext()
{
    m_context = SDL_GL_CreateContext( m_window );
    if ( m_context == nullptr )
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit( EXIT_FAILURE );
    }
}


void WindowHandler::initGui()
{
    m_imGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_imGuiContext);
    ImGui_ImplSDL2_InitForOpenGL( m_window, m_context );
    ImGui_ImplOpenGL3_Init( "#version 330" );
}
