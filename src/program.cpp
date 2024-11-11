#include "program.hpp"
#include "openGLHandler.hpp"
#include "renderer.hpp"
#include "constants.hpp"
#include "transformator.hpp"
#include "camera.hpp"
#include "sceneHandler.hpp"

std::shared_ptr<DataHandler> dataHandler = std::make_shared<DataHandler>();

void Program::run()
{
    initSDL();
    SDL_Event event;

    IMGUI_CHECKVERSION();
    BenchmarkWindowHandler benchmarkWindowHandler = { TITLE + " Benchmarks",
                                                      dataHandler->getBenchmarkWindowWidth(),
                                                      dataHandler->getBenchmarkWindowHeight() };
    bool benchmarksShown = dataHandler->isBenchmarkShown();
    SDL_HideWindow( benchmarkWindowHandler.getWindow() );
    ImGui::StyleColorsDark();
    GUI::setStyles();

    RenderingWindowHandler windowHandler = { TITLE, dataHandler->getWindowWidth(),
                                             dataHandler->getWindowHeight() };
    ImGui::StyleColorsDark();
    GUI::setStyles();


    OpenGLHandler openGlHandler = {};
    std::shared_ptr<ShaderHandler> shaderHandler = openGlHandler.getShaderHandler();
    Transformator transformator = { shaderHandler };
    SceneHandler sceneHandler = { shaderHandler };
    Renderer renderer = {};

    Camera camera = {};
    Direction cameraDirection;

    // fps settings and display variables
    int frameCount = 0;
    float deltaTime, frameDuration;
    Uint64 currentCounter;
    Uint64 fpsTimer = SDL_GetPerformanceCounter();
    Uint64 lastCounter = SDL_GetPerformanceCounter();
    Uint64 performanceFrequency = SDL_GetPerformanceFrequency();


    while ( !windowHandler.isClosed())
    {
        currentCounter = SDL_GetPerformanceCounter();

        if ( SDL_PollEvent( &event ) && event.type == SDL_WINDOWEVENT )
        {
            if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
            {
                if ( SDL_GetWindowID( windowHandler.getWindow()) ==
                     event.window.windowID )
                {
                    windowHandler.close();
                } else
                {
                    dataHandler->showBenchmarks( false );
                }
            } else if ( event.window.event == SDL_WINDOWEVENT_RESIZED )
            {
                if ( event.window.windowID ==
                     SDL_GetWindowID( windowHandler.getWindow()))
                {
                    windowHandler.updateWindowSize();
                }
                else if ( event.window.windowID ==
                            SDL_GetWindowID( benchmarkWindowHandler.getWindow()))
                {
                    benchmarkWindowHandler.updateWindowSize();
                }
            }
        } else
        {
            ImGui_ImplSDL2_ProcessEvent( &event );
        }


        deltaTime = ( static_cast<float>(currentCounter - lastCounter)) /
                    static_cast<float>(performanceFrequency);
        lastCounter = currentCounter;

        if ( benchmarksShown != dataHandler->isBenchmarkShown())
        {
            benchmarksShown = dataHandler->isBenchmarkShown();
            SDL_Window* w = benchmarkWindowHandler.getWindow();
            ( benchmarksShown ) ? SDL_ShowWindow( w ) : SDL_HideWindow( w );
        }

        if ( benchmarksShown )
        {
            benchmarkWindowHandler.makeCurrent();
            benchmarkWindowHandler.loadGUIFrame();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            benchmarkWindowHandler.swapWindow();
        };

        // imgui
        windowHandler.makeCurrent();
        windowHandler.loadGUIFrame();

        // main methods

        EventHandler::processInput( event, windowHandler, cameraDirection );
        if ( !dataHandler->isWindowFreezed())
        {
            camera.update( cameraDirection, deltaTime );
            transformator.transform( camera.getPosition(), camera.getDirection());
            sceneHandler.setScene( camera.getPosition());
            renderer.render();
            OpenGLHandler::use();
        }

        // ImGui Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData());
        windowHandler.swapWindow();

        // constant fps
        frameCount++;
        if ( currentCounter - fpsTimer >= performanceFrequency )
        {
            dataHandler->setCurrentFPS( frameCount );
            std::clog << "\rcurrent FPS: " << frameCount << ' ' << std::flush;
            frameCount = 0;
            fpsTimer = SDL_GetPerformanceCounter();
        }

        frameDuration = ( 1000.f * ( static_cast<float>(SDL_GetPerformanceCounter() -
                                                        currentCounter))) /
                        static_cast<float>(performanceFrequency);
        if ( FRAME_DELAY > frameDuration )
        {
            SDL_Delay( static_cast<Uint32>(FRAME_DELAY - frameDuration));
        }
    }

    // clean up SDL/GL/ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}


void Program::initSDL()
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
}
