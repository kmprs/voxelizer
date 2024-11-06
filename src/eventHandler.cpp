#include "eventHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;

void EventHandler::processInput( SDL_Event &event, WindowHandler &windowHandler,
                                 Direction &cameraDirection )
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
            case SDLK_a:
                cameraDirection = LEFT;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                cameraDirection = RIGHT;
                break;
            case SDLK_UP:
            case SDLK_SPACE:
                cameraDirection = UP;
                break;
            case SDLK_DOWN:
            case SDLK_c:
                cameraDirection = DOWN;
                break;
            case SDLK_w:
                cameraDirection = FORWARD;
                break;
            case SDLK_s:
                cameraDirection = BACKWARD;
                break;
            case SDLK_h:
                dataHandler->toggleWindowFreeze();
                break;


            default:
                cameraDirection = NO_MOVEMENT;
                break;
        }
    } else if ( event.type == SDL_KEYUP )
    {
        cameraDirection = NO_MOVEMENT;
    };
}
