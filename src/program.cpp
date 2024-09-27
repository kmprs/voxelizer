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

    unsigned int frameStart, frameTime, currentTime;
    int frameCount = 0;
    unsigned int fpsTimer = SDL_GetTicks();
    float deltaTime = 0.0f;
    unsigned lastTime = SDL_GetTicks();

    while ( !windowHandler.isClosed())
    {
        // constant fps
         frameStart = SDL_GetTicks();

        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        }
        currentTime = SDL_GetTicks();
        deltaTime = (static_cast<float>(currentTime - lastTime)) / 1000.f;
        lastTime = currentTime;

        EventHandler::processInput( event, windowHandler, cameraDirection );
        camera.update( cameraDirection, deltaTime );
        windowHandler.swapWindow();
        transformator.transform( camera.getPosition(), camera.getDirection());
        sceneHandler.setScene();
        renderer.render();
        openGlHandler.use();

        // constant fps
        frameTime = SDL_GetTicks() - frameStart;
        frameCount++;
        if (SDL_GetTicks() - fpsTimer >= 1000) {
            std::clog << "\rcurrent FPS: " << frameCount << ' ' << std::flush;
            frameCount = 0;
            fpsTimer = SDL_GetTicks();
        }
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}
