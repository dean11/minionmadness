#include "ShaderProgram.h"

#include <string>
#include <NoEdgeUtilities.h>


ShaderProgram::ShaderProgram()
{
	this->shaderProgram = 0;
}
ShaderProgram::~ShaderProgram()
{

}

int ShaderProgram::LoadShaderFromFile(const char* file, ShaderType shaderType)
{
	if (!file || !strcmp(file, "")) return -1;

	std::string buff;
	if (NoEdgeUtilies::Stream::ReadFileContentAsByte(file, buff))
	{
		const GLchar* arr[] = { buff.c_str() };
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, arr, NULL);
		glCompileShader(shader);

		//Check compile status
		GLint res;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
		if (res == GL_FALSE)
		{
			fprintf(stderr, "Failed to compile shader");
			int logLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				std::string log;
				log.resize(logLen);
				GLsizei written;
				glGetShaderInfoLog(shader, logLen, &written, &log[0]);
				fprintf(stderr, "Shader log:\n", log.c_str());
			}
		}
		else
		{
			glAttachShader(this->shaderProgram, shader);
			return 1;
		}
	}
	return 0;
}
int ShaderProgram::Create(ShaderInitDesc& desc)
{
	this->shaderProgram = glCreateProgram();
	GLuint shader = 0;

	if (LoadShaderFromFile(desc.vertexShader_path.c_str(), ShaderType_vertex) == 0)				
		return false;
		
	if (LoadShaderFromFile(desc.fragmentShader_path.c_str(), ShaderType_fragment) == 0)
		return false;

	if (LoadShaderFromFile(desc.computeShader_path.c_str(), ShaderType_compute) == 0)
		return false;
		
	if (LoadShaderFromFile(desc.tessControl_path.c_str(), ShaderType_tessControl) == 0)
		return false;
		
	if (LoadShaderFromFile(desc.tessEvaluation_path.c_str(), ShaderType_tessEvaluation) == 0)
		return false;
		
	if (LoadShaderFromFile(desc.geometryShader_path.c_str(), ShaderType_geometry) == 0)
		return false;

	return true;
}

void ShaderProgram::Release()
{

}