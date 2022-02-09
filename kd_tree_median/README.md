##### Description
This is an implemntation of a 3 dimensional kd-tree. It uses the median algorithm which is space filling
This is implemented specifically for triangles, however a n-dimensional bvh (Bounding Volume Heirarchy) kd-tree can be implemented, or an n-dimensional point kd-tree could be implemented.

All this meaning a template version could be created however the templates would have to vary on what the tree is being used for. Bounding Volumes, or Points. 

Additional methods can/may be added such as rebuilding/repartitioning, meaning objects can repartition themselves, if they are no longer on a given side of a partition (due to transformations), they can generate new nodes if necessary, or implement simple add/delete methods.

##### Build
A build script is included however it is for the gnu toolchain. So, to run it go into any terminal, and get in the directory and type ./build.sh. If you don't use the gnu toolchain use any other compiler, it's a single file implememintation and uses only c++ standard libraries.
