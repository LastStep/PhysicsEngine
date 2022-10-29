#include <Graphics/Mesh.h>
#include <Core/GLCore.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexBufferLayout.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


MeshSquare::MeshSquare(MeshRectangleAttributes meshRectangleAttributes)
    :   m_EntityID(0), 
        m_MeshRectangleAttributes(meshRectangleAttributes),
        m_Positions({
            meshRectangleAttributes.position.x + meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y + meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x + meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y - meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x - meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y - meshRectangleAttributes.dimensions.y,
            meshRectangleAttributes.position.x - meshRectangleAttributes.dimensions.x, meshRectangleAttributes.position.y + meshRectangleAttributes.dimensions.y,
        }),
        m_Shader("Resources/Shaders/Basic.shader")
{
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

void MeshSquare::Draw()
{
    m_Shader.Bind();
    m_Shader.SetUniform4fv("u_Color", m_MeshRectangleAttributes.color);

    glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
    //glm::mat4 proj = glm::translate(glm::mat4(1.0f), m_MeshRectangleAttributes.position);
    m_Shader.SetUniformMatrix4f("u_ViewProjection", proj);

    m_VertexArray.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0));
}

