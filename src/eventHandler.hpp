#pragma once

#include "windowHandler.hpp"


class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;
    static void processInput(SDL_Event &event, WindowHandler &windowHandler);
};
