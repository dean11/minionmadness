#include "ShaderProgram.h"

#include <string>
#include <utilities.h>
#include <map>

#include "../include/MinionExeptions.h"



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


void ShaderProgram::CreateShaderProgramFromFile(const ShaderProgramInitDesc& shaders)
{
	this->initDesc = shaders;

	ShaderProgramInitDesc source;
//Compute Shader
	if (shaders.computeShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.computeShader.c_str(), source.computeShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.computeShader).c_str(), ErrorCode_Failed);

//Fragment Shader
	if (shaders.fragmentShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.fragmentShader.c_str(), source.fragmentShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.fragmentShader).c_str(), ErrorCode_Failed);

//Geometry Shader
	if (shaders.geometryShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.geometryShader.c_str(), source.geometryShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.geometryShader).c_str(), ErrorCode_Failed);

//Tess Control Shader
	if (shaders.tessControllShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.tessControllShader.c_str(), source.tessControllShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.tessControllShader).c_str(), ErrorCode_Failed);

//Tess Evaluation Shader
	if (shaders.tessEvaluationShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.tessEvaluationShader.c_str(), source.tessEvaluationShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.tessEvaluationShader).c_str(), ErrorCode_Failed);

//Vertex Shader
	if (shaders.vertexShader.size() && utilities::Stream::ReadFileContentAsByte(shaders.vertexShader.c_str(), source.vertexShader) == 0)
		throw ShaderProgramException(("Failed to read file: " + shaders.vertexShader).c_str(), ErrorCode_Failed);

	try
	{
		CreateShaderProgramFromString(source);
	}
	catch (ShaderProgramException& e)
	{
		switch (e.type)
		{
		case ShaderProgram::ShaderType_vertex:
			e.path = shaders.vertexShader;
			break;
		case ShaderProgram::ShaderType_tessControl:
			e.path = shaders.tessControllShader;
			break;
		case ShaderProgram::ShaderType_tessEvaluation:
			e.path = shaders.tessEvaluationShader;
			break;
		case ShaderProgram::ShaderType_geometry:
			e.path = shaders.geometryShader;
			break;
		case ShaderProgram::ShaderType_fragment:
			e.path = shaders.fragmentShader;
			break;
		case ShaderProgram::ShaderType_compute:
			e.path = shaders.computeShader;
			break;
		}

		throw e;
	}
}
void ShaderProgram::CreateShaderProgramFromString(const ShaderProgramInitDesc& source)
{
	this->initDesc = source;

	std::vector<ShaderInfo::ShaderCompileTypeInfo> toCompile;

	if (source.computeShader.size()) toCompile.push_back({ source.computeShader, ShaderType_compute });
	if (source.fragmentShader.size()) toCompile.push_back({ source.fragmentShader, ShaderType_fragment });
	if (source.geometryShader.size()) toCompile.push_back({ source.geometryShader, ShaderType_geometry });
	if (source.tessControllShader.size()) toCompile.push_back({ source.tessControllShader, ShaderType_tessControl });
	if (source.tessEvaluationShader.size()) toCompile.push_back({ source.tessEvaluationShader, ShaderType_tessEvaluation });
	if (source.vertexShader.size()) toCompile.push_back({ source.vertexShader, ShaderType_vertex });

	if (toCompile.size() == 0)
		throw ShaderProgramException("No Shaders to compile", ErrorCode_NoShaders);

	//Create the shader program handle
	if (this->shaderProgramHandle == 0 && (this->shaderProgramHandle = glCreateProgram()) == 0)
		throw ShaderProgramException("Failed to create gl shader program handle", ErrorCode_Failed);

	// Compile and attach the shaders to the program handle
	std::vector<GLuint> compiledShaders;
	for (size_t i = 0; i < toCompile.size(); i++)
	{
		GLuint shader = 0;
		if ((shader = CompileShaderFromSource(toCompile[i].source, toCompile[i].shaderType)) == 0)
			throw ShaderProgramException("Failed to create gl shader program handle", ErrorCode_Failed);

		compiledShaders.push_back(shader);
		glAttachShader(this->shaderProgramHandle, shader);
	}

	//Link the program
	glLinkProgram(this->shaderProgramHandle);


	// Check the program
	GLint linked = GL_FALSE;
	int logLen;
	glGetProgramiv(this->shaderProgramHandle, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		std::string errorMessage;
		glGetProgramiv(this->shaderProgramHandle, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			errorMessage.resize(logLen + 1);
			glGetProgramInfoLog(this->shaderProgramHandle, logLen, NULL, &errorMessage[0]);
			throw ShaderProgramException(("Failed to create the shader\n\t " + errorMessage).c_str(), ErrorCode_Failed);
		}
		throw ShaderProgramException("Failed to create the shader", ErrorCode_Failed);
	}

	////Release shaders that is already linked and attached to the program handle
	//for (size_t i = 0; i < compiledShaders.size(); i++)
	//{
	//	glDetachShader(this->shaderProgramHandle, compiledShaders[i]);
	//	glDeleteShader(compiledShaders[i]);
	//}
}
GLuint ShaderProgram::CompileShaderFromSource(const std::string & source, ShaderType type)
{
	const char *c_str = source.c_str();
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	//Check compile status and errors
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		int logLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			std::string tmpStr;
			tmpStr.resize(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, &tmpStr[0]);

			throw ShaderProgramException(tmpStr.c_str(), ErrorCode_FailedToCompile, type);
		}

		throw ShaderProgramException("Failed to compile the shader", ErrorCode_FailedToCompile, type);
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

std::string ShaderProgram::ToString(ShaderType type)
{
	std::map<ShaderType, const char*> typeStrings = 
	{
		{ ShaderType_vertex, "Vertex" },
		{ ShaderType_tessControl, "Tesselation Control" },
		{ ShaderType_tessEvaluation, "Tesselation Evaluation" },
		{ ShaderType_geometry, "Geometry" },
		{ ShaderType_fragment, "Fragment" },
		{ ShaderType_compute, "Compute" }
	};

	return typeStrings.at(type);
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
		for (unsigned int i = 0; i < utilities::StaticArray::NumElementsOf(ShaderInfo::extensions); i++)
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

