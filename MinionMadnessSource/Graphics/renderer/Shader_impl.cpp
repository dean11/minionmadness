#include "../Graphics_impl.h"


namespace
{
	static const ShaderProgram::ShaderProgramDesc shaderPrograms[] =
	{
		{ "basic", "basic_vs.glsl", 0, 0, 0, "basic_fs.glsl", 0 },
		{ "deferredGather", "deferredGather_vs.glsl", 0, 0, 0, "deferredGather_fs.glsl", 0 },
		{ "deferredRender", "deferredRender_vs.glsl", 0, 0, 0, "deferredRender_fs.glsl", 0 },
	};
}

int Graphics_impl::CreateShaders()
{
	unsigned int numberOfShaders = NoEdgeUtilies::StaticArray::NumElementsOf(shaderPrograms);

	for (unsigned int i = 0; i < numberOfShaders; i++)
	{
		ShaderProgram p;

		if (p.Create(shaderPrograms[i]) == 0)
		{
			//log shader error
			continue;
		}

		//Save shader
		this->shaders[shaderPrograms[i].shaderName] = p;
	}
	return 0;
}