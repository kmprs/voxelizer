#pragma once

#include <string>
#include <memory>
#include "voxel.hpp"
#include "objParser.hpp"
#include "octreeVoxelizer.hpp"


class DataHandler
{
public:
    DataHandler( std::string path, FileFormat format );
    ~DataHandler() = default;

    [[nodiscard]] std::vector<std::shared_ptr<Voxel>> getVoxels() const;
    [[nodiscard]] std::vector<std::shared_ptr<TriangleFace>> getTriangleFaces() const;

private:
    std::string m_path;
    std::vector<std::shared_ptr<Voxel>> m_voxels = {};
    std::vector<std::shared_ptr<TriangleFace>> m_triangleFaces = {};
    std::unique_ptr<Parser> m_reader = nullptr;
    OctreeVoxelizer m_voxelizer;

    void voxelize();
};