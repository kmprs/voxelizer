#include "voxelizer.hpp"
#include "util.hpp"


Voxelizer::Voxelizer( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces )
{
    for ( const std::shared_ptr<TriangleFace> &triangleFace: triangleFaces )
    {
        m_meshTriangles.push_back( triangleFace->toTriangle());
    }
}


void Voxelizer::buildOctree( OctreeNode* node, int depth, int maxDepth )
{
    // TODO: refactor!!!

    if ( depth >= maxDepth ) return;
    // fetch vertex positions from octree node
    std::array<Triangle, 12> voxelTriangles = util::getCubeTriangles( node->position,
                                                                      node->edgeLength );


    bool found = false;
    for ( const Triangle &voxelTriangle: voxelTriangles )
    {
        for ( const Triangle &meshTriangle: m_meshTriangles )
        {
            // check for triangle-triangle intersection
            if ( doTrianglesIntersect( meshTriangle, voxelTriangle ))
            {
                node->isAir = false;
                // new function call of buildOctree with children of node
                if ( depth - 1 < maxDepth )
                {
                    node->createChildren();
                    for ( OctreeNode* child: node->children )
                    {
                        buildOctree( child, depth + 1, maxDepth );
                    }
                }
                found = true;
                break;
            }
        }
        if ( found ) break;
    }
}


bool Voxelizer::doTrianglesIntersect( const Triangle &t0, const Triangle &t1 )
{
    // TODO: refactor this method!
    // TODO: test this method!
    // this method is based on the algorithm presented by Thomas Moeller
    // test if triangles are on the same side of the plane build by the other triangle
    // if yes, both triangles do not intersect
    glm::vec3 normalT1 = glm::cross( t1.position2 - t1.position1,
                                     t1.position3 - t1.position1 );
    float distanceT1 = glm::dot( -normalT1, t1.position1 );
    float distance0T0 = glm::dot( normalT1, t0.position1 ) + distanceT1;
    float distance1T0 = glm::dot( normalT1, t0.position2 ) + distanceT1;
    float distance2T0 = glm::dot( normalT1, t0.position3 ) + distanceT1;
    if ( distance0T0 > 0 && distance1T0 > 0 && distance2T0 > 0 ||
         distance0T0 < 0 && distance1T0 < 0 && distance2T0 < 0 )
    {
        return false;
    }
    glm::vec3 normalT0 = glm::cross( t0.position2 - t0.position1,
                                     t0.position3 - t0.position1 );
    float distanceT0 = glm::dot( -normalT0, t0.position1 );
    float distance0T1 = glm::dot( normalT0, t1.position1 ) + distanceT0;
    float distance1T1 = glm::dot( normalT0, t1.position2 ) + distanceT0;
    float distance2T1 = glm::dot( normalT0, t1.position3 ) + distanceT0;
    if ( distance0T1 > 0 && distance1T1 > 0 && distance2T1 > 0 ||
         distance0T1 < 0 && distance1T1 < 0 && distance2T1 < 0 )
    {
        return false;
    }

    glm::vec3 intersectionDirection = glm::cross( normalT0, normalT1 );
    // finding the triangle point which is on the other side of the plane
    // T0
    float pT00 = glm::dot( intersectionDirection, t0.position1 );
    float pT01 = glm::dot( intersectionDirection, t0.position2 );
    float pT02 = glm::dot( intersectionDirection, t0.position3 );
    float interval0[2];
    if ( util::differentSign( distance0T0, distance1T0, distance2T0 ))
    {
        interval0[0] =
                pT01 + ( pT00 - pT01 ) * ( distance1T0 / ( distance1T0 - distance0T0 ));
        interval0[1] =
                pT02 + ( pT00 - pT02 ) * ( distance2T0 / ( distance2T0 - distance0T0 ));
    }
    else if ( util::differentSign( distance1T0, distance0T0, distance2T0 ))
    {
        interval0[0] =
                pT00 + ( pT01 - pT00 ) * ( distance0T0 / ( distance0T0 - distance1T0 ));
        interval0[1] =
                pT02 + ( pT01 - pT02 ) * ( distance2T0 / ( distance2T0 - distance1T0 ));
    }
    else
    {
        interval0[0] =
                pT00 + ( pT02 - pT00 ) * ( distance0T0 / ( distance0T0 - distance2T0 ));
        interval0[1] =
                pT01 + ( pT02 - pT01 ) * ( distance1T0 / ( distance1T0 - distance2T0 ));
    }

    float pT10 = glm::dot( intersectionDirection, t1.position1 );
    float pT11 = glm::dot( intersectionDirection, t1.position2 );
    float pT12 = glm::dot( intersectionDirection, t1.position3 );
    float interval1[2];

    if ( util::differentSign( distance0T1, distance1T1, distance2T1 ))
    {
        interval1[0] =
                pT11 + ( pT10 - pT11 ) * ( distance1T1 / ( distance1T1 - distance0T1 ));
        interval1[1] =
                pT12 + ( pT10 - pT12 ) * ( distance2T1 / ( distance2T1 - distance0T1 ));
    }
    else if ( util::differentSign( distance1T1, distance0T1, distance2T1 ))
    {
        interval1[0] =
                pT10 + ( pT11 - pT10 ) * ( distance0T1 / ( distance0T1 - distance1T1 ));
        interval1[1] =
                pT12 + ( pT11 - pT12 ) * ( distance2T1 / ( distance2T1 - distance1T1 ));
    }
    else
    {
        interval1[0] =
                pT10 + ( pT12 - pT10 ) * ( distance0T1 / ( distance0T1 - distance2T1 ));
        interval1[1] =
                pT11 + ( pT12 - pT11 ) * ( distance1T1 / ( distance1T1 - distance2T1 ));
    }
    
    return util::doIntervalsIntersect(interval0, interval1);
}

