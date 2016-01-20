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
	struct ShaderProgramDesc
	{
		const char* shaderName;
		const char* vertexShader_path;
		const char* tessControl_path;
		const char* tessEvaluation_path;
		const char* geometryShader_path;
		const char* fragmentShader_path;
		const char* computeShader_path;
	};

public:
	ShaderProgram();
	virtual~ShaderProgram();

	int Create(const ShaderProgramDesc& desc);
	void Release();

public:
	operator GLuint() { return shaderProgram; }

private:
	int LoadShaderFromFile(const char* shaderPath, ShaderType shaderType);

	GLuint shaderProgram;
};


#endif // !SHADER_PROGRAM
