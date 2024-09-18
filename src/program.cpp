#include "program.hpp"
#include "openGLHandler.hpp"
#include "renderer.hpp"


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const std::string TITLE = "TestVoxelizer";

void Program::run()
{
    SDL_Event event;
    EventHandler eventHandler = {};
    WindowHandler windowHandler = { TITLE, WINDOW_WIDTH, WINDOW_HEIGHT };
    OpenGLHandler openGlHandler = {};
    Renderer renderer = {};

    while ( !windowHandler.isClosed())
    {
        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        }
        eventHandler.processInput(event, windowHandler);
        windowHandler.swapWindow();
        renderer.render();
        openGlHandler.use();
    }
}
