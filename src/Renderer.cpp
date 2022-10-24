#include <Graphics/Renderer.h>
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
};

bool GLLogCall(const char* function, const char* file, int line)
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