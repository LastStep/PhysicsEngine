#include <iostream>
#include <Graphics/VertexArray.h>
#include <Graphics/GLCore.h>

VertexArray::VertexArray()
	: m_RendererID(0)
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& vertexBufferElements = vertexBufferLayout.GetElements();
	unsigned int attributeOffset = 0;
	for (unsigned int i = 0; i < vertexBufferElements.size(); i++)
	{
		const auto& vertexBufferElement = vertexBufferElements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(
			i, vertexBufferElement.count, vertexBufferElement.type, vertexBufferElement.normalized,
			vertexBufferLayout.GetStride(), (const void*)attributeOffset));
		attributeOffset += vertexBufferElement.GetOffsetOfElement();
	}
	vertexBuffer.Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
};

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
};