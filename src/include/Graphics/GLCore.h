#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
};

inline bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] Error Code     : " << error << std::endl;
        std::cout << "[OpenGL Error] Error Funciton : " << function << std::endl;
        std::cout << "[OpenGL Error] Error File     : " << file << std::endl;
        std::cout << "[OpenGL Error] Error Line     : " << line << std::endl;
        return false;
    }
    return true;
}