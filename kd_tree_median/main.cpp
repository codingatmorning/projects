#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
// jsdoc/doxygen not used as it's buggy in vscode
//  Defintion of Vertex Type a Vertex has 3 Points (x,y,z)
typedef class Vertex
{

public:
    // x,y,z
    double x, y, z;
    // Makes [] usable on a vertex
    double &operator[](int index)
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
        }
    }
} Vertex;

// Defintion of a triangle type a Triangle has 3 verticies (3 Vertex Type)
typedef struct triangle
{
    // 3 vertices
    Vertex vertex[3];
} triangle;

// get the front top right corner, and bottom back left corner of bounding box of triangle
//.____.__.
//| /\ |  |
//./__\.__. (3d)
void get_bounds(triangle in, Vertex &max, Vertex &min)
{
    max = in.vertex[0];
    min = in.vertex[0];
    for (int i = 1; i < 3; i++)
    {
        min.x = std::min(min.x, in.vertex[i].x);
        min.y = std::min(min.y, in.vertex[i].y);
        min.z = std::min(min.z, in.vertex[i].z);
        max.x = std::max(max.x, in.vertex[i].x);
        max.y = std::max(max.y, in.vertex[i].y);
        max.z = std::max(max.z, in.vertex[i].z);
    }
}

// Seperates which triangles are to the left of a given partitioning plane, and it's axis
// example: triangle {Vertex{-10,-10,-10}, Vertex{-8,-8,-8}, Vertex{-1,-1,-1}} to the left of the plane x=3? Yes, because all points on the x axis {-10,-8,1} are the left of x=3
std::vector<triangle *> seperate_left(std::vector<triangle *> cur_que, unsigned char axis, float median)
{
    std::vector<triangle *> temp;
    for (int i = 0; i < (int)cur_que.size(); i++)
    {
        Vertex max;
        Vertex min;
        get_bounds(*cur_que.at(i), max, min);
        if (max[axis] <= median || min[axis] < median)
            temp.push_back(cur_que.at(i));
    }
    return temp;
}
// Same as above function except finds triangles to the right of a given partioning plane
std::vector<triangle *> seperate_right(std::vector<triangle *> cur_que, unsigned char axis, float median)
{

    std::vector<triangle *> temp;
    for (int i = 0; i < (int)cur_que.size(); i++)
    {
        Vertex max;
        Vertex min;
        get_bounds(*cur_que.at(i), max, min);
        if (max[axis] > median || min[axis] >= median)
            temp.push_back(cur_que.at(i));
    }

    return temp;
}
/* Comparison Functor for Verticies, Compares two given Verticies along a given axis
return a boolean value, returns true if lhs < rhs on a given axis(x,y,z) */
class AxisComparison
{
    unsigned char axis;

public:
    AxisComparison(unsigned char _axis)
    {
        axis = _axis;
    }
    bool operator()(Vertex &lhs, Vertex &rhs) const
    {
        return lhs[axis] < rhs[axis];
    }
};

// Find Median Point
double find_median(std::vector<triangle *> trs, unsigned char axis)
{
    std::vector<Vertex> buffer;
    int size = (int)trs.size();
    for (int i = 0; i < size; i++)
    {
        Vertex max;
        Vertex min;
        get_bounds(*trs.at(i), max, min);
        buffer.push_back(min);
        buffer.push_back(max);
    }

    std::sort(buffer.begin(), buffer.end(), AxisComparison(axis));
    if (size != 0)
        return buffer[(int)buffer.size() / 2][axis];
    else
        return 0;
}
// kd_node stores data
class kd_node
{
public:
    // we only need 2 bits to store the axis for 3 dimensions
    unsigned char axis : 2;
    double division;
    kd_node *left_node = nullptr;
    kd_node *right_node = nullptr;
    // pointers to the object are used because it's cheaper to point to the object as objects may span multiple nodes
    // so it's cheaper to point to an object that stores ex: 400 bits, then store 400 bits in each node per item (a pointer is only 64-32 bits)
    std::vector<triangle *> storage;
    kd_node(std::vector<triangle *> que_p, unsigned char depth)
    {
        depth = depth - 1;
        axis = depth % 3;
        if (que_p.size() == 1 || que_p.size() == 0 || depth == 0)
        {
            storage = que_p;
        }
        else
        {
            division = find_median(que_p, depth % 3);
            left_node = new kd_node(seperate_left(que_p, depth % 3, division), depth);
            right_node = new kd_node(seperate_right(que_p, depth % 3, division), depth);
        }
    }
};
// Data is partioned by rotating through each dimension in our cases 3 dimension x then y then z then x then y then z...until the depth has been reached or all the data is partitioned
// the data is partioned by the median of all the data, what is to the left and to the right, of the median on the current dimension/axis
// kd_tree stores some necessary data for the root kd_node
class kd_tree
{
public:
    // The root of the tree
    kd_node *head = nullptr;
    // root bounding box is stored for query, and ray tracing for intersection, and overlap calculations of nodes below (only need to store in the root)
    Vertex Max;
    Vertex Min;

    // Depth tells you the the max height you will allow for the Kd-tree
    // que_p buffer of triangles you want to store/partition
    // Tree Constructor
    kd_tree(unsigned char depth, std::vector<triangle *> que_p)
    {
        // Find the Bounding Volume of Data
        int flag = true;
        for (int i = 0; i < (int)que_p.size(); i++)
        {
            Vertex _max;
            Vertex _min;
            get_bounds(*que_p.at(i), _max, _min);
            if (flag)
            {
                this->Max = _max;
                this->Min = _min;
                flag = false;
            }
            for (int j = 0; j < 3; j++)
            {
                if (Max[j] < _max[j])
                    Max[j] = _max[j];
                if (Min[j] > _min[j])
                    Min[j] = _min[j];
            }
        }
        // Initialize the head of the tree, and start buildling process
        head = new kd_node(que_p, depth);
    }
};
// Prints kd_tree
void print_tree(kd_node *node, std::string a)
{

    if (node->storage.size() != 0)
    {
        std::cout << a;
        int size = node->storage.size();
        // print triangles
        for (int i = 0; i < size; i++)
        {
            std::cout << "{";
            for (int j = 0; j < 3; j++)
            {
                std::cout << "{";
                for (int k = 0; k < 3; k++)
                {
                    std::cout << node->storage[i]->vertex[j][k] << " ,";
                }
                std::cout << "}";
            }
            std::cout << "}";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << a << std::endl;
        if (node->left_node != nullptr)
            print_tree(node->left_node, a + "-");
        if (node->right_node != nullptr)
            print_tree(node->right_node, a + "-");
    }
}
int main()
{
    // Create a bunch of triangles
    std::vector<triangle *> test;
    triangle *a = new triangle();
    a->vertex[0] = Vertex{0, 0, 0};
    a->vertex[1] = Vertex{1, 1, 1};
    a->vertex[2] = Vertex{2, 2, 2};
    test.push_back(a);
    a = new triangle();
    a->vertex[0] = Vertex{3, 3, 3};
    a->vertex[1] = Vertex{4, 4, 4};
    a->vertex[2] = Vertex{5, 5, 5};
    test.push_back(a);
    a = new triangle();
    a->vertex[0] = Vertex{6, 6, 6};
    a->vertex[1] = Vertex{7, 7, 7};
    a->vertex[2] = Vertex{8, 8, 8};
    test.push_back(a);
    a = new triangle();
    a->vertex[0] = Vertex{9, 9, 9};
    a->vertex[1] = Vertex{10, 10, 10};
    a->vertex[2] = Vertex{11, 11, 11};
    test.push_back(a);
    // example of how partition works the above triangles should seperate into one triangle per node, and print as such:
    //    |
    //  /   \
    // | | | |
    // t t t t
    // first it partitions the first two triangles to the left node, the last two triangles to the right node
    // then from the left node partitions the first triangle to a left node, and the second triangle to a right node, then does the same for the last two.
    kd_tree *kd = new kd_tree(4, test);
    print_tree(kd->head, "-");
}
