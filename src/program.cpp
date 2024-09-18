#include "program.hpp"
#include "openGLHandler.hpp"


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const std::string TITLE = "TestVoxelizer";

void Program::run()
{
    SDL_Event event;
    EventHandler eventHandler = {};
    WindowHandler windowHandler = { TITLE, WINDOW_WIDTH, WINDOW_HEIGHT };
    OpenGLHandler openGlHandler = {};

    while ( !windowHandler.isClosed())
    {
        if ( SDL_PollEvent( &event ) && event.type == SDL_QUIT )
        {
            windowHandler.close();
        }
        eventHandler.processInput(event, windowHandler);
        windowHandler.swapWindow();
    }
}
