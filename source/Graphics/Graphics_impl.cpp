#include "Graphics_impl.h"

#include "models\Plane.h"
#include "models\Sphere.h"
#include "models\Cube.h"
#include "models\Mesh.h"
#include "models\Triangle.h"

#include <logger.h>

#include <NoEdgeUtilities.h>

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
		Logger::Debug(loggerName, message);
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
MinionGraphics* MinionGraphics::GetGraphicsHandle()
{
	if (!minionGraphicsPtr)
	{
		minionGraphicsPtr = new Graphics_impl();
	}

	minionGraphicsPtr_count++;
	
	return minionGraphicsPtr;
}
MinionGraphics::~MinionGraphics()
{

}

Graphics_impl::Graphics_impl()
{
	this->graphicsIsInitiated = false;
}
Graphics_impl::~Graphics_impl()
{
	this->graphicsIsInitiated = false;
}

MinionErrorCode Graphics_impl::InitiateGraphics(MinionWindow* window)
{
	if (!window)
		return MinionErrorCode_NoWindowSet;

	this->window = (GraphicsWindow*)window;

	MinionErrorCode result = MinionErrorCode_SUCESS;
	
	// Initiate OpenGL
	result = InitializeOpenGL();
	if (result != MinionErrorCode_SUCESS)
		return result;

	//Create Shaders
	result = this->InitializeRenderers();
	if (result != MinionErrorCode_SUCESS)
		return MinionErrorCode_FAIL;



	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glDebugMessageCallback(debug::glErrorCallback, this);

	return result;
}
void Graphics_impl::Release()
{
	minionGraphicsPtr_count--;

	if (minionGraphicsPtr_count == 0)
	{
		for (size_t i = 0; i < this->models.size(); i++)
		{
			this->models[i]->Release();
			delete this->models[i];
			this->models[i] = 0;
		}
		//Release resources
		glfwTerminate();
		this->window = 0;

		delete minionGraphicsPtr;
		minionGraphicsPtr = 0;

	}
}

void Graphics_impl::QueueForRendering(MinionModel* m)
{
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

void Graphics_impl::RenderGraphics()
{
	//Clear Previous stuff on backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////Save shadowmaps to texture
	//this->shadowmapRenderer.ProcessQueuedModels();
	//
	////Perform the geometry pass with the deferred renderer
	this->deferredRenderer.ExcecuteGeometryPass();
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
void Graphics_impl::UpdateGraphics(float dt)
{
	
}

MinionModel* Graphics_impl::CreateModel_FromFile(const char* file)
{
	std::string f = file;
	Mesh *m = new Mesh();
	if (m->CreateMesh(f))
	{
		this->models.push_back(m);
		return this->models[this->models.size() - 1];
	}
	else
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
MinionModel* Graphics_impl::CreateModel_Triangle(float height, float width)
{
	Model *m = new Triangle(height, width);
	this->models.push_back(m);
	return this->models[this->models.size() - 1];
}

const std::string& Graphics_impl::GetLastError() const
{
	return this->errorstr;
}

void Graphics_impl::SetRenderWindow(MinionWindow* win)
{
	this->window = (GraphicsWindow*)win;
	glfwMakeContextCurrent(*this->window);
}
void Graphics_impl::SetClearColor(float r, float g, float b)
{
	if (this->graphicsIsInitiated)
	{
		glClearColor(r, g, b, 1.0f);
	}
}
void Graphics_impl::SetEnableLogging(bool toggle)
{
	if (!this->logging)
	{
		this->logging = toggle;

		Logger::CreateLogger(loggerName.c_str(), "");
	}
}





/*****************************************************************************************/
/********************************* PRIVATE METHODS ***************************************/
/*****************************************************************************************/
MinionErrorCode Graphics_impl::InitializeOpenGL()
{
	if (this->graphicsIsInitiated)	return MinionErrorCode_SUCESS;
	if (glfwInit() == GL_FALSE)		return MinionErrorCode_FAIL;
	if (this->window == nullptr)	return MinionErrorCode_NoWindowSet;

	//We need to make sure the window is the current context before initializing
	
	glfwMakeContextCurrent(*this->window);

	//--------------- Initiate GLEW
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		this->errorstr = (const char*)glewGetErrorString(glewErr);
		if (this->logging)	Logger::Debug(loggerName, this->errorstr.c_str());
			return MinionErrorCode_FAIL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	this->graphicsIsInitiated = true;

	return MinionErrorCode_SUCESS;
}
MinionErrorCode Graphics_impl::InitializeRenderers()
{
	if (this->window)
	{ 
		if (this->deferredRenderer.Initialize(this->window->GetWidth(), this->window->GetHeight()) == 0)
		{
			this->errorstr = this->deferredRenderer.GetErrorStr();
			if (this->logging)	Logger::Debug(loggerName, this->errorstr.c_str());
			debug::StdStreamPrint(this->errorstr.c_str());
			return MinionErrorCode_FAIL;
		}
		//this->guiRenderer;
		//this->shadowmapRenderer;
	}
	return MinionErrorCode_SUCESS;
}
