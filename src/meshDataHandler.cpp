#include "meshDataHandler.hpp"

extern std::shared_ptr<DataHandler> dataHandler;

MeshDataHandler::MeshDataHandler( FileFormat format ) :
        m_voxelizer( std::make_unique<OptimizedVoxelizer>()),
        m_currentModelPath( dataHandler->getCurrentModelPath()),
        m_currentResolution( dataHandler->getVoxelResolution()),
        m_currentAlgorithm( dataHandler->getVoxelizationAlgorithm())
{
    if ( format == OBJ ) m_parser = std::make_unique<OBJParser>();
    m_triangleFaces = m_parser->parse( dataHandler->getCurrentModelPath());
    voxelize( dataHandler->getVoxelResolution());
}

vecVoxelSharedPtr MeshDataHandler::getVoxels() const
{
    return m_voxels;
}

vecTriangleFaceSharedPtr MeshDataHandler::getTriangleFaces() const
{
    return m_triangleFaces;
}

void MeshDataHandler::voxelize( int voxelResolution )
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Voxel> voxels = m_voxelizer->run( m_triangleFaces, voxelResolution );
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationS = std::chrono::duration_cast<std::chrono::seconds>( stop - start );
    auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(
            stop - start );
#ifdef DEBUG
    std::cout << "\nVoxelization took: " << durationS.count() << "s:"
              << durationMS.count() % 1000 << "ms" << "\n";
#endif
    for ( const Voxel &v: voxels )
    {
        m_voxels.push_back( std::make_shared<Voxel>( v ));
    }

    dataHandler->setNumberOfVoxels( static_cast<int>(m_voxels.size()));
}

bool MeshDataHandler::update()
{
    bool meshDataChanged = false;

    if ( m_currentModelPath != dataHandler->getCurrentModelPath())
    {
        m_currentModelPath = dataHandler->getCurrentModelPath();
        m_triangleFaces.clear();
        m_triangleFaces = m_parser->parse( m_currentModelPath );
        dataHandler->setWorldCenter(
                util::geometry::calculateCentroid( m_triangleFaces ));
        m_voxels.clear();
        voxelize( dataHandler->getVoxelResolution());
        meshDataChanged = true;
    } else if ( dataHandler->getVoxelizationAlgorithm() != m_currentAlgorithm )
    {
        switch ( dataHandler->getVoxelizationAlgorithm())
        {
            case OPTIMIZED:
                m_voxelizer = std::make_unique<OptimizedVoxelizer>();
                break;
            case OCTREE:
                m_voxelizer = std::make_unique<OctreeVoxelizer>();
                break;
            case BVH:
                m_voxelizer = std::make_unique<BVHVoxelizer>();
                break;
            case NAIVE:
                m_voxelizer = std::make_unique<NaiveVoxelizer>();
                break;
            default:
                break;
        }
        m_currentAlgorithm = dataHandler->getVoxelizationAlgorithm();
        m_voxels.clear();
        voxelize( dataHandler->getVoxelResolution());
        meshDataChanged = true;
    } else if ( m_currentResolution != dataHandler->getVoxelResolution())
    {
        m_currentResolution = dataHandler->getVoxelResolution();
        m_voxels.clear();
        voxelize( m_currentResolution );
        meshDataChanged = true;
    }

    return meshDataChanged;
}

