#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glew.h>
#include <string>

class ShaderProgram
{
public:
	enum ShaderType
	{
		ShaderType_vertex = GL_VERTEX_SHADER,
		ShaderType_fragment = GL_FRAGMENT_SHADER,
		ShaderType_compute = GL_COMPUTE_SHADER,
		ShaderType_tessControl = GL_TESS_CONTROL_SHADER,
		ShaderType_tessEvaluation = GL_TESS_EVALUATION_SHADER,
		ShaderType_geometry = GL_GEOMETRY_SHADER,
	};
	struct ShaderInitDesc
	{
		std::string vertexShader_path;
		std::string fragmentShader_path;
		std::string geometryShader_path;
		std::string computeShader_path;
		std::string tessControl_path;
		std::string tessEvaluation_path;
	};

public:
	operator GLuint() { return shaderProgram; }
public:
	ShaderProgram();
	virtual~ShaderProgram();

	int Create(ShaderInitDesc& desc);
	void Release();

private:
	int LoadShaderFromFile(const char* shaderPath, ShaderType shaderType);

	GLuint shaderProgram;
};


#endif // !SHADER_PROGRAM
