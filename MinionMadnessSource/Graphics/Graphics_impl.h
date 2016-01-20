#ifndef GRAPHICS_IMPL_H
#define GRAPHICS_IMPL_H

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "Opengl32.lib")

#if defined(_DEBUG)
	#pragma comment(lib, "BulletCollision_Debug.lib")
	#pragma comment(lib, "BulletDynamics_Debug.lib")
	#pragma comment(lib, "BulletSoftBody_Debug.lib")
	#pragma comment(lib, "LinearMath_Debug.lib")
	#pragma comment(lib, "log4cpp_Debug.lib")
#else
	#pragma comment(lib, "BulletCollision.lib")
	#pragma comment(lib, "BulletDynamics.lib")
	#pragma comment(lib, "BulletSoftBody.lib")
	#pragma comment(lib, "LinearMath.lib")
	#pragma comment(lib, "log4cpp.lib")
#endif

#include "include/MinionGraphics.h"

#include <NoEdgeUtilities.h>
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <map>
#include <stdio.h>
#include <glew.h>
#include <vld.h>

#include "renderer/DeferredRenderer.h"
#include "renderer/ShadowMapRenderer.h"
#include "renderer/GUIRenderer.h"
#include "renderer/ShaderProgram.h"
#include "models/Model.h"

//Is already defines
#undef APIENTRY
#include "log4cpp\Appender.hh"
#include "log4cpp\AppendersFactory.hh"


class Graphics_impl	:public MinionGraphics
{
public:
	Graphics_impl();
	virtual~Graphics_impl();

	int InitiateMinionGraphics(const MinionGraphicsInitDesc&) override;
	void Release()override;
	const char* GetLastError()override;

	int SetOption(const char* option, ...) override;

	void BeginScene() override;
	void EndScene() override;

	void BeginGUI() override;
	void EndGUI() override;

	void BeginText() override;
	void EndText() override;

	MinionModel* CreateModel(const char* file) override;
	MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) override;
	MinionModel* CreateModel_Cube(float width, float height, float depth) override;
	MinionModel* CreateModel_Sphere(float radius) override;

private:
	Graphics_impl* GetInstancePointer();
	int InitializeOpenGL();
	int CreateShaders();
	static void glError_callback(int error, const char* description);

private:
	struct RendererOptions
	{
		int windowWidth, windowHeight;
		int windowX, windowY;
		const char* windowTitle;
		glm::vec3 backgroundColor;

		RendererOptions()
			: windowTitle("Untitled")
			, windowWidth(640)
			, windowHeight(480)
			, windowX(0)
			, windowY(0)
		{}
	};

private:
	RendererOptions options;
	const char* errorstr;
	GLFWwindow* window;
	
	DeferredRenderer deferredRenderer;
	ShadowMapRenderer shadowmapRenderer;
	GUIRenderer guiRenderer;

	std::map<const char*, ShaderProgram> shaders;
	std::vector<Model*> models;

	bool graphicsIsInitiated;
};

#endif // !MINION_GRAPHICS
