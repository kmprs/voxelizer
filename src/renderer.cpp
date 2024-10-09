#include "renderer.hpp"
#include "dataHandler.hpp"

extern unsigned int programID;

Renderer::Renderer()
{
    std::unique_ptr<DataHandler> dataHandler = std::make_unique<DataHandler>( MODEL_PATH, OBJ );
//    std::vector<std::shared_ptr<TriangleFace>> triangleFaces = dataHandler->getTriangleFaces();
//    m_renderables.insert( m_renderables.end(), triangleFaces.begin(), triangleFaces.end());
    std::vector<std::shared_ptr<Voxel>> voxels = dataHandler->getVoxels();
    m_renderables.insert( m_renderables.end(), voxels.begin(), voxels.end());

    m_mesh = Mesh( m_renderables );
}

void Renderer::render()
{
    glClearColor( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_mesh.draw();
}


