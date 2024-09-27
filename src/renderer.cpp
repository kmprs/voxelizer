#include "renderer.hpp"

extern unsigned int programID;

Renderer::Renderer() :
        m_mesh( Mesh())
{
}

void Renderer::render()
{
    glClearColor( 0.35f, 0.4f, 0.37f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_mesh.draw();
}


