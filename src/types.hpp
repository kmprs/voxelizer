#pragma once


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
};


struct TriangleFace
{
    TriangleFace( const Vertex vertices[3], unsigned int offset ) :
            vertices{ vertices[0], vertices[1], vertices[2] }, offset( offset )
    {
        indices[0] = offset + 0;
        indices[1] = offset + 1;
        indices[2] = offset + 2;
    };
    TriangleFace() = default;

    Vertex vertices[3] = {};
    unsigned int indices[3] = {};
    unsigned int offset = 0;
};


struct VoxelFace
{
    VoxelFace( const Vertex vertices[4], unsigned int offset )
            :
            vertices{ vertices[0], vertices[1], vertices[2], vertices[3] },
            offset( offset )
    {
        indices[0] = offset + 0;
        indices[1] = offset + 1;
        indices[2] = offset + 2;
        indices[3] = offset + 1;
        indices[4] = offset + 3;
        indices[5] = offset + 2;
    }

    VoxelFace() = default;

    unsigned int offset = 0;
    Vertex vertices[4] = {};
    unsigned int indices[6] = {};
};


struct Voxel
{
    Voxel( const VoxelFace &front, const VoxelFace &back, const VoxelFace &top, const VoxelFace &bottom,
           const VoxelFace &left, const VoxelFace &right )
            :
            front( front ), back( back ), top( top ), bottom( bottom ), left( left ), right( right )
    {};
    Voxel() = default;
    VoxelFace front = {};
    VoxelFace back = {};
    VoxelFace top = {};
    VoxelFace bottom = {};
    VoxelFace left = {};
    VoxelFace right = {};
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