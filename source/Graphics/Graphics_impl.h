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
#else
	#pragma comment(lib, "BulletCollision.lib")
	#pragma comment(lib, "BulletDynamics.lib")
	#pragma comment(lib, "BulletSoftBody.lib")
	#pragma comment(lib, "LinearMath.lib")
#endif

#include "include/MinionGraphics.h"
#include "rendering/renderers/DeferredRenderer.h"
#include "rendering/renderers/GUIRenderer.h"
#include "rendering/renderers/ShadowMapRenderer.h"
#include "rendering/ShaderProgram.h"
#include "models/Model.h"
#include "GraphicsWindow.h"

#include <NoEdgeUtilities.h>
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <map>
#include <stdio.h>
#include <glew.h>
#include <vld.h>

using namespace Minion;

class Graphics_impl	:public MinionGraphics
{
public:
	Graphics_impl();
	virtual~Graphics_impl();

	virtual MinionErrorCode InitiateGraphics(MinionWindow* window) override;
	virtual void Release()override;

	virtual void QueueForRendering(MinionModel*) override;
	//virtual void QueueToScene(MinionGUI* g) override;
	//virtual void QueueToScene(MinionText* t) override;
	//virtual void QueueToScene(MinionScene* s) override;

	virtual void RenderGraphics() override;
	virtual void UpdateGraphics(float dt) override;

	MinionModel* CreateModel_FromFile(const char* file) override;
	MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) override;
	MinionModel* CreateModel_Cube(float width, float height, float depth) override;
	MinionModel* CreateModel_Sphere(float radius) override;
	MinionModel* CreateModel_Triangle(float height, float width) override;

	virtual const std::string& GetLastError() const override;

	void SetRenderWindow(MinionWindow* win) override;
	void SetClearColor(float r, float g, float b) override;
	void SetEnableLogging(bool toggle) override;

private:
	MinionErrorCode InitializeOpenGL();
	MinionErrorCode InitializeRenderers();
	static void glError_callback(int error, const char* description);

private:
	std::string errorstr;
	GraphicsWindow* window;
	
	//The renderers
	DeferredRenderer			deferredRenderer;
	ShadowMapRenderer			shadowmapRenderer;
	GUIRenderer					guiRenderer;

	//The models
	std::vector<Model*>			models;

	bool						graphicsIsInitiated;
	bool						logging;
};

#endif // !MINION_GRAPHICS
