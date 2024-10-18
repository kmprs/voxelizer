#include "bresenhamVoxelizer.hpp"


std::vector<Voxel> BresenhamVoxelizer::run(
        const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces )
{
    std::set<Voxel> voxelSet;

    for ( const auto& triangleFace: triangleFaces )
    {
        std::array<Line, 3> lines = toLines( triangleFace );
        for ( const Line &line: lines )
        {
            createLineVoxels( line.position0, line.position1, voxelSet );
        }
    }

    std::vector<Voxel> voxels;
    voxels.reserve( voxelSet.size());
    for ( const Voxel &voxel: voxelSet )
    {
        voxels.push_back( voxel );
    }
    return voxels;
}


void BresenhamVoxelizer::createLineVoxels( const glm::vec3 &start, const glm::vec3 &end,
                                           std::set<Voxel> &voxels )
{
    const float edgeLength = 1.f / RESOLUTION_LEVEL;

    glm::vec3 startQuantized = quantizeToVoxelCenter( start, edgeLength );
    glm::vec3 endQuantized = quantizeToVoxelCenter( end, edgeLength );

    int x1 = static_cast<int>( std::round( startQuantized.x / edgeLength ));
    int y1 = static_cast<int>( std::round( startQuantized.y / edgeLength ));
    int z1 = static_cast<int>( std::round( startQuantized.z / edgeLength ));

    int x2 = static_cast<int>( std::round( endQuantized.x / edgeLength ));
    int y2 = static_cast<int>( std::round( endQuantized.y / edgeLength ));
    int z2 = static_cast<int>( std::round( endQuantized.z / edgeLength ));

    int dx = abs( x2 - x1 );
    int dy = abs( y2 - y1 );
    int dz = abs( z2 - z1 );

    int xs = ( x2 > x1 ) ? 1 : -1;
    int ys = ( y2 > y1 ) ? 1 : -1;
    int zs = ( z2 > z1 ) ? 1 : -1;

    if ( dx >= dy && dx >= dz )
    {// X-dominant
        int p1 = 2 * dy - dx;
        int p2 = 2 * dz - dx;
        while ( x1 != x2 )
        {
            glm::vec3 center = quantizeToVoxelCenter(
                    glm::vec3( x1, y1, z1 ) * edgeLength, edgeLength );
            Voxel v = util::voxel::createVoxel( center,
                                                voxels.size() * VOXEL_MEMORY_SIZE,
                                                edgeLength );
            voxels.insert( v );
            x1 += xs;
            if ( p1 >= 0 )
            {
                y1 += ys;
                p1 -= 2 * dx;
            }
            if ( p2 >= 0 )
            {
                z1 += zs;
                p2 -= 2 * dx;
            }
            p1 += 2 * dy;
            p2 += 2 * dz;
        }
    } else if ( dy >= dx && dy >= dz )
    {// Y-dominant
        int p1 = 2 * dx - dy;
        int p2 = 2 * dz - dy;
        while ( y1 != y2 )
        {
            glm::vec3 center = quantizeToVoxelCenter(
                    glm::vec3( x1, y1, z1 ) * edgeLength, edgeLength );
            Voxel v = util::voxel::createVoxel( center,
                                                voxels.size() * VOXEL_MEMORY_SIZE,
                                                edgeLength );
            voxels.insert( v );
            y1 += ys;
            if ( p1 >= 0 )
            {
                x1 += xs;
                p1 -= 2 * dy;
            }
            if ( p2 >= 0 )
            {
                z1 += zs;
                p2 -= 2 * dy;
            }
            p1 += 2 * dx;
            p2 += 2 * dz;
        }
    } else
    {// Z-dominant
        int p1 = 2 * dy - dz;
        int p2 = 2 * dx - dz;
        while ( z1 != z2 )
        {
            glm::vec3 center = quantizeToVoxelCenter(
                    glm::vec3( x1, y1, z1 ) * edgeLength, edgeLength );
            Voxel v = util::voxel::createVoxel( center,
                                                voxels.size() * VOXEL_MEMORY_SIZE,
                                                edgeLength );
            voxels.insert( v );
            z1 += zs;
            if ( p1 >= 0 )
            {
                y1 += ys;
                p1 -= 2 * dz;
            }
            if ( p2 >= 0 )
            {
                x1 += xs;
                p2 -= 2 * dz;
            }
            p1 += 2 * dy;
            p2 += 2 * dx;
        }
    }

    // End-Voxel hinzufügen
    glm::vec3 center = quantizeToVoxelCenter( glm::vec3( x2, y2, z2 ) * edgeLength,
                                              edgeLength );
    Voxel v = util::voxel::createVoxel( center,
                                        voxels.size() * VOXEL_MEMORY_SIZE,
                                        edgeLength );
    voxels.insert( v );
}


std::array<Line, 3>
BresenhamVoxelizer::toLines( const std::shared_ptr<TriangleFace> &triangleFace )
{
    Triangle triangle = triangleFace->toTriangle();
    return std::array<Line, 3>{
            Line( triangle.position0, triangle.position1 ),
            Line( triangle.position0, triangle.position2 ),
            Line( triangle.position1, triangle.position2 )
    };
}


glm::vec3
BresenhamVoxelizer::quantizeToVoxelCenter( const glm::vec3 &point, float edgeLength )
{
    return glm::vec3(
            std::round( point.x / edgeLength ) * edgeLength,
            std::round( point.y / edgeLength ) * edgeLength,
            std::round( point.z / edgeLength ) * edgeLength
    );
}
