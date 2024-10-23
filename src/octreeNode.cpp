#include "octreeNode.hpp"

OctreeNode::OctreeNode( OctreeNode* parent, float edgeLength, const glm::vec3 &position )
        :
        parent( parent ), edgeLength( edgeLength ), position( position )
{
}

void OctreeNode::createChildren()
{
    if ( children[0] != nullptr ) return;

    isLeaf = false;
    float offset = edgeLength / 4;
    for ( int i = 0; i < 8; i++ )
    {
        float offsetX = ( i & 1 ) ? offset : -offset;
        float offsetY = ( i & 2 ) ? offset : -offset;
        float offsetZ = ( i & 4 ) ? offset : -offset;

        // creates 8 child nodes with offsets calculated above
        children[i] = new OctreeNode( this, edgeLength / 2,
                                      { position.x + offsetX, position.y + offsetY,
                                        position.z + offsetZ } );
    }
}