#include "bvhNode.hpp"

void BVHNode::getLeaves( std::vector<BVHNode*> &leaves )
{
    if ( left == nullptr && right == nullptr )
    {
        leaves.push_back( this );
    } else
    {
        if (left != nullptr)
        {
            left->getLeaves(leaves);
        }
        if (right != nullptr)
        {
            right->getLeaves(leaves);
        }
    }
}
