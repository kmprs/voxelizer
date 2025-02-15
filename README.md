# Voxelizer 🎲
![header image](./assets/readme_header.png)

## Table of Contents
- [Introduction](#Introduction)
- [Installation](#Installation)

---

## Introduction 
OptimizedVoxelizer is a C++ project designed to convert 3D models into voxel representations. 
It includes features for voxel face creation, file parsing, bounding volume hierarchy (BVH)
construction, and efficient spatial partitioning. This project aims to provide a lightweight
platform for rendering 3D-models as voxels and to explore different optimization methods. 

## Installation

- Clone the repository
- Navigate to the project directory
- Run the build script
- Install the necessary dependencies 
  - OpenGL 
  - SDL2 
- Create a /binaries directory and add your 3D models to it
  - In order for the voxelizer to run correctly, you need to adjust the initial model in 
  dataHandler.cpp 
- Adjust the 3D model path in src/constants.hpp 
