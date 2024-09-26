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

    while ( !windowHandler.isClosed())
    {
        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        }
        Direction cameraDirection;
        EventHandler::processInput( event, windowHandler, cameraDirection );
        camera.update( cameraDirection );
        windowHandler.swapWindow();
        transformator.transform( camera.getPosition(), camera.getDirection());
        sceneHandler.setScene();
        renderer.render();
        openGlHandler.use();
    }
}
