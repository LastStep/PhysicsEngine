#pragma once

#include <array>
#include <memory>

#include <Graphics/VertexArray.h>
#include <Graphics/Shader.h>
#include <Physics/Core.h>
#include <Util/OrthographicCameraController.h>


struct MeshTransform
{
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	//glm::vec3 Rotation;
};

struct MeshAttributes
{
	glm::vec3 Position;
	glm::vec4 Color = { 0.8f, 0.2f, 0.4f, 1.0f };
};

struct MeshRectangleAttributes : MeshAttributes
{
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
};

class Mesh
{
public:
	unsigned int m_EntityID = 0;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VertexArray;
	MeshTransform m_MeshTransform;

	bool SHOW_IN_IMGUI = false;

	Mesh(std::string ShaderFilePath)
		:	m_Shader(std::make_shared<Shader>(ShaderFilePath)),
			m_VertexArray(std::make_shared<VertexArray>())
	{
	};

	virtual void Draw(OrthographicCameraController* cameraController) = 0;
	virtual glm::vec4* GetColor() = 0;

	inline unsigned int GetID() { return m_EntityID; }
	inline std::shared_ptr<VertexArray> GetVertexArray() { return m_VertexArray; }
};

class MeshRectangle : public Mesh
{
private:
	MeshRectangleAttributes m_MeshRectangleAttributes;
	std::array<float, 8>  m_Positions;
	std::array<unsigned int, 6> m_Indices = {
		0, 1, 2,
		2, 3, 0
	};

public:
	MeshRectangle(MeshRectangleAttributes meshRectangleAttributes);
	~MeshRectangle();

	void Draw(OrthographicCameraController* cameraController) override;
	inline glm::vec4* GetColor() override { return &m_MeshRectangleAttributes.Color; }
};
