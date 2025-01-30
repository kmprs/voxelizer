#include "benchmark.hpp"


Benchmark::Benchmark( const std::set<VoxelizationAlgorithm> &algorithms,
                      std::string modelName,
                      const vecTriangleFaceSharedPtr &triangleFaces )
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
void Benchmark::create( unsigned int numberOfRuns )
{
    std::vector<std::thread> threads;
    threads.reserve( m_voxelizer.size());
    for ( const auto &voxelizer: m_voxelizer )
    {
        threads.emplace_back( [this, &voxelizer, numberOfRuns]() {
            std::shared_ptr<BenchmarkMetric> metric = std::make_shared<BenchmarkMetric>();
            metric->model.title = m_modelName;
            metric->model.numberOfTriangles = static_cast<int>(m_triangleFaces.size());
            metric->algorithm = voxelizer.first;

            std::vector<PerformanceData> performance;
            for ( int i = 1; i <= MAX_RESOLUTION_BENCHMARK; i++ )
            {
                std::vector<long long> runTimes = {};
                std::vector<std::thread> runThreads;
                runThreads.reserve(numberOfRuns);
                std::mutex runTimesMutex;

                for (int j = 0; j < numberOfRuns; j++) {
                    runThreads.emplace_back([&, j]() {
                        auto start = std::chrono::high_resolution_clock::now();
                        voxelizer.second->run(m_triangleFaces, i);
                        auto stop = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

                        std::lock_guard<std::mutex> lock(runTimesMutex);
                        runTimes.push_back(duration.count());
                    });
                }

                for (auto& t : runThreads) {
                    if (t.joinable())
                        t.join();
                }

                double mean = util::time::calculateMean( runTimes );
                double standardDeviation = util::time::calculateStandardDeviation(
                        runTimes, mean);
                PerformanceData data = {};
                data.resolution = i;
                data.duration.s = static_cast<int>(mean/1e6);
                data.duration.ms = static_cast<int>(mean/1e3);
                data.duration.micros = static_cast<int>(mean);
                data.standardDeviation.s = static_cast<int>(standardDeviation/1e6);
                data.standardDeviation.ms = static_cast<int>(standardDeviation/1e3);
                data.standardDeviation.micros = static_cast<int>(standardDeviation);
                performance.push_back( data );
            }
            metric->performanceData = performance;

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


vecBenchmarkMetricSharedPtr Benchmark::get() const
{
    return m_metrics;
}



