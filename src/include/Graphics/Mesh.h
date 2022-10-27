#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <Graphics/VertexArray.h>
#include <Graphics/Shader.h>
#include <glm/glm.hpp>

int const SQUARE_POINTS = 8;


struct MeshRectangleAttributes
{
	glm::vec3 position;
	glm::vec2 dimensions;
	glm::vec4 color = { 0.6f, 0.3f, 0.8f, 1.0f };
};


class MeshSquare
{
private:
	unsigned int m_EntityID;
	MeshRectangleAttributes m_MeshRectangleAttributes;
	std::array<float, SQUARE_POINTS>  m_Positions;
	std::array<unsigned int, 6> m_Indices = {
		0, 1, 2,
		2, 3, 0
	};
	Shader m_Shader;

public:
	VertexArray m_VertexArray;
	MeshSquare(MeshRectangleAttributes meshRectangleAttributes);
	~MeshSquare();

	void Draw();

	inline std::array<float, SQUARE_POINTS> GetPositions() const { return m_Positions; }
	inline VertexArray GetVertexArray() { return m_VertexArray; }

};