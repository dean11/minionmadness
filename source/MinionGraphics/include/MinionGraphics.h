#ifndef MINIONGRAPHICS_H
#define MINIONGRAPHICS_H

#include "MinionModel.h"
#include "MinionWindow.h"

#include <string>
#include <functional>

namespace Minion
{
	/*
	*	Error-codes
	*/
	enum MinionErrorCode
	{
		MinionErrorCode_FAIL,
		MinionErrorCode_SUCESS,
	};
	/*
	*	To get a reference of MinionGraphics, use the static function GetGraphicsPointer();
	*	Don't forget to releas is when done.
	*/
	class MinionGraphics
	{
	public:
		static void GetGraphicsHandle(MinionGraphics** graphicsHandlerPtr);
		static void ReleaseGraphicsHandle(MinionGraphics** graphicsHandlerPtr);

	protected:
		virtual ~MinionGraphics();

	public:
		virtual MinionErrorCode InitializeRenderWindow(MinionWindow** out_window, unsigned int width = 640, unsigned int height = 420, const char* title = "MininonGraphics") = 0;

		virtual void QueueForRendering(MinionModel*) = 0;
		//virtual void QueueForRendering(MinionGUI* g) = 0;
		//virtual void QueueForRendering(MinionText* t) = 0;
		//virtual void QueueForRendering(MinionScene* s) = 0;

		virtual void UpdateGraphics(float dt) = 0;
		virtual void RenderGraphics() = 0;

		virtual MinionModel* CreateModel_FromFile(const char* file) = 0;
		virtual MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) = 0;
		virtual MinionModel* CreateModel_Cube(float width, float height, float depth) = 0;
		virtual MinionModel* CreateModel_Sphere(float radius) = 0;
		virtual MinionModel* CreateModel_Triangle(float height, float width) = 0;

		virtual const std::string& GetLastError() const = 0;

		virtual void SetClearColor(float r, float g, float b) = 0;
		virtual void SetEnableLogging(bool toggle) = 0;

		virtual MinionWindow* GetWindow() = 0;

	};
}


#endif // !MINIONGRAPHICS
