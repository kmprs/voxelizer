#include "renderingWindowHandler.hpp"


RenderingWindowHandler::RenderingWindowHandler(const std::string& title, int width, int height)
        : WindowHandler(title, width, height)
{
    initGLContext();
    initGui();
}


RenderingWindowHandler::~RenderingWindowHandler()
{
    ImGui_ImplOpenGL3_Shutdown();
    SDL_GL_DeleteContext(m_context);
}


void RenderingWindowHandler::initGLContext()
{
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );

    m_context = SDL_GL_CreateContext( m_window );
    if ( m_context == nullptr )
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit( EXIT_FAILURE );
    }
}


void RenderingWindowHandler::initGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ( void ) io;
    ImGui_ImplSDL2_InitForOpenGL( m_window, m_context );
    ImGui_ImplOpenGL3_Init( "#version 330" );

    ImGui::StyleColorsDark();
    GUI::setStyles();
}


void RenderingWindowHandler::makeCurrent()
{
    SDL_GL_MakeCurrent( m_window, m_context );
}