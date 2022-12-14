#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	void DeleteVertexBuffer();

	void Bind() const;
	void Unbind() const;
};