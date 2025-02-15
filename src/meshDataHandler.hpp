#pragma once

#include "objParser.hpp"
#include "optimizedVoxelizer.hpp"
#include "naiveVoxelizer.hpp"
#include "octreeVoxelizer.hpp"
#include "bvhVoxelizer.hpp"


class MeshDataHandler
{
public:
    MeshDataHandler( FileFormat format );
    MeshDataHandler() = default;
    ~MeshDataHandler() = default;

    [[nodiscard]] std::vector<std::shared_ptr<Voxel>> getVoxels() const;
    [[nodiscard]] vecTriangleFaceSharedPtr getTriangleFaces() const;
    bool update();

private:
    std::string m_path;
    vecVoxelSharedPtr m_voxels = {};
    vecTriangleFaceSharedPtr m_triangleFaces = {};
    std::unique_ptr<Parser> m_parser = nullptr;
    std::unique_ptr<Voxelizer> m_voxelizer = nullptr;
    VoxelizationAlgorithm m_currentAlgorithm;
    std::string m_currentModelPath;
    int m_currentResolution = -1;

    void voxelize( int voxelResolution );

};