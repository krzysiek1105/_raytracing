#include "includes/octree.hpp"

Octree::Octree()
{
}

void Node::split()
{
    static int level = 0;
    if(triangles.size() <= MAX_TRIANGLES_IN_NODE || level >= MAX_RECURSION_LEVEL)
        return;

    nodes.resize(8);
    nodes[0].aabb = aabb;
    nodes[0].aabb.max.x /= 2;
    nodes[0].aabb.max.y /= 2;
    nodes[0].aabb.max.z /= 2;

    nodes[1].aabb = aabb;
    nodes[1].aabb.min.x = aabb.max.x / 2;
    nodes[1].aabb.max.y /= 2;
    nodes[1].aabb.max.z /= 2;

    nodes[2].aabb = aabb;
    nodes[2].aabb.max.x /= 2;
    nodes[2].aabb.min.y = aabb.max.y / 2;
    nodes[2].aabb.max.z /= 2;

    nodes[3].aabb = aabb;
    nodes[3].aabb.min.x = aabb.max.x / 2;
    nodes[3].aabb.min.y = aabb.max.y / 2;
    nodes[3].aabb.max.z /= 2;

    nodes[4].aabb = aabb;
    nodes[4].aabb.max.x /= 2;
    nodes[4].aabb.max.y /= 2;
    nodes[4].aabb.min.z = aabb.max.z / 2;

    nodes[5].aabb = aabb;
    nodes[5].aabb.min.x = aabb.max.x / 2;
    nodes[5].aabb.max.y /= 2;
    nodes[5].aabb.min.z = aabb.max.z / 2;

    nodes[6].aabb = aabb;
    nodes[6].aabb.max.x /= 2;
    nodes[6].aabb.min.y = aabb.max.y / 2;
    nodes[6].aabb.min.z = aabb.max.z / 2;

    nodes[7].aabb = aabb;
    nodes[7].aabb.min.x = aabb.max.x / 2;
    nodes[7].aabb.min.y = aabb.max.y / 2;
    nodes[7].aabb.min.z = aabb.max.z / 2;

    std::vector<Triangle> tmp;
    for(Triangle &t : triangles)
    {
        bool found = false;
        for(Node &n : nodes)
        {
            if(n.aabb.isPointInAABB(t.vertices[0]) && n.aabb.isPointInAABB(t.vertices[1]) && n.aabb.isPointInAABB(t.vertices[2]))
            {
                n.triangles.push_back(t);
                found = true;
                break;
            }
        }

        if(!found)
            tmp.push_back(t);
    }

    triangles.clear();
    tmp.swap(triangles);

    level++;
    for(Node &n : nodes)
        n.split();
}

Octree::Octree(std::vector<Triangle> &triangles)
{
    root.aabb = AABB(triangles);
    triangles.swap(root.triangles);
    root.split();
}