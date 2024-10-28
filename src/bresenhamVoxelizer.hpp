#pragma once


#include <set>
#include "voxelizer.hpp"
#include "util.hpp"
#include "constants.hpp"


class BresenhamVoxelizer : public Voxelizer
{
public:
    BresenhamVoxelizer() = default;
    std::vector<Voxel>
    run( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces,
         int resolution ) override;

private:

    void createLineVoxels( const glm::vec3 &start, const glm::vec3 &end,
                           std::set<Voxel> &voxels );
    static std::array<Line, 3>
    toLines( const std::shared_ptr<TriangleFace> &triangleFace );
    static glm::vec3 quantizeToVoxelCenter( const glm::vec3 &point, float edgeLength );
};

