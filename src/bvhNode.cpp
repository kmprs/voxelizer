#include "bvhNode.hpp"

void BVHNode::getLeaves( std::vector<BVHNode*> &leaves )
{
    if ( left == nullptr && right == nullptr )
    {
        leaves.push_back( this );
    } else
    {
        left->getLeaves( leaves );
        right->getLeaves( leaves );
    }
}
