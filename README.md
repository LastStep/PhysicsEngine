# PhysicsEngine

A 2D physics engine, written in C++

## Demo

https://github.com/user-attachments/assets/1126859d-6fbf-4ebd-840d-c191f4ae2a49



## Project structure
- The [core](/src/Core) is the start of the project, which contains core imports for the engine, event system, and sets up the engine window.
- The [graphics](/src/Graphics) project contains all the logic to interact with OpenGL, shaders and gui code.
- The [util](/src/Util) project contains code that can be used in all project.
- The [physics](/src/Physics) project contains code for handling all the physics, including *Physics World*, *Physics Objects*, *Colliders* etc.

## Dependencies
- [GLFW](https://www.glfw.org/) Verified working with GLFW 3.3
- [GLEW](http://glew.sourceforge.net/) Verified with GLEW 2.1.0
- [glm](https://github.com/g-truc/glm/)
- [Dear ImGui](https://github.com/ocornut/imgui/tree/docking) Verified with ImGui v1.88



