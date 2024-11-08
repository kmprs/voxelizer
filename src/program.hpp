#pragma once

#include "eventHandler.hpp"
#include "windows/renderingWindowHandler.hpp"
#include "windows/benchmarkWindowHandler.hpp"

class Program
{
public:
    Program() = default;
    ~Program() = default;

    static void run();

private:
    static void initSDL();
};
