<img src="https://user-images.githubusercontent.com/60249504/147365454-ec78a07c-8121-4341-b229-825325cf4b92.gif" alt="Img Couldn't Load" width="500">

##### Description
This is an implemntation of a 3 dimensional kd-tree. It uses the median algorithm which is space filling
This is implemented specifically for triangles, however a n-dimensional bvh (Bounding Volume Heirarchy) kd-tree can be implemented

All this meaning a template version could be created however the templates would have to vary on what the tree is being used for (BVH, Point, EBH (Equation Bouding Heirarchy).  

Additional methods can/may be added such as rebuilding/repartitioning, meaning objects can repartition themselves, if they are no longer on a given side of a partition (due to transformations), they can generate new nodes if necessary, or implement simple add/delete methods.

##### Build
A build script is included however it is for the gnu toolchain. So, to run it go into any terminal, and get in the directory and type ./build.sh. If you don't use the gnu toolchain use any other compiler, it's a single file implememintation and uses only c++ standard libraries.

- [x] Add operator [] to vertex
- [ ] Add operator [] to triangle 
- [ ] Convert to templatable BVH
- [ ] Create Makefile

:collision: Can be translated to a lot of applications, and uses
