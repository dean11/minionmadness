#ifndef GRAPHICS_IMPL_H
#define GRAPHICS_IMPL_H

#include "include/MinionGraphics.h"
#include "rendering/renderers/DeferredRenderer.h"
#include "rendering/renderers/GUIRenderer.h"
#include "rendering/renderers/ShadowMapRenderer.h"
#include "rendering/ShaderProgram.h"
#include "models/Model.h"
#include "Window_impl.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <map>
#include <stdio.h>

#ifdef _MSC_VER
#include <vld.h>
#endif
#include <utilities.h>


using namespace minion;

namespace Defaults
{
	static void NotificationCallback(Enum::NotificationValue&, const char* msg) {}
}

class Graphics_impl	:public MinionGraphics
{
public:
	Graphics_impl();
	virtual~Graphics_impl();

	virtual void InitializeGraphics(MinionWindow** out_window, unsigned int width, unsigned int height, const char* title) override;

	virtual void QueueForRendering(MinionModel*) override;
	//virtual void QueueToScene(MinionGUI* g) override;
	//virtual void QueueToScene(MinionText* t) override;
	//virtual void QueueToScene(MinionScene* s) override;

	virtual void UpdateGraphics(long milliseconds) override;
	virtual void RenderGraphics() override;

	virtual MinionModel* CreateModel_FromFile(const char* file) override;
	virtual MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) override;
	virtual MinionModel* CreateModel_Cube(float width, float height, float depth) override;
	virtual MinionModel* CreateModel_Sphere(float radius) override;
	virtual MinionModel* CreateModel_Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3) override;
	
	virtual void System_SetClearColor(float r, float g, float b) override;
	virtual void System_SetDefaultCamera(std::shared_ptr<MinionCamera> camera) override;
	virtual void System_SetNotificationCallback(NotificationCallback callback) override;
	virtual MinionWindow* System_GetWindow() override;

protected:
	void InitializeWindow(unsigned int width, unsigned int height, const char* title);
	void InitializeOpenGL();
	void InitializeRenderers();

	static void glError_callback(int error, const char* description);

protected:
	Window_impl* window;

	std::shared_ptr<MinionCamera> defaultCamera;

	NotificationCallback notificationCallback;

	//The renderers
	DeferredRenderer			deferredRenderer;
	ShadowMapRenderer			shadowmapRenderer;
	GUIRenderer					guiRenderer;

	//The models
	std::vector<Model*>			models;

	bool						graphicsIsInitiated;
};

#endif // !MINION_GRAPHICS
