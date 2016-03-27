#include "ShaderProgram.h"

#include <string>
#include <NoEdgeUtilities.h>



namespace ShaderInfo {
	struct ShaderCompileTypeInfo
	{
		const std::string& source;
		ShaderProgram::ShaderType shaderType;
	};
	struct shader_file_extension 
	{
		const char *ext;
		ShaderProgram::ShaderType type;
	};

	struct shader_file_extension extensions[] =
	{
		{ ".vs", ShaderProgram::ShaderType_vertex },
		{ ".vert", ShaderProgram::ShaderType_vertex },
		{ ".gs", ShaderProgram::ShaderType_geometry },
		{ ".geom", ShaderProgram::ShaderType_geometry },
		{ ".tcs", ShaderProgram::ShaderType_tessControl },
		{ ".tes", ShaderProgram::ShaderType_tessEvaluation },
		{ ".fs", ShaderProgram::ShaderType_fragment },
		{ ".frag", ShaderProgram::ShaderType_fragment },
		{ ".cs", ShaderProgram::ShaderType_compute }
	};
}


ShaderProgram::ShaderProgram(const char* name)
{
	this->shaderProgramHandle = 0;
	this->shaderProgramName = name;
}
ShaderProgram::~ShaderProgram()
{

}


int ShaderProgram::CreateShaderProgramFromFile(const ShaderProgramInitDesc& shaders)
{
	ShaderProgramInitDesc source;

//Compute Shader
	if (shaders.computeShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.computeShader.c_str(), source.computeShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.computeShader;
		return 0;
	}

//Fragment Shader
	if (shaders.fragmentShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.fragmentShader.c_str(), source.fragmentShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.fragmentShader;
		return 0;
	}

//Geometry Shader
	if (shaders.geometryShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.geometryShader.c_str(), source.geometryShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.geometryShader;
		return 0;
	}

//Tess Control Shader
	if (shaders.tessControllShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.tessControllShader.c_str(), source.tessControllShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.tessControllShader;
		return 0;
	}

//Tess Evaluation Shader
	if (shaders.tessEvaluationShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.tessEvaluationShader.c_str(), source.tessEvaluationShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.tessEvaluationShader;
		return 0;
	}

//Vertex Shader
	if (shaders.vertexShader.size() && NoEdgeUtilies::Stream::ReadFileContentAsByte(shaders.vertexShader.c_str(), source.vertexShader) == 0)
	{
		this->lastError = "Failed to read file: " + shaders.vertexShader;
		return 0;
	}

	return CreateShaderProgramFromSource(source);
}
int ShaderProgram::CreateShaderProgramFromSource(const ShaderProgramInitDesc& source)
{
	std::vector<ShaderInfo::ShaderCompileTypeInfo> toCompile;

	if (source.computeShader.size()) toCompile.push_back({ source.computeShader, ShaderType_compute });
	if (source.fragmentShader.size()) toCompile.push_back({ source.fragmentShader, ShaderType_fragment });
	if (source.geometryShader.size()) toCompile.push_back({ source.geometryShader, ShaderType_geometry });
	if (source.tessControllShader.size()) toCompile.push_back({ source.tessControllShader, ShaderType_tessControl });
	if (source.tessEvaluationShader.size()) toCompile.push_back({ source.tessEvaluationShader, ShaderType_tessEvaluation });
	if (source.vertexShader.size()) toCompile.push_back({ source.vertexShader, ShaderType_vertex });

	if (toCompile.size() == 0)
		return 0;

	//Create the shader program handle
	if (this->shaderProgramHandle == 0)
	{
		this->shaderProgramHandle = glCreateProgram();
		if (this->shaderProgramHandle == 0)
		{
			this->lastError = "Failed to create gl shader program";
			return 0;
		}
	}

	// Compile and attach the shaders to the program handle
	std::vector<GLuint> compiledShaders;
	for (size_t i = 0; i < toCompile.size(); i++)
	{
		GLuint shader = CompileShaderFromSource(toCompile[i].source, toCompile[i].shaderType);
		if (shader == 0)
			return 0;

		compiledShaders.push_back(shader);
		glAttachShader(this->shaderProgramHandle, compiledShaders[i]);
	}

	//Link the program
	glLinkProgram(this->shaderProgramHandle);


	// Check the program
	GLint Result = GL_FALSE;
	int logLen;
	glGetProgramiv(this->shaderProgramHandle, GL_LINK_STATUS, &Result);
	glGetProgramiv(this->shaderProgramHandle, GL_INFO_LOG_LENGTH, &logLen);
	if (Result == GL_FALSE && logLen > 0)
	{
		std::string errorMessage;
		errorMessage.resize(logLen + 1);
		glGetProgramInfoLog(this->shaderProgramHandle, logLen, NULL, &errorMessage[0]);
		this->lastError = errorMessage;
		return 0;
	}

	//Release shaders that is already linked and attached to the program handle
	for (size_t i = 0; i < compiledShaders.size(); i++)
	{
		glDetachShader(this->shaderProgramHandle, compiledShaders[i]);
		glDeleteShader(compiledShaders[i]);
	}

	return 1;
}
GLuint ShaderProgram::CompileShaderFromSource(const std::string & source, ShaderType type)
{
	const GLchar* arr[] = { source.c_str() };
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, arr, NULL);
	glCompileShader(shader);

	//Check compile status and errors
	GLint res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int logLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			std::string tmpStr;
			tmpStr.resize(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, &tmpStr[0]);
			
			this->lastError = tmpStr;
		}

		return 0;
	}

	return shader;
}

void ShaderProgram::Release()
{ 
	glDeleteShader(this->shaderProgramHandle);
	this->shaderProgramHandle = 0;
}

void ShaderProgram::UseShaderProgram()
{
	glUseProgram(this->shaderProgramHandle);
	
}
const std::string& ShaderProgram::GetErrorStr() const
{
	return this->lastError;
}

ShaderProgram::ShaderType ShaderProgram::_GetShaderExtension(const std::string &name)
{
	ShaderType type = ShaderType_Undefined;

	std::string nameStr(name);
	std::string ext = "";
	size_t loc = nameStr.find_last_of('.');
	if (loc != std::string::npos) 
	{
		ext = nameStr.substr(loc, std::string::npos);
		for (unsigned int i = 0; i < NoEdgeUtilies::StaticArray::NumElementsOf(ShaderInfo::extensions); i++)
		{
			if (ext == ShaderInfo::extensions[i].ext)
			{
				type = ShaderInfo::extensions[i].type;
				break;
			}
		}
	}
	return type;
}

