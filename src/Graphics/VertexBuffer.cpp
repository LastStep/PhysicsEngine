#include <Core/GLCore.h>
#include <Graphics/VertexBuffer.h>


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    : m_RendererID(0)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
};

void VertexBuffer::DeleteVertexBuffer()
{
    GLCall(glDeleteBuffers(GL_ARRAY_BUFFER, &m_RendererID));
};

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
};

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
};