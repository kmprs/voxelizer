#include "renderer.hpp"

void Renderer::render()
{
    glClearColor( 0.8f, 0.8f, 0.8f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}