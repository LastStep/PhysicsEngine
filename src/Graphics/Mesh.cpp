#include <Core/GLCore.h>
#include <Graphics/Mesh.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexBufferLayout.h>
#include <iostream>

MeshSquare::MeshSquare(MeshRectangleAttributes meshRectangleAttributes)
    :   Mesh("Resources/Shaders/Basic.shader"),
        m_MeshRectangleAttributes(meshRectangleAttributes),
        m_Positions({
            meshRectangleAttributes.Position.x + meshRectangleAttributes.Dimensions.x / 2, meshRectangleAttributes.Position.y + meshRectangleAttributes.Dimensions.y / 2,
            meshRectangleAttributes.Position.x + meshRectangleAttributes.Dimensions.x / 2, meshRectangleAttributes.Position.y - meshRectangleAttributes.Dimensions.y / 2,
            meshRectangleAttributes.Position.x - meshRectangleAttributes.Dimensions.x / 2, meshRectangleAttributes.Position.y - meshRectangleAttributes.Dimensions.y / 2,
            meshRectangleAttributes.Position.x - meshRectangleAttributes.Dimensions.x / 2, meshRectangleAttributes.Position.y + meshRectangleAttributes.Dimensions.y / 2,
        })
{
    m_EntityID = m_VertexArray->GetID();
    m_VertexArray->Bind();
    VertexBuffer v_VertexBuffer(&m_Positions, (unsigned int) m_Positions.size() * sizeof(float));

    VertexBufferLayout v_VertexBufferLayout;
    v_VertexBufferLayout.Push<float>(2);

    m_VertexArray->AddBuffer(v_VertexBuffer, v_VertexBufferLayout);

    IndexBuffer v_IndexBuffer(m_Indices.data(), (unsigned int) m_Indices.size());

    m_VertexArray->Unbind();
    v_VertexBuffer.Unbind();
    v_IndexBuffer.Unbind();
}

MeshSquare::~MeshSquare()
{
}

void MeshSquare::Draw(std::shared_ptr<OrthographicCameraController> cameraController, std::shared_ptr<Physics::PhysicsObject> physicsObject)
{
    m_Shader->Bind();
    m_Shader->SetUniform4fv("u_Color", m_MeshRectangleAttributes.Color);

    glm::vec3 worldPosition = GetWorldPosition(physicsObject) - m_MeshRectangleAttributes.Position;

    glm::mat4 MVP = glm::translate(cameraController->GetCamera().GetViewProjectionMatrix(), worldPosition);
    m_Shader->SetUniformMatrix4f("u_ViewProjection", MVP);

    m_VertexArray->Bind();

	GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0));
}

glm::vec3 MeshSquare::GetLocalPosition()
{
    glm::vec3 o_LocalPosition = m_MeshRectangleAttributes.Position + m_MeshRectangleAttributes.Offset;
    return o_LocalPosition;
}

glm::vec3 MeshSquare::GetWorldPosition(std::shared_ptr<Physics::PhysicsObject> physicsObject)
{
    glm::vec3 o_WorldPosition = physicsObject->GetPosition() + m_MeshRectangleAttributes.Offset;
    return o_WorldPosition;
}

