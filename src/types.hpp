#pragma once

#include <iostream>
#include <vector>

struct Vertex
{
    Vertex( float x, float y, float z, float nx, float ny, float nz ) :
            x( x ), y( y ), z( z ), nx( nx ), ny( ny ), nz( nz )
    {}

    Vertex() = default;

    float x = 0;
    float y = 0;
    float z = 0;
    float nx = 0;
    float ny = 0;
    float nz = 0;

    std::vector<float> toVector()
    {
        return std::vector<float>{ x, y, z, nx, ny, nz };
    }
};


struct VoxelFace
{
    VoxelFace( const Vertex vertices[4], unsigned int offset )
            :
            vertices{ vertices[0], vertices[1], vertices[2], vertices[3] }
    {
        indices[0] = offset + 0;
        indices[1] = offset + 1;
        indices[2] = offset + 2;
        indices[3] = offset + 1;
        indices[4] = offset + 3;
        indices[5] = offset + 2;
    }

    VoxelFace() = default;

    Vertex vertices[4] = {};
    unsigned int indices[6] = {};

    std::vector<float> verticesToVector()
    {
        std::vector<float> result = {};
        for ( Vertex vertex: vertices )
        {
            std::vector<float> vertexData = vertex.toVector();
            result.insert( result.end(), vertexData.begin(), vertexData.end());
        }
        return result;
    }

    std::vector<unsigned int> indicesToVector()
    {
        return { std::begin( indices ), std::end( indices ) };
    }
};


struct OBJFaceIndices
{
    OBJFaceIndices( int f1Coords, int f1Normal, int f2Coords, int f2Normal, int f3Coords, int f3Normal ) :
            f1Coords{ f1Coords }, f1Normal( f1Normal ), f2Coords( f2Coords ), f2Normal( f2Normal ),
            f3Coords( f3Coords ), f3Normal( f3Normal )
    {};
    int f1Coords, f1Normal, f2Coords, f2Normal, f3Coords, f3Normal;
};


enum Direction
{
    NO_MOVEMENT,
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    LEFT,
    RIGHT
};


enum FileFormat
{
    OBJ,
};


