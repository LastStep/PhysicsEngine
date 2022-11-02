#include <Graphics/Mesh.h>
#include <Core/GLCore.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexBufferLayout.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <iostream>
MeshSquare::MeshSquare(MeshRectangleAttributes meshRectangleAttributes)
    :   m_MeshRectangleAttributes(meshRectangleAttributes),
        m_Positions({
            meshRectangleAttributes.position.x + meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y + meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x + meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y - meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x - meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y - meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x - meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y + meshRectangleAttributes.dimensions.y,
        }),
        m_Shader("Resources/Shaders/Basic.shader")
{
    m_EntityID = m_VertexArray.GetID();
    m_VertexArray.Bind();
    VertexBuffer v_VertexBuffer(&m_Positions, (unsigned int) m_Positions.size() * sizeof(float));

    VertexBufferLayout v_VertexBufferLayout;
    v_VertexBufferLayout.Push<float>(2);

    m_VertexArray.AddBuffer(v_VertexBuffer, v_VertexBufferLayout);

    IndexBuffer v_IndexBuffer(m_Indices.data(), (unsigned int) m_Indices.size());

    m_VertexArray.Unbind();
    v_VertexBuffer.Unbind();
    v_IndexBuffer.Unbind();
}

MeshSquare::~MeshSquare()
{
}

void MeshSquare::Draw(OrthographicCameraController* cameraController)
{
    m_Shader.Bind();
    m_Shader.SetUniform4fv("u_Color", m_MeshRectangleAttributes.color);

    glm::mat4 MVP = glm::translate(cameraController->GetCamera().GetViewProjectionMatrix(), m_MeshRectangleAttributes.offset);
    m_Shader.SetUniformMatrix4f("u_ViewProjection", MVP);

    m_VertexArray.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0));
}

