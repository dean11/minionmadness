#include "Graphics_impl.h"

#include "models\Plane.h"
#include "models\Sphere.h"
#include "models\Cube.h"
#include "models\Mesh.h"

#include <NoEdgeUtilities.h>

#include <string>
#include <stdarg.h> 
#include <memory>


Graphics_impl *minionGraphicsPtr = nullptr;
int minionGraphicsPtr_count = 0;


// Method implemented from the MinionGraphics.h interface
MinionGraphics* MinionGraphics::GetGraphicsPointer()
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
	this->errorstr = 0;
	this->graphicsIsInitiated = false;
}
Graphics_impl::~Graphics_impl()
{
	this->graphicsIsInitiated = false;
}

int Graphics_impl::InitiateMinionGraphics(const MinionGraphicsInitDesc& desc)
{
	this->options.windowTitle = desc.windowName;
	this->options.windowWidth = desc.windowWidth;
	this->options.windowHeight = desc.windowHeight;
	this->options.windowX = desc.windowX;
	this->options.windowY = desc.windowY;
	this->options.backgroundColor = glm::vec3(0.2f, 0.2f, 1.0f);

	InitializeOpenGL();

	return 1;
}
int Graphics_impl::InitializeOpenGL()
{
	if (this->graphicsIsInitiated)
	{
		return 2;
	}

	glfwSetErrorCallback(glError_callback);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	this->window = glfwCreateWindow(this->options.windowWidth, this->options.windowHeight, this->options.windowTitle, NULL, NULL);
	glfwSetWindowPos(this->window, this->options.windowX, this->options.windowY);

	if (!this->window)
	{
		glfwTerminate();
		return 0;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(this->window);

	//--------------- Initiate GLEW
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		this->errorstr = (const char*)glewGetErrorString(glewErr);
		return 0;
	}

	//Create Shaders
	if (this->CreateShaders() == 0)
		return 0;

	this->graphicsIsInitiated = true;

	return 1;
}

void Graphics_impl::Release()
{
	minionGraphicsPtr_count--;

	if (minionGraphicsPtr_count == 0)
	{
		//Release resources
		glfwTerminate();
		glfwDestroyWindow(this->window);
		this->window = 0;

		delete minionGraphicsPtr;
		minionGraphicsPtr = 0;

	}
}
const char* Graphics_impl::GetLastError()
{
	return this->errorstr;
}

int Graphics_impl::SetOption(const char* option, ...)
{
	std::string p = option;
	va_list vl;
	va_start(vl, option);

	if (p == "winSize")
	{
		this->options.windowWidth = va_arg(vl, int);
		this->options.windowHeight = va_arg(vl, int);

		if (this->window)
		{
			glfwSetWindowSize(this->window, this->options.windowWidth, this->options.windowHeight);
		}
	}
	else if (p == "winTitle")
	{
		this->options.windowTitle = va_arg(vl, const char*);
	}
	else if (p == "winPos")
	{
		this->options.windowX = va_arg(vl, int);
		this->options.windowY = va_arg(vl, int);
	}
	else if (p == "bgCol")
	{
		this->options.backgroundColor[0] = (float)va_arg(vl, double);
		this->options.backgroundColor[1] = (float)va_arg(vl, double);
		this->options.backgroundColor[2] = (float)va_arg(vl, double);
	}
	else
	{
		this->errorstr = "That option does not exist!";
		return -1;
	}
	va_end(vl);

	return 1;
}

void Graphics_impl::BeginScene()
{
	glClearColor(this->options.backgroundColor[0], this->options.backgroundColor[1], this->options.backgroundColor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Graphics_impl::EndScene()
{
	/*
	*	render to shadowmaps
	*	render to rendertargets
	*	render transparent
	*	render GUI
	*	render text
	*	Present final image
	*/
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}
void Graphics_impl::BeginGUI()
{

}
void Graphics_impl::EndGUI()
{

}
void Graphics_impl::BeginText()
{

}
void Graphics_impl::EndText()
{

}
MinionModel* Graphics_impl::CreateModel(const char* file)
{
	Model *m = new Mesh(file);
	this->models.push_back(m);
	return this->models[this->models.size() - 1];
	return 0;
}
MinionModel* Graphics_impl::CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax, float tmax, const char* diffuseTexture)
{
	Model *m = new Plane(xsize, zsize, xdivs, zdivs, smax, tmax);
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

Graphics_impl* Graphics_impl::GetInstancePointer()
{
	return minionGraphicsPtr;
}

void Graphics_impl::glError_callback(int error, const char* description)
{
	if (minionGraphicsPtr)
	{
		minionGraphicsPtr->errorstr = description;
	}
}