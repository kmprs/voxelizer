#pragma once


#include <string>
#include <set>
#include <utility>
#include <vector>
#include <thread>
#include "types.hpp"
#include "triangleFace.hpp"
#include "voxelizer.hpp"
#include "optimizedVoxelizer.hpp"
#include "bvhVoxelizer.hpp"
#include "octreeVoxelizer.hpp"
#include "naiveVoxelizer.hpp"


class Benchmark
{
public:
    Benchmark( const std::set<VoxelizationAlgorithm> &algorithms,
               std::string modelName,
               const vecTriangleFaceSharedPtr &triangleFaces
    );

    void create();
    [[nodiscard]] std::vector<BenchmarkMetric> get() const;

private:
    std::vector<BenchmarkMetric> m_metrics;
    std::set<VoxelizationAlgorithm> m_algorithms;
    std::vector<std::pair<VoxelizationAlgorithm, std::unique_ptr<Voxelizer>>> m_voxelizer = {};
    std::string m_modelName;
    vecTriangleFaceSharedPtr m_triangleFaces;
    std::mutex m_metricsMutex;

};


