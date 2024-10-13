#include "program.hpp"
#include "openGLHandler.hpp"
#include "renderer.hpp"
#include "constants.hpp"
#include "transformator.hpp"
#include "camera.hpp"
#include "sceneHandler.hpp"


void Program::run()
{
    SDL_Event event;
    WindowHandler windowHandler = {TITLE, WINDOW_WIDTH, WINDOW_HEIGHT};
    OpenGLHandler openGlHandler = {};
    std::shared_ptr<ShaderHandler> shaderHandler = openGlHandler.getShaderHandler();
    Camera camera = {};
    Transformator transformator = {shaderHandler};
    SceneHandler sceneHandler = {shaderHandler};
    Renderer renderer = {};

    Direction cameraDirection;

    // fps settings and display variables
    int frameCount = 0;
    float deltaTime, frameDuration;
    Uint64 currentCounter;
    Uint64 fpsTimer = SDL_GetPerformanceCounter();
    Uint64 lastCounter = SDL_GetPerformanceCounter();
    Uint64 performanceFrequency = SDL_GetPerformanceFrequency();

//    return;
    while ( !windowHandler.isClosed())
    {
        currentCounter = SDL_GetPerformanceCounter();

        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        }

        deltaTime = (static_cast<float>(currentCounter - lastCounter)) / static_cast<float>(performanceFrequency);
        lastCounter = currentCounter;

        // main methods
        EventHandler::processInput( event, windowHandler, cameraDirection );
        camera.update( cameraDirection, deltaTime );
        windowHandler.swapWindow();
        transformator.transform( camera.getPosition(), camera.getDirection());
        sceneHandler.setScene();
        renderer.render();
        openGlHandler.use();

        // constant fps
        frameCount++;
        if (currentCounter - fpsTimer >= performanceFrequency) {
            std::clog << "\rcurrent FPS: " << frameCount << ' ' << std::flush;
            frameCount = 0;
            fpsTimer = SDL_GetPerformanceCounter();
        }

        frameDuration = (1000.f * (static_cast<float>(SDL_GetPerformanceCounter() - currentCounter))) / static_cast<float>(performanceFrequency);
        if (FRAME_DELAY > frameDuration) {
            SDL_Delay(static_cast<Uint32>(FRAME_DELAY - frameDuration));
        }
    }
}
