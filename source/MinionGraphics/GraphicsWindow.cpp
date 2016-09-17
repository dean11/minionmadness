#include "GraphicsWindow.h"

#include "../Utilities/logger.h"

#include <algorithm>

const std::string loggerName = "MinionWindow";

//------------------- From MinionWindow --------------------------
MinionWindow* MinionWindow::CreateMinionWindow(unsigned int width, unsigned int height, const char* title, bool mainWindow)
{
	//Use gflw to create window
	/* Initialize the library */
	if (glfwInit() == GLFW_FALSE)
		return nullptr;

	
	/* Creates a windowed mode window and its OpenGL context */
	GLFWwindow *windowPtr = glfwCreateWindow(width, height, title, NULL, NULL);
	
	if (!windowPtr)
	{
		glfwTerminate();
		return nullptr;
	}

	/* Make the window's context current */
	if (mainWindow)
		glfwMakeContextCurrent(windowPtr);

	GraphicsWindow* win = new GraphicsWindow(windowPtr);

	return win;
}


//------------------- MinionWindow End ---------------------------

//###################### Event Callbacks #############################
std::vector<GraphicsWindow*> GraphicsWindow::windowCollection = std::vector<GraphicsWindow*>();

void GraphicsWindow::_OnClose(GLFWwindow* win)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onClose) 
			w->onClose(w, w->data);
	}
}
void GraphicsWindow::_OnFocus(GLFWwindow*, int f)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onFocus)
			w->onFocus(w, f==1, w->data);
	}
}
void GraphicsWindow::_OnIconify(GLFWwindow*, int a)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onIconify)
			w->onIconify(w, a==1, w->data);
	}
}
void GraphicsWindow::_OnPos(GLFWwindow*, int x, int y)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onPosition)
			w->onPosition(w, x, y, w->data);
	}
}
void GraphicsWindow::_OnRefresh(GLFWwindow*)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onRefresh)
			w->onRefresh(w, w->data);
	}
}
void GraphicsWindow::_OnSize(GLFWwindow*, int width, int height)
{
	for (GraphicsWindow* w : windowCollection)
	{
		if (w->onSize)
			w->onSize(w, width, height, w->data);
	}
}
//#####################################################################


GraphicsWindow::GraphicsWindow(GLFWwindow* window)
{
	if (!window) return;

	this->window = window;
	this->data = 0;
	this->onClose = 0;
	this->onFocus = 0;
	this->onIconify = 0;
	this->onPosition = 0;
	this->onRefresh = 0;
	this->onSize = 0;
	this->self = this;
	windowCollection.push_back(this);
}
GraphicsWindow::~GraphicsWindow()
{
	//Remove from global list
	auto o = std::find(windowCollection.begin(), windowCollection.end(), this);
	if (o != windowCollection.end())
		windowCollection.erase(o);

	glfwSetWindowCloseCallback(this->window, nullptr);
	glfwSetWindowFocusCallback(this->window, nullptr);
	glfwSetWindowIconifyCallback(this->window, nullptr);
	glfwSetWindowPosCallback(this->window, nullptr);
	glfwSetWindowRefreshCallback(this->window, nullptr);
	glfwSetWindowSizeCallback(this->window, nullptr);

	glfwDestroyWindow(this->window);
	
	if (windowCollection.size() == 0)
	{
		glfwTerminate();
	}
}
void GraphicsWindow::Release()
{
	// Remove yourselfe from yourself! x)
	if (this) delete this->self;
}
int GraphicsWindow::ProcessEvents()
{
	try
	{
		glfwPollEvents();
	}
	catch (std::exception& e)
	{
		Logger::Debug(loggerName, "LINE %i - Exception message:%s", __LINE__, e.what());
	}
	
	if (glfwWindowShouldClose(window))
	{
		return 0;
	}
	return 1;
}
void GraphicsWindow::SetCallbackData(void* data)
{
	this->data = data;
}
void GraphicsWindow::SetOnClose(OnClose fnc)		  
{
	if (!fnc)
	{
		this->onClose = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onClose = fnc;
	glfwSetWindowCloseCallback(window, _OnClose);
}
void GraphicsWindow::SetOnFocus(OnFocus fnc)
{
	if (!fnc)
	{
		this->onFocus = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onFocus = fnc;
	glfwSetWindowFocusCallback(window, _OnFocus);
}
void GraphicsWindow::SetOnIconify(OnIconify fnc)
{
	if (!fnc)
	{
		this->onIconify = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onIconify = fnc;
	glfwSetWindowIconifyCallback(window, _OnIconify);
}
void GraphicsWindow::SetOnPosition(OnPosition fnc)
{
	if (!fnc)
	{
		this->onPosition = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onPosition = fnc;
	glfwSetWindowPosCallback(window, _OnPos);
}
void GraphicsWindow::SetOnRefresh(OnRefresh fnc)
{
	if (!fnc)
	{
		this->onRefresh = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onRefresh = fnc;
	glfwSetWindowRefreshCallback(window, _OnRefresh);
}
void GraphicsWindow::SetOnSize(OnSize fnc)
{
	if (!fnc)
	{
		this->onSize = nullptr;
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	this->onSize = fnc;

	glfwSetWindowSizeCallback(window, _OnSize);
}

void GraphicsWindow::SetWindowTitle(const char* title)
{
	if (this->window)
	{
		glfwSetWindowTitle(this->window, title);
	}
}
void GraphicsWindow::SetWindowSize(unsigned int width, unsigned int height)
{
	if (this->window)
	{
		glfwSetWindowSize(this->window, width, height);
	}
}
void GraphicsWindow::SetWindowPosition(int x, int y)
{
	if (this->window)
	{
		glfwSetWindowPos(this->window, x, y);
	}
}
void GraphicsWindow::SetWindowPosition(WindowPosition pos)
{
	int x = 0;
	int y = 0;
	switch (pos)
	{
	case Minion::MinionWindow::WindowPosition_TopLeft:
		break;
	case Minion::MinionWindow::WindowPosition_TopRight:
		break;
	case Minion::MinionWindow::WindowPosition_Center:
		break;
	case Minion::MinionWindow::WindowPosition_BottomLeft:
		break;
	case Minion::MinionWindow::WindowPosition_BottomRight:
		break;
	case Minion::MinionWindow::WindowPosition_Left:
		break;
	case Minion::MinionWindow::WindowPosition_Right:
		break;
	case Minion::MinionWindow::WindowPosition_Top:
		break;
	case Minion::MinionWindow::WindowPosition_Bottom:
		break;
	default:
		break;
	}

	if (this->window)
	{
		glfwSetWindowPos(this->window, x, y);
	}
}
void GraphicsWindow::SetAsMainWindow()
{
	glfwMakeContextCurrent(this->window);
}

unsigned int GraphicsWindow::GetWidth() const
{
	int w,h;
	glfwGetWindowSize(this->window, &w, &h);
	return w;
}
unsigned int GraphicsWindow::GetHeight() const									 
{
	int w, h;
	glfwGetWindowSize(this->window, &w, &h);
	return h;
}
void GraphicsWindow::GetSize(unsigned int& width, unsigned int& height) const	 
{
	int w, h;
	glfwGetWindowSize(this->window, &w, &h);
	width = (unsigned int)w;
	height = (unsigned int)h;
}
int GraphicsWindow::GetPosX() const												 
{
	int x, y;
	glfwGetWindowPos(this->window, &x, &y);
	return x;
}
int GraphicsWindow::GetPosY() const												 
{
	int x, y;
	glfwGetWindowPos(this->window, &x, &y);
	return y;
}
void GraphicsWindow::GetPosition(int& x, int& y) const							 
{
	glfwGetWindowPos(this->window, &x, &y);
}