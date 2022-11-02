#pragma once

#include <Graphics/VertexBuffer.h>
#include <Graphics/VertexBufferLayout.h>


class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vertexBufferLayout);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetID() { return m_RendererID; }
};