#include "Graphics_impl.h"

#include "models/Plane.h"
#include "models/Sphere.h"
#include "models/Cube.h"
#include "models/Mesh.h"
#include "models/Triangle.h"

#include <utilities.h>

#include <string>
#include <stdarg.h> 
#include <memory>



Graphics_impl *minionGraphicsPtr = nullptr;
int minionGraphicsPtr_count = 0;
const std::string loggerName = "MinionGraphics";


namespace debug
{
	void GLAPIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		//Logger::Debug(loggerName, message);
	}

	#ifdef DEBUG_DEVEL
	void StdStreamPrint(const char*  format, ...)
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
	#else
	void StdStreamPrint(const char*  format, ...){}
	#endif
}


// Method implemented from the MinionGraphics.h interface
void MinionGraphics::GetGraphicsHandle(MinionGraphics** graphicsHandlerPtr)
{
	if (!minionGraphicsPtr)
	{
		minionGraphicsPtr = new Graphics_impl();
	}

	minionGraphicsPtr_count++;
	
	*graphicsHandlerPtr = minionGraphicsPtr;
}
void MinionGraphics::ReleaseGraphicsHandle(MinionGraphics** graphicsHandlerPtr)
{
	if (!(*graphicsHandlerPtr))
		return;

	*graphicsHandlerPtr = nullptr;
	minionGraphicsPtr_count--;

	if (minionGraphicsPtr_count == 0)
	{
		delete minionGraphicsPtr;
		minionGraphicsPtr = 0;

	}
}
MinionGraphics::~MinionGraphics()
{

}
// ----------------------------------------------------------------------



Graphics_impl::Graphics_impl()
{
	this->graphicsIsInitiated = false;
}
Graphics_impl::~Graphics_impl()
{
	for (size_t i = 0; i < this->models.size(); i++)
	{
		this->models[i]->Release();
		delete this->models[i];
		this->models[i] = 0;
	}
	
	delete this->window;
	
	glfwTerminate();
}

void Graphics_impl::InitializeGraphics(MinionWindow** out_RenderWindow, unsigned int width, unsigned int height, const char* title)
{
	// Initialize window
	InitializeWindow(width, height, title);
	(*out_RenderWindow) = this->window;

	// Initialize OpenGL
	InitializeOpenGL();

	//Initialize Shaders
	InitializeRenderers();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	#if defined DEBUG || defined _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(debug::glErrorCallback, this);
	#endif

	/*Logger::Debug(loggerName, (char*)glGetString(GL_VERSION));
	Logger::Debug(loggerName, (char*)glGetString(GL_VENDOR));*/
}

void Graphics_impl::QueueForRendering(MinionModel* minionModel)
{
	Model* m = (Model*)minionModel;
	if (m->ShouldRender())
	{
		this->deferredRenderer.QueueModel((Model*)m);
	}
	if (m->ShouldCastShadow())
	{
		this->shadowmapRenderer.QueueModel((Model*)m);
	}
	if (m->ShouldAnimate())
	{
		
	}
	if (m->ShouldCollide())
	{
		
	}
}
//void Graphics_impl::QueueToScene(MinionGUI* g)
//{
//	
//}
//void Graphics_impl::QueueToScene(MinionText* t)
//{
//
//}
//void Graphics_impl::QueueToScene(MinionScene* s)
//{
//
//}

void Graphics_impl::UpdateGraphics(long milliseconds)
{

}
void Graphics_impl::RenderGraphics()
{
	//Clear Previous stuff on backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!this->defaultCamera)
		// Event callback?
		return;

	////Save shadowmaps to texture
	//this->shadowmapRenderer.ProcessQueuedModels();
	//
	////Perform the geometry pass with the deferred renderer
	this->deferredRenderer.ExcecuteGeometryPass(this->defaultCamera);
	//
	////Add lighting to the scene
	//this->deferredRenderer.ExcecuteLightPass();
	//
	////Final pass in deferred renders to final texture on backbuffer.
	//this->deferredRenderer.ExcecuteFinalPass();
	//
	////Forward rendererer to render transparency and stuff
	//
	////Render GUI on top
	//this->guiRenderer;
	
	//Present the scene by swapping with backbuffer
	if (this->window)
		glfwSwapBuffers(*this->window);
}

MinionModel* Graphics_impl::CreateModel_FromFile(const char* file)
{
	std::string f = file;
	Mesh *m = new Mesh();
	try
	{
		m->CreateMesh(f);

		this->models.push_back(m);
		return this->models[this->models.size() - 1];
	}
	catch (...)
	{
		delete m;
	}
	return 0;
}
MinionModel* Graphics_impl::CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax, float tmax, const char* diffuseTexture)
{
	Model *m = new Plane(xsize, zsize, xdivs, zdivs, smax, tmax);

	if (!m)		
		return nullptr;

	this->models.push_back(m);
	return this->models[this->models.size() - 1];
}
MinionModel* Graphics_impl::CreateModel_Cube(float width, float height, float depth)
{
	Model *m = new Cube(width, height, depth);
	this->models.push_back(m);
	return this->models[this->models.size() - 1];
}
MinionModel* Graphics_impl::CreateModel_Sphere(float radius)
{
	Model *m = new Sphere(radius);
	this->models.push_back(m);
	return this->models[this->models.size() - 1];
}	
MinionModel* Graphics_impl::CreateModel_Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
	Model *m = new Triangle(v1, v2, v3);
	this->models.push_back(m);
	return this->models[this->models.size() - 1];
}


void Graphics_impl::System_SetClearColor(float r, float g, float b)
{
	if (this->graphicsIsInitiated)
	{
		glClearColor(r, g, b, 1.0f);
	}
}
void Graphics_impl::System_SetDefaultCamera(std::shared_ptr<MinionCamera> camera)
{
	this->defaultCamera = camera;
}
void Graphics_impl::System_SetNotificationCallback(NotificationCallback callback)
{
	this->notificationCallback = callback ? callback : Defaults::NotificationCallback;
}
MinionWindow* Graphics_impl::System_GetWindow()
{
	return this->window;
}




/*****************************************************************************************/
/********************************* PRIVATE METHODS ***************************************/
/*****************************************************************************************/
void Graphics_impl::InitializeWindow(unsigned int width, unsigned int height, const char* title)
{
	//Use gflw to create window
	/* Initialize the library */
	if (glfwInit() == GLFW_FALSE)
	{
		(*window) = nullptr;
		throw MinionGraphicsException("Failed to initialize GLFW!", MinionGraphicsException::ErrorCode_FailedToInitializeGLFW);
	}
	
	/* Creates a windowed mode window and its OpenGL context */
	GLFWwindow *glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	
	if (!glfwWindow)
	{
		glfwTerminate();
		(*window) = nullptr;
		throw MinionGraphicsException("Failed to initialize render window!", MinionGraphicsException::ErrorCode_FailedToInitializeRenderWindow);
	}

	glfwMakeContextCurrent(glfwWindow);

	this->window = new Window_impl(glfwWindow);

}
void Graphics_impl::InitializeOpenGL()
{
	if (!this->window)
		throw MinionGraphicsException("No window created. Must create a window before initializing graphics.", MinionGraphicsException::ErrorCode_FailedToInitializeGraphics);

	if (this->graphicsIsInitiated)	return;
	
	//We need to make sure the window is the current context before initializing
	glfwMakeContextCurrent(*this->window);

	//--------------- Initiate GLEW
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		//if (this->logging)	Logger::Debug(loggerName, (const char*)glewGetErrorString(glewErr));
		throw MinionGraphicsException((const char*)glewGetErrorString(glewErr), MinionGraphicsException::ErrorCode_FailedToInitializeGLEW);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	this->graphicsIsInitiated = true;
}
void Graphics_impl::InitializeRenderers()
{
	try
	{
		if (this->window)
		{
			this->deferredRenderer.Initialize(this->window->GetWidth(), this->window->GetHeight());
			//this->guiRenderer;
			//this->shadowmapRenderer;
		}
	}
	catch (ShaderProgramException& e)
	{
		std::string tmp = "PATH: " + e.path;
		tmp += "\n";
		tmp += "WHAT: " + std::string(e.what());
		tmp += "\n";
		throw MinionGraphicsException(tmp.c_str(), MinionGraphicsException::ErrorCode_FailedToInitializeRenderer);
	}
}
