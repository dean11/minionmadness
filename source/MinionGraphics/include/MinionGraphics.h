#ifndef MINIONGRAPHICS_H
#define MINIONGRAPHICS_H

#include "MinionModel.h"
#include "MinionWindow.h"
#include "MinionMath.h"
#include "MinionCamera.h"

#include <string>
#include <functional>

namespace minion
{
	namespace Enum
	{
		enum NotificationValue
		{
			NoDefaultRenderingCameraSet,
		};
	}
	typedef std::function<void(Enum::NotificationValue&, const char* msg)> NotificationCallback;

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
		virtual void InitializeGraphics(MinionWindow** out_window, unsigned int width = 640, unsigned int height = 420, const char* title = "MininonGraphics") = 0;

		virtual void QueueForRendering(MinionModel*) = 0;
		//virtual void QueueForRendering(MinionGUI* g) = 0;
		//virtual void QueueForRendering(MinionText* t) = 0;
		//virtual void QueueForRendering(MinionScene* s) = 0;

		virtual void UpdateGraphics(long milliseconds) = 0;
		virtual void RenderGraphics() = 0;

		virtual MinionModel* CreateModel_FromFile(const char* file) = 0;
		virtual MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) = 0;
		virtual MinionModel* CreateModel_Cube(float width, float height, float depth) = 0;
		virtual MinionModel* CreateModel_Sphere(float radius) = 0;
		virtual MinionModel* CreateModel_Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3) = 0;

	public:
		virtual void System_SetClearColor(float r, float g, float b) = 0;
		virtual void System_SetDefaultCamera(std::shared_ptr<MinionCamera> camera) = 0;
		virtual void System_SetNotificationCallback(NotificationCallback callback) = 0;
		virtual MinionWindow* System_GetWindow() = 0;

	};

	class MinionGraphicsException :public std::runtime_error
	{
	public:
		enum ErrorCode
		{
			ErrorCode_FailedToInitializeGLFW,
			ErrorCode_FailedToInitializeRenderWindow,
			ErrorCode_FailedToInitializeGraphics,
			ErrorCode_FailedToInitializeRenderer,
			ErrorCode_FailedToInitializeGLEW,

			ErrorCode_END
		};
	public:
		MinionGraphicsException(const char* msg, ErrorCode code);
		MinionGraphicsException(ErrorCode code);
		virtual~MinionGraphicsException();

		friend std::ostream& operator<<(std::ostream& os, const MinionGraphicsException& obj);

		const char* ToText(ErrorCode code) const;
	private:
		ErrorCode code;
	};
}


#endif // !MINIONGRAPHICS
