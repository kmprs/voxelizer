#pragma once

#include "objParser.hpp"
#include "octreeBVHVoxelizer.hpp"
#include "bresenhamVoxelizer.hpp"
#include "naiveVoxelizer.hpp"
#include "octreeVoxelizer.hpp"


class MeshDataHandler
{
public:
    MeshDataHandler( std::string path, FileFormat format );
    MeshDataHandler() = default;
    ~MeshDataHandler() = default;

    [[nodiscard]] std::vector<std::shared_ptr<Voxel>> getVoxels() const;
    [[nodiscard]] std::vector<std::shared_ptr<TriangleFace>> getTriangleFaces() const;
    void update();

private:
    std::string m_path = "";
    std::vector<std::shared_ptr<Voxel>> m_voxels = {};
    std::vector<std::shared_ptr<TriangleFace>> m_triangleFaces = {};
    std::unique_ptr<Parser> m_reader = nullptr;
    std::unique_ptr<Voxelizer> m_voxelizer = nullptr;

    void voxelize( int voxelResolution );
};