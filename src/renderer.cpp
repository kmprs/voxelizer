#include "renderer.hpp"
#include "meshDataHandler.hpp"

extern unsigned int programID;

extern std::shared_ptr<DataHandler> dataHandler;

Renderer::Renderer()
{
    std::unique_ptr<MeshDataHandler> meshDataHandler = std::make_unique<MeshDataHandler>(
            MODEL_PATH, OBJ );

    std::vector<std::shared_ptr<TriangleFace>> triangleFaces = meshDataHandler->getTriangleFaces();
    m_meshTriangle = Mesh( { triangleFaces.begin(), triangleFaces.end() } );

    std::vector<std::shared_ptr<Voxel>> voxels = meshDataHandler->getVoxels();
    m_meshVoxel = Mesh( { voxels.begin(), voxels.end() } );


    // calculate centroid of mesh based on the triangle-representation of the model;
    glm::vec3 center = { 0, 0, 0 };
    for ( const auto &triangleFace: triangleFaces )
    {
        glm::vec3 triangleCenter = triangleFace->getCenter();
        center.x += triangleCenter.x / static_cast<float>(triangleFaces.size());
        center.y += triangleCenter.y / static_cast<float>(triangleFaces.size());
        center.z += triangleCenter.z / static_cast<float>(triangleFaces.size());
    }
    dataHandler->setWorldCenter( center );
    dataHandler->setNumberOfVoxels( static_cast<int>(voxels.size()));
}

void Renderer::render()
{
    glClearColor( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( dataHandler->getModelRepresentation() == VOXEL ) m_meshVoxel.draw();
    else m_meshTriangle.draw();

}


