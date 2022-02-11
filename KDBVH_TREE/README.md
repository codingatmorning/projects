<img src="https://user-images.githubusercontent.com/60249504/147365454-ec78a07c-8121-4341-b229-825325cf4b92.gif" alt="Img Couldn't Load" width="500">

## Description

This is an implemntation of a KDBVH Tree

:sparkler: It stores a Bounding Volume in N dimensions (x,y,z,w,...)
    :fireworks: 2D = Square, 3d = Cube, 4d = Tesseract, .... (Hyper Cube)
:sparkler: Simply Inhert BVH class, and your Object is now storable in a BVH Tree
    :fireworks: Just define get_bounds()
:sparkler: The Tree is Space-Filling which means worse case access time is log(n)

## Build

- Build Script included ./build.sh
  - For different Compilers change the code to compiler equivalent
- Compile with Define Example to see Example Usage

## Future Additions

- [ ] Auto-Repartition
      - When an Object stored in the leaf transforms it should move itself to the proper leaf
      
## Applications 
- :collision: Can be used in a lot of applications, and uses
  - Spacial Database, Computer Graphics, Mathametical Visualization...
