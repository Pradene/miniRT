# miniRT

miniRT is a simple ray tracing program written in C, developed as part of the 42 Network curriculum. The project aims to render computer-generated images by simulating the way rays interact with objects in a scene.

## About

This project serves as an introduction to ray tracing, allowing the rendering of scenes composed of basic geometric shapes such as planes, spheres, and cylinders. The ray tracer implements features like:

- **Object Rendering**: Supports rendering of planes, spheres, and cylinders.
- **Lighting**: Implements ambient and point light sources with adjustable brightness.
- **Transformations**: Allows translation and rotation of objects, camera, and light sources.
- **Shadows**: Computes hard shadows based on light occlusion.

## Features

- **Scene Definition**: Define scenes using a simple text file format specifying objects, lights, and camera parameters.
- **Real-Time Rendering**: Utilizes CPU-based rendering to generate images, with optimizations for performance.
- **Interactive Controls**: Navigate and manipulate the scene using keyboard inputs.
- **Cross-Platform**: Developed using MiniLibX, a simple X-Window programming API in C, ensuring compatibility across Unix-based systems.

## Installation

To build and run miniRT, follow these steps:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/Pradene/miniRT.git
   ```

2. **Build the Project**:


    ```bash
    make
    ```

## Usage
To run the ray tracer:

  ```bash
  ./minirt path/to/scene_file
  ```
