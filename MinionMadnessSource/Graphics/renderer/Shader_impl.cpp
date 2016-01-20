#include "../Graphics_impl.h"

namespace
{
	struct ShaderProgrammeDesc
	{
		const char* shaderName;
		const char* vert;
		const char* tess_cont;
		const char* tess_eval;
		const char* geom;
		const char* frag;
		const char* comp;
	};
	static const ShaderProgrammeDesc shaderPrograms[] =
	{
		{ "basic", "basic_vs.glsl", 0, 0, 0, "basic_fs.glsl", 0 },
	};
}

int Graphics_impl::CreateShaders()
{
	this->numberOfShaders = NoEdgeUtilies::StaticArray::NumElementsOf(shaderPrograms);

	for (unsigned int i = 0; i < numberOfShaders; i++)
	{
		ShaderProgram p;
		ShaderProgram::ShaderInitDesc desc;
		std::string dir = options.shaderDirectory;

		if (shaderPrograms[i].comp)				desc.computeShader_path.append(dir + shaderPrograms[i].comp);
		if (shaderPrograms[i].frag)				desc.fragmentShader_path.append(dir + shaderPrograms[i].frag);
		if (shaderPrograms[i].geom)				desc.geometryShader_path.append(dir + shaderPrograms[i].geom);
		if (shaderPrograms[i].tess_cont)		desc.tessControl_path.append(dir + shaderPrograms[i].tess_cont);
		if (shaderPrograms[i].tess_eval)		desc.tessEvaluation_path.append(dir + shaderPrograms[i].tess_eval);
		if (shaderPrograms[i].vert)				desc.vertexShader_path.append(dir + shaderPrograms[i].vert);

		if (p.Create(desc) == 0)
			continue;

		//Save shader
		this->shaders[shaderPrograms[i].shaderName] = p;
	}
	return 0;
}