#include "benchmark.hpp"


Benchmark::Benchmark( const std::set<VoxelizationAlgorithm> &algorithms,
                      std::string modelName,
                      const vecTriangleFace &triangleFaces )
        :
        m_algorithms( algorithms ), m_modelName( std::move( modelName )),
        m_triangleFaces( triangleFaces )
{
    for ( VoxelizationAlgorithm a: m_algorithms )
    {
        switch ( a )
        {
            case OPTIMIZED:
            {
                m_voxelizer.emplace_back(
                        a, std::make_unique<OptimizedVoxelizer>( OptimizedVoxelizer()));
                break;
            }
            case BVH:
            {
                m_voxelizer.emplace_back(
                        a, std::make_unique<BVHVoxelizer>( BVHVoxelizer()));
                break;
            }
            case OCTREE:
            {
                m_voxelizer.emplace_back(
                        a, std::make_unique<OctreeVoxelizer>( OctreeVoxelizer()));
                break;
            }
            case NAIVE:
            {
                m_voxelizer.emplace_back(
                        a, std::make_unique<NaiveVoxelizer>( NaiveVoxelizer()));
                break;
            }
            default:
                break;
        }
    }
}

/**
 * @brief runs each voxelization algorithm in every resolution and stores the result in
 * a vector (accessible via .get())
 */
void Benchmark::create()
{
    std::vector<std::thread> threads;
    threads.reserve( m_voxelizer.size());
    for ( const auto &voxelizer: m_voxelizer )
    {
        threads.emplace_back( [this, &voxelizer]() {
            BenchmarkMetric metric;
            metric.model.title = m_modelName;
            metric.model.numberOfTriangles = static_cast<int>(m_triangleFaces.size());
            metric.algorithm = voxelizer.first;

            std::vector<PerformanceData> performance;
            for ( int i = 1; i <= MAX_RESOLUTION_BENCHMARK; i++ )
            {
                // measure the time it takes for one voxelization run
                auto start = std::chrono::high_resolution_clock::now();

                voxelizer.second->run( m_triangleFaces, i );

                auto stop = std::chrono::high_resolution_clock::now();
                auto durationS = std::chrono::duration_cast<std::chrono::seconds>(
                        stop - start );
                auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(
                        stop - start );
                auto durationMicroS = std::chrono::duration_cast<std::chrono::microseconds>(
                        stop - start );

                PerformanceData data = {};
                data.resolution = i;
                data.duration.s = static_cast<int>(durationS.count());
                data.duration.ms = static_cast<int>(durationMS.count());
                data.duration.micros = static_cast<int>(durationMicroS.count());
                performance.push_back( data );
            }
            metric.performanceData = performance;

            // Lock access to m_metrics for thread safety
            std::lock_guard<std::mutex> lock( m_metricsMutex );
            m_metrics.push_back( metric );
        } );
    }

    // Join all threads
    for ( auto &thread: threads )
    {
        if ( thread.joinable())
        {
            thread.join();
        }
    }
}


std::vector<BenchmarkMetric> Benchmark::get() const
{
    return m_metrics;
}



