#pragma once

#include "windows/windowHandler.hpp"
#include "camera.hpp"


class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;
    static void processInput( SDL_Event &event, WindowHandler &windowHandler, Direction &cameraDirection );

};
