#ifndef GRAPHICS_IMPL_H
#define GRAPHICS_IMPL_H

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>

#include <map>
#include <stdio.h>

#ifdef _MSC_VER
#include <vld.h>
#endif
#include <NoEdgeUtilities.h>

#include "autolink_windows.h"

#include "include/MinionGraphics.h"
#include "rendering/renderers/DeferredRenderer.h"
#include "rendering/renderers/GUIRenderer.h"
#include "rendering/renderers/ShadowMapRenderer.h"
#include "rendering/ShaderProgram.h"
#include "models/Model.h"
#include "Window_impl.h"


using namespace Minion;

class Graphics_impl	:public MinionGraphics
{
public:
	Graphics_impl();
	virtual~Graphics_impl();

	virtual MinionErrorCode InitializeRenderWindow(MinionWindow** out_window, unsigned int width, unsigned int height, const char* title) override;

	virtual void QueueForRendering(MinionModel*) override;
	//virtual void QueueToScene(MinionGUI* g) override;
	//virtual void QueueToScene(MinionText* t) override;
	//virtual void QueueToScene(MinionScene* s) override;

	void UpdateGraphics(float dt) override;
	void RenderGraphics() override;

	MinionModel* CreateModel_FromFile(const char* file) override;
	MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) override;
	MinionModel* CreateModel_Cube(float width, float height, float depth) override;
	MinionModel* CreateModel_Sphere(float radius) override;
	MinionModel* CreateModel_Triangle(float height, float width) override;

	virtual const std::string& GetLastError() const override;

	void SetClearColor(float r, float g, float b) override;
	void SetEnableLogging(bool toggle) override;

	virtual MinionWindow* GetWindow() override;

private:
	MinionErrorCode InitializeWindow(unsigned int width, unsigned int height, const char* title);
	MinionErrorCode InitializeOpenGL();
	MinionErrorCode InitializeRenderers();

	static void glError_callback(int error, const char* description);

private:
	std::string errorstr;
	Window_impl* window;
	
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
