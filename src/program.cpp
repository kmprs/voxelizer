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
    SDL_Event event;
    WindowHandler windowHandler = { TITLE, dataHandler->getWindowWidth(),
                                    dataHandler->getWindowHeight() };
    OpenGLHandler openGlHandler = {};
    std::shared_ptr<ShaderHandler> shaderHandler = openGlHandler.getShaderHandler();
    Camera camera = {};
    Transformator transformator = { shaderHandler };
    SceneHandler sceneHandler = { shaderHandler };
    Renderer renderer = {};

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

        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        } else if ( event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_RESIZED )
        {
            windowHandler.updateWindowSize();
        } else
        {
            ImGui_ImplSDL2_ProcessEvent( &event );
        }

        deltaTime = ( static_cast<float>(currentCounter - lastCounter)) /
                    static_cast<float>(performanceFrequency);
        lastCounter = currentCounter;

        // imgui
        windowHandler.loadGUIFrame();

        // main methods
        EventHandler::processInput( event, windowHandler, cameraDirection );
        camera.update( cameraDirection, deltaTime );
        transformator.transform( camera.getPosition(), camera.getDirection());
        sceneHandler.setScene();
        renderer.render();
        openGlHandler.use();

        // ImGui Rendering
        ImGui::Render();
        windowHandler.makeCurrent();
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
}
