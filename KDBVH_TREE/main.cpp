#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#define X_ 1
#define Y_ 2
#define Z_ 3
#define dim 3
// N dimensional Vertex
typedef struct Vertex
{
public:
    // x,y,z,w....
    double coords[dim];
    double &operator[](unsigned int index)
    {
        return coords[index];
    }
} Vertex;

// Abstract Class that any class can inherit to be stored in BVH tree
class bounding_box
{
public:
    // Max, Min of Bounding Box
    Vertex max, min;
    std::string id;
    // get bounds
    virtual void get_bounds()
    {
        std::cout << "get_bounds undefined";
    };
};
#ifdef Example
// Example Usage of Bounding Box (Triangle)
class triangle : public bounding_box
{
public:
    // Triangle has 3 vertices
    Vertex vertex[3];
    triangle(std::string id)
    {
        this->id = id;
    }
    Vertex &operator[](unsigned int index)
    {
        return vertex[index];
    }
    void get_bounds()
    {
        this->max = vertex[0];
        this->min = vertex[1];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (vertex[i][j] > max[j])
                {
                    max[j] = vertex[i][j];
                }
                else if (vertex[i][j] < min[j])
                {
                    max[j] = vertex[i][j];
                }
            }
        }
    }
};

// Example usage of Bounding Box (Model)
class model : public bounding_box
{
    model(std::string id)
    {
        this->id = id;
    }
    // Have as much vertex data as you want
    Vertex vertex[4]{{10, 2, 3}, {1, 2, 3}, {5, 6, 7}, {3, 2, 1}};
    int data_2;
    int data2;
    Vertex &operator[](unsigned int index)
    {
        return vertex[index];
    }
    void get_bounds()
    {
        this->max = vertex[0];
        this->min = vertex[1];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; i < dim; i++)
            {
                if (vertex[i][j] > max[j])
                {
                    max[j] = vertex[i][j];
                }
                else if (vertex[i][j] < min[j])
                {
                    max[j] = vertex[i][j];
                }
            }
        }
    }
};
#endif
// Check which Bounding Boxes are to left of a given partition
std::vector<std::shared_ptr<bounding_box>> seperate_left(std::vector<std::shared_ptr<bounding_box>> cur_que, unsigned char axis, float partition)
{
    std::vector<std::shared_ptr<bounding_box>> temp;
    for (int i = 0; i < (int)cur_que.size(); i++)
    {
        Vertex max;
        Vertex min;
        cur_que[i]->get_bounds();
        max = cur_que[i]->max;
        min = cur_que[i]->min;
        if (max[axis] <= partition || min[axis] < partition)
            temp.push_back(cur_que.at(i));
    }
    return temp;
}
// Check which Bounding Boxes are to right of a given partition
std::vector<std::shared_ptr<bounding_box>> seperate_right(std::vector<std::shared_ptr<bounding_box>> cur_que, unsigned char axis, float partition)
{

    std::vector<std::shared_ptr<bounding_box>> temp;
    for (int i = 0; i < (int)cur_que.size(); i++)
    {
        Vertex max;
        Vertex min;
        cur_que[i]->get_bounds();
        max = cur_que[i]->max;
        min = cur_que[i]->min;
        if (max[axis] > partition || min[axis] >= partition)
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

// Find Median Point of Bounding Volumes {0,1,2,3,4,5,6,7,8} 4 is the median (Simplified)
double find_median(std::vector<std::shared_ptr<bounding_box>> bvs, unsigned char axis)
{
    std::vector<Vertex> buffer;
    unsigned int size = (unsigned int)bvs.size();
    for (int i = 0; i < size; i++)
    {
        Vertex max;
        Vertex min;
        bvs[i]->get_bounds();
        max = bvs[i]->max;
        min = bvs[i]->min;
        buffer.push_back(min);
        buffer.push_back(max);
    }

    std::sort(buffer.begin(), buffer.end(), AxisComparison(axis));
    if (size != 0)
        return buffer[(int)buffer.size() / 2][axis];
    else
        return 0;
}
// bvh_node stores data
class bvh_node
{
public:
    unsigned char axis : 2;
    double division;
    bvh_node *left_node = nullptr;
    bvh_node *right_node = nullptr;
    std::vector<std::shared_ptr<bounding_box>> storage;
    bvh_node(std::vector<std::shared_ptr<bounding_box>> que_p, unsigned char depth)
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
            left_node = new bvh_node(seperate_left(que_p, depth % 3, division), depth);
            right_node = new bvh_node(seperate_right(que_p, depth % 3, division), depth);
        }
    }
};

class bvh_tree
{
public:
    // The root of the tree
    bvh_node *head = nullptr;

    // Bounding Box for Root, so traversals can calculate partitioning plane
    Vertex Max = {-INFINITY};
    Vertex Min = {+INFINITY};

    bvh_tree(unsigned char depth, std::vector<std::shared_ptr<bounding_box>> que_p)
    {
        for (auto x : que_p)
        {
            x->get_bounds();
            for (int i = 0; i < dim; i++)
            {
                if (x->max[i] > Max[i])
                    x->max[i] = Max[i];
                else if (x->min[i] < Min[i])
                    x->min[i] = Min[i];
            }
        }

        // Initialize the head of the tree, and start buildling process
        head = new bvh_node(que_p, depth);
    }
};
// Prints bvh_tree
void print_tree(bvh_node *node, std::string a)
{

    if (node->storage.size() != 0)
    {
        std::cout << a;
        for (auto x : node->storage)
        {
            std::cout << x->id;
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
#ifdef Example
    std::vector<std::shared_ptr<bounding_box>> test;
    triangle a("1");
    a.vertex[0] = Vertex{1, 1, 1};
    a.vertex[1] = Vertex{2, 2, 2};
    a.vertex[2] = Vertex{3, 3, 3};
    test.push_back(std::make_shared<triangle>(a));
    triangle b("2");
    b.vertex[0] = Vertex{3, 3, 3};
    b.vertex[1] = Vertex{4, 4, 4};
    b.vertex[2] = Vertex{5, 5, 5};
    test.push_back(std::make_shared<triangle>(b));
    triangle c("3");
    c.vertex[0] = Vertex{6, 6, 6};
    c.vertex[1] = Vertex{7, 7, 7};
    c.vertex[2] = Vertex{8, 8, 8};
    test.push_back(std::make_shared<triangle>(c));
    triangle d("4");
    d.vertex[0] = Vertex{9, 9, 9};
    d.vertex[1] = Vertex{10, 10, 10};
    d.vertex[2] = Vertex{11, 11, 11};
    test.push_back(std::make_shared<triangle>(d));
    bvh_tree *kd = new bvh_tree(4, test);
    // example of how partition works the above triangles should seperate into one triangle per node, and print as such:
    //    |
    //  /   \
    // | | | |
    // t t t t
    print_tree(kd->head, "-");

#endif
}
