#include "renderingWindowHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


RenderingWindowHandler::RenderingWindowHandler(const std::string& title, int width, int height)
        : WindowHandler(title, width, height)
{
    initGLContext();
    initGui();
}


RenderingWindowHandler::~RenderingWindowHandler()
{
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


void RenderingWindowHandler::updateWindowSize()
{
    SDL_GetWindowSize( m_window, &m_width, &m_height );
    glViewport(GUI_WIDTH, 0, m_width -  2 * GUI_WIDTH, m_height);
    dataHandler->setWindowWidth( m_width );
    dataHandler->setWindowHeight( m_height );
}

void RenderingWindowHandler::loadGUIFrame()
{
    m_gui.createFrame( static_cast<float>(GUI_WIDTH), static_cast<float>(m_height), 0, 0 );
}