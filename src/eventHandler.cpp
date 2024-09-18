#include "eventHandler.hpp"


void EventHandler::processInput( SDL_Event &event, WindowHandler &windowHandler)
{
    if ( event.type == SDL_KEYDOWN)
    {
        if ( event.key.keysym.sym == SDLK_ESCAPE )
        {
            windowHandler.close();
        }
    }
}