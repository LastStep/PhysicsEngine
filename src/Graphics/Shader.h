#pragma once

#include <string>
#include <unordered_map>

#include <Physics/Core.h>


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform4fv(const std::string& name, glm::vec4 values);
	void SetUniformMatrix4f(const std::string& name, const glm::mat4& values);

private:
	unsigned int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};