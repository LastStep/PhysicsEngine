#pragma once

#include <array>
#include <memory>

#include <Graphics/VertexArray.h>
#include <Graphics/Shader.h>
#include <Physics/Core.h>
#include <Util/OrthographicCameraController.h>


int const SQUARE_POINTS = 8;

struct MeshAttributes
{
	glm::vec3 Position;
	glm::vec3 Offset = { 0.0f, 0.0f, 0.0f };
	glm::vec4 Color = { 0.8f, 0.2f, 0.4f, 1.0f };
};

struct MeshRectangleAttributes : MeshAttributes
{
	glm::vec2 Dimensions;
};

class Mesh
{
public:
	unsigned int m_EntityID = 0;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VertexArray;

	bool SHOW_IN_IMGUI = false;

	Mesh(std::string ShaderFilePath)
		:	m_Shader(std::make_shared<Shader>(ShaderFilePath)),
			m_VertexArray(std::make_shared<VertexArray>())
	{
	};

	virtual void Draw(std::shared_ptr<OrthographicCameraController> cameraController, std::shared_ptr<Physics::PhysicsObject> physicsObject) = 0;
	virtual glm::vec3 GetLocalPosition() = 0;
	virtual glm::vec3 GetWorldPosition(std::shared_ptr<Physics::PhysicsObject> physicsObject) = 0;
	virtual glm::vec4* GetColor() = 0;
	virtual glm::vec3* GetOffset() = 0;
	virtual void SetOffset(glm::vec3 offset) = 0;

	inline unsigned int GetID() { return m_EntityID; }
	inline std::shared_ptr<VertexArray> GetVertexArray() { return m_VertexArray; }
};

class MeshSquare : public Mesh
{
private:
	MeshRectangleAttributes m_MeshRectangleAttributes;
	std::array<float, SQUARE_POINTS>  m_Positions;
	std::array<unsigned int, 6> m_Indices = {
		0, 1, 2,
		2, 3, 0
	};

public:
	MeshSquare(MeshRectangleAttributes meshRectangleAttributes);
	~MeshSquare();

	void Draw(std::shared_ptr<OrthographicCameraController> cameraController, std::shared_ptr<Physics::PhysicsObject> physicsObject) override;
	glm::vec3 GetLocalPosition() override;
	glm::vec3 GetWorldPosition(std::shared_ptr<Physics::PhysicsObject> physicsObject) override;

	inline std::array<float, SQUARE_POINTS> GetPositions() const { return m_Positions; }

	inline glm::vec4* GetColor() override { return &m_MeshRectangleAttributes.Color; }
	inline glm::vec3* GetOffset() override { return &m_MeshRectangleAttributes.Offset; }
	inline void SetOffset(glm::vec3 offset) override { m_MeshRectangleAttributes.Offset = offset; }
};