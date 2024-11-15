#include "renderer.hpp"

extern unsigned int programID;

extern std::shared_ptr<DataHandler> dataHandler;

Renderer::Renderer()
{
    m_meshDataHandler = std::make_unique<MeshDataHandler>( OBJ );

    vecTriangleFaceSharedPtr triangleFaces = m_meshDataHandler->getTriangleFaces();
    vecVoxelSharedPtr voxels = m_meshDataHandler->getVoxels();

    m_meshTriangle = Mesh( { triangleFaces.begin(), triangleFaces.end() } );
    m_meshVoxel = Mesh( { voxels.begin(), voxels.end() } );

    dataHandler->setWorldCenter( util::geometry::calculateCentroid( triangleFaces ) );
    dataHandler->setNumberOfVoxels( static_cast<int>(voxels.size()));
}

void Renderer::render()
{
    glClearColor( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    bool meshDataUpdated = m_meshDataHandler->update();
    if ( meshDataUpdated )
    {
        vecTriangleFaceSharedPtr triangleFaces = m_meshDataHandler->getTriangleFaces();
        vecVoxelSharedPtr voxels = m_meshDataHandler->getVoxels();
        m_meshTriangle = Mesh( { triangleFaces.begin(), triangleFaces.end() } );
        m_meshVoxel = Mesh( { voxels.begin(), voxels.end() } );
    }

    if ( dataHandler->getModelRepresentation() == VOXEL )
        m_meshVoxel.draw();
    else
        m_meshTriangle.draw();
}


