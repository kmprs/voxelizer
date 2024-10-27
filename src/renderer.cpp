#include "renderer.hpp"
#include "meshDataHandler.hpp"

extern unsigned int programID;

extern std::shared_ptr<DataHandler> dataHandler;

Renderer::Renderer()
{
    std::unique_ptr<MeshDataHandler> meshDataHandler = std::make_unique<MeshDataHandler>(
            MODEL_PATH, OBJ );
    std::vector<std::shared_ptr<TriangleFace>> triangleFaces = meshDataHandler->getTriangleFaces();
    glm::vec3 center = { 0, 0, 0 };
    for ( const auto &triangleFace: triangleFaces )
    {
        glm::vec3 triangleCenter = triangleFace->getCenter();
        center.x += triangleCenter.x / static_cast<float>(triangleFaces.size());
        center.y += triangleCenter.y / static_cast<float>(triangleFaces.size());
        center.z += triangleCenter.z / static_cast<float>(triangleFaces.size());
    }
    dataHandler->setWorldCenter( center );
//    m_renderables.insert( m_renderables.end(), triangleFaces.begin(), triangleFaces.end());
    std::vector<std::shared_ptr<Voxel>> voxels = meshDataHandler->getVoxels();
    dataHandler->setNumberOfVoxels( static_cast<int>(voxels.size()));
    m_renderables.insert( m_renderables.end(), voxels.begin(), voxels.end());

    m_mesh = Mesh( m_renderables );
}

void Renderer::render()
{
    glClearColor( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_mesh.draw();
}


