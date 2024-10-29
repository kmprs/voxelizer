#include "eventHandler.hpp"


void EventHandler::processInput( SDL_Event &event, WindowHandler &windowHandler, Direction &cameraDirection )
{
    if ( event.type == SDL_KEYDOWN )
    {
        switch ( event.key.keysym.sym )
        {
            case SDLK_ESCAPE:
                windowHandler.close();
                break;
            case SDLK_f:
                windowHandler.toggleFullscreen();
                break;
            case SDLK_LEFT:
                cameraDirection = LEFT;
                break;
            case SDLK_a:
                cameraDirection = LEFT;
                break;
            case SDLK_RIGHT:
                cameraDirection = RIGHT;
                break;
            case SDLK_d:
                cameraDirection = RIGHT;
                break;
            case SDLK_UP:
                cameraDirection = UP;
                break;
            case SDLK_SPACE:
                cameraDirection = UP;
                break;
            case SDLK_DOWN:
                cameraDirection = DOWN;
                break;
            case SDLK_c:
                cameraDirection = DOWN;
                break;
            case SDLK_w:
                cameraDirection = FORWARD;
                break;

            case SDLK_s:
                cameraDirection = BACKWARD;
                break;
            default:
                cameraDirection = NO_MOVEMENT;
                break;
        }
    } else if ( event.type == SDL_KEYUP ) cameraDirection = NO_MOVEMENT;
}
