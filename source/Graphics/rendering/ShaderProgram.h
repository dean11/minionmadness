#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glew.h>
#include <string>
#include <functional>

class ShaderProgram
{
public:
	enum ShaderType
	{
		ShaderType_vertex = GL_VERTEX_SHADER,
		ShaderType_tessControl = GL_TESS_CONTROL_SHADER,
		ShaderType_tessEvaluation = GL_TESS_EVALUATION_SHADER,
		ShaderType_geometry = GL_GEOMETRY_SHADER,
		ShaderType_fragment = GL_FRAGMENT_SHADER,
		ShaderType_compute = GL_COMPUTE_SHADER,
		ShaderType_Count = 6,
		ShaderType_Undefined,
	};
	struct ShaderProgramInitDesc
	{
		std::string vertexShader;
		std::string tessControllShader;
		std::string tessEvaluationShader;
		std::string geometryShader;
		std::string fragmentShader;
		std::string computeShader;

		ShaderProgramInitDesc()
		{}
		ShaderProgramInitDesc(std::string _vertexShader, std::string _tessControllShader, std::string _tessEvaluationShader, std::string _geometryShader, std::string _fragmentShader, std::string _computeShader)
		{
			vertexShader			= _vertexShader	;
			tessControllShader		= _tessControllShader;
			tessEvaluationShader	= _tessEvaluationShader;
			geometryShader			= _geometryShader;
			fragmentShader			= _fragmentShader;
			computeShader			= _computeShader	;
		}
	};

public:
	ShaderProgram(const char* shaderProgramName = "unamed");
	virtual~ShaderProgram();

	int CreateShaderProgramFromFile(const ShaderProgramInitDesc& desc);
	int CreateShaderProgramFromSource(const ShaderProgramInitDesc& desc);

	void Release();

	//Sets the shader program to the gpu
	void UseShaderProgram();

	const std::string& GetErrorStr() const;

public:
	inline operator GLuint() { return shaderProgramHandle; }
	inline operator const char*() { return this->shaderProgramName; }
	inline operator std::string() { return this->shaderProgramName; }

private:
	GLuint CompileShaderFromSource(const std::string & source, ShaderType type);

	ShaderProgram(const ShaderProgram &other) { }
	ShaderProgram & operator=(const ShaderProgram &other) { return *this; }
	ShaderType _GetShaderExtension(const std::string &name);

private:
	GLuint shaderProgramHandle;
	const char* shaderProgramName;
	std::string lastError;
};


#endif // !SHADER_PROGRAM
