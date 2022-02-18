## Description - Implementation of KDBVH-Tree

- It stores objects in a Hypercube Bounding Volume (x, y, z, w, ... n-Dimensions)  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- 2D = Square, 3D = Cube, 4D = Tesseract, .... (Hypercube)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Just define dim with a value 1, 2, 3, ... however many dimensions you want

- Simply Inherit BVH class, and your Object is now storable in a BVH Tree  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Just define get_bounds()  

- The Tree is Space-Filling which means worse case access time is log(n)  

## Build

- Build Script included ./build.sh
  - For different Compilers change the code to compiler equivalent
- Compile with -DExample to see Example Usage

## Constructs
- Shared_Ptr
- Polymorphism
- Inheritance
- Macros
- Typedef
- Vector
- Functor
- Operator Overloading
- Bit Efficiency
      
## Applications 
- :collision: Can be used in a lot of applications, and uses
  - Spacial Database, Computer Graphics, Mathametical Visualization...
