#include "meshDataHandler.hpp"


MeshDataHandler::MeshDataHandler( std::string path, FileFormat format ) :
        m_path( std::move( path )), m_voxelizer( std::make_unique<OctreeVoxelizer>())
{
    if ( format == OBJ ) m_reader = std::make_unique<OBJParser>();
    m_triangleFaces = m_reader->parse( m_path );
    voxelize();
}

std::vector<std::shared_ptr<Voxel>> MeshDataHandler::getVoxels() const
{
    return m_voxels;
}

std::vector<std::shared_ptr<TriangleFace>> MeshDataHandler::getTriangleFaces() const
{
    return m_triangleFaces;
}

void MeshDataHandler::voxelize()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Voxel> voxels = m_voxelizer->run( m_triangleFaces );

    auto stop = std::chrono::high_resolution_clock::now();
    auto durationS = std::chrono::duration_cast<std::chrono::seconds>( stop - start );
    auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(
            stop - start );
    std::cout << "Voxelization took: " << durationS.count() << "s:"
              << durationMS.count() % 1000 << "ms" << std::endl;

    for ( const Voxel &v: voxels )
    {
        m_voxels.push_back( std::make_shared<Voxel>( v ));
    }

    std::cout << "Number of voxels: " << m_voxels.size() << std::endl;

}

