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
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );


    if ( m_window == nullptr )
    {
        std::cerr << "Failed to create window\n";
        exit( EXIT_FAILURE );
    }

//    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    m_context = SDL_GL_CreateContext( m_window );
    if ( m_context == nullptr )
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit( EXIT_FAILURE );
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ( void ) io;
    ImGui_ImplSDL2_InitForOpenGL( m_window, m_context );
    ImGui_ImplOpenGL3_Init( "#version 330" );

    ImGui::StyleColorsDark();

    m_gui = { m_window, m_context };
}

WindowHandler::~WindowHandler()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
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

void WindowHandler::makeCurrent()
{
    SDL_GL_MakeCurrent( m_window, m_context );
}

int WindowHandler::getHeight() const
{
    int width, height;
    SDL_GetWindowSize( m_window, &width, &height );
    return height;
}

void WindowHandler::loadGUIFrame()
{
    SDL_GetWindowSize( m_window, &m_width, &m_height );
    m_gui.createFrame( static_cast<float>(m_width) * .25f, static_cast<float>(m_height), 0, 0 );
}



