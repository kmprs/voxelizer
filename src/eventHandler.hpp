#pragma once

#include "windowHandler.hpp"


class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;
    void processInput(SDL_Event &event, WindowHandler &windowHandler);
};
