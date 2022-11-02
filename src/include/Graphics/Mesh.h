#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <Graphics/VertexArray.h>
#include <Graphics/Shader.h>
#include <glm/glm.hpp>
#include <Util/OrthographicCameraController.h>

int const SQUARE_POINTS = 8;


struct MeshRectangleAttributes
{
	glm::vec3 position;
	glm::vec2 dimensions;
	glm::vec3 offset = { 0.0f, 0.0f, 0.0f };
	glm::vec4 color = { 0.8f, 0.2f, 0.4f, 1.0f };
};


class MeshSquare
{
private:
	unsigned int m_EntityID = 0;
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

	void Draw(OrthographicCameraController* cameraController);

	inline unsigned int GetID() { return m_EntityID; }

	inline std::array<float, SQUARE_POINTS> GetPositions() const { return m_Positions; }
	inline VertexArray GetVertexArray() { return m_VertexArray; }

	inline glm::vec4* GetColor() { return &m_MeshRectangleAttributes.color; }

	inline glm::vec3* GetOffset() { return &m_MeshRectangleAttributes.offset; }
	inline void SetOffset(glm::vec3 offset) { m_MeshRectangleAttributes.offset = offset; }

	bool SHOW_IN_IMGUI = false;
};