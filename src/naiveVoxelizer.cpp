#include "naiveVoxelizer.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


std::vector<Voxel> NaiveVoxelizer::run(const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces,
                                       int resolution)
{
    std::vector<Voxel> result;
    float voxelSize = 1.f / std::pow(2, resolution - 2);

    int numVoxelsPerDimension = static_cast<int>(std::ceil(2.f / voxelSize)); // Calculate the number of voxels per dimension

    for (int i = 0; i < numVoxelsPerDimension; ++i)
    {
        for (int j = 0; j < numVoxelsPerDimension; ++j)
        {
            for (int k = 0; k < numVoxelsPerDimension; ++k)
            {
                float x = -1.0f + (static_cast<float>(i) + 0.5f) * voxelSize;
                float y = -1.0f + (static_cast<float>(j) + 0.5f) * voxelSize;
                float z = -1.0f + (static_cast<float>(k) + 0.5f) * voxelSize;
                std::array<Triangle, 12> voxelTriangles = util::geometry::getCubeTriangles({ x, y, z }, voxelSize);
                bool isSolid = false;

                for (const Triangle &voxelTriangle : voxelTriangles)
                {
                    for (const auto &triangleFace : triangleFaces)
                    {
                        if (util::geometry::doTrianglesIntersect(voxelTriangle, triangleFace->toTriangle()))
                        {
                            isSolid = true;
                            break;
                        }
                    }
                    if (isSolid) break;
                }
                if (isSolid)
                {
                    result.push_back(util::voxel::createVoxel({ x, y, z }, result.size() * VOXEL_MEMORY_SIZE, voxelSize));
                }
            }
        }
    }
    return result;
}
