#include "Window_impl.h"

#include "../Utilities/logger.h"

#include <algorithm>

const std::string loggerName = "MinionWindow";

//------------------- From MinionWindow --------------------------
MinionWindow::~MinionWindow(){}
//------------------- MinionWindow End ---------------------------


Window_impl::Window_impl(GLFWwindow* window)
{
	if (!window) return;

	this->window = window;
	//this->data = 0;
	//this->self = this;
	glfwSetWindowUserPointer(window, this);
	//windowCollection.push_back(this);
}
Window_impl::~Window_impl()
{
	glfwSetWindowCloseCallback(this->window, nullptr);
	glfwSetWindowFocusCallback(this->window, nullptr);
	glfwSetWindowIconifyCallback(this->window, nullptr);
	glfwSetWindowPosCallback(this->window, nullptr);
	glfwSetWindowRefreshCallback(this->window, nullptr);
	glfwSetWindowSizeCallback(this->window, nullptr);

	glfwDestroyWindow(this->window);
}
MinionWindow::WindowReturnCode Window_impl::Run(std::function<MinionWindow::CallbackReturnCode(MinionWindow*)> fnc)
{
	if (!fnc)
		Logger::Debug(loggerName, "Must specify a callback function when creating a window");

	bool runing = true;
	MinionWindow::WindowReturnCode returnResult = MinionWindow::WindowReturnCode_Success;

	do
	{
		try
		{
			glfwPollEvents();

			if (glfwWindowShouldClose(window))
			{
				runing = false;
			}
			else
			{
				MinionWindow::CallbackReturnCode res = fnc(this);
				if (res == Minion::MinionWindow::CallbackReturnCode_Close)
						runing = false;
			}
		}
		catch (std::exception& e)
		{
			Logger::Debug(loggerName, "LINE %i - Exception message:%s", __LINE__, e.what());
			returnResult = WindowReturnCode_Failed;
		}
	} while (runing);

	return returnResult;
}
void Window_impl::SetOnClose(OnClose fnc)		  
{
	this->onClose = fnc;

	if (!fnc)
	{
		glfwSetWindowCloseCallback(window, nullptr);
	}
	else
	{
		glfwSetWindowCloseCallback(window, [](GLFWwindow* win)
		{
			Window_impl *gw = (Window_impl*)glfwGetWindowUserPointer(win);
			gw->onClose(gw);
		});
	}
}
void Window_impl::SetOnFocus(OnFocus fnc)
{
	this->onFocus = fnc;
	if (!fnc)
	{
		glfwSetWindowFocusCallback(window, nullptr);
	}
	else
	{
		glfwSetWindowFocusCallback(window, [](GLFWwindow* win, int f)
		{
			Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(win);
			tmp->onFocus(tmp, f);
		});
	}
}
void Window_impl::SetOnIconify(OnIconify fnc)
{
	this->onIconify = fnc;
	if (!fnc)
	{
		glfwSetWindowIconifyCallback(window, nullptr);
		return;
	}
	
	glfwSetWindowIconifyCallback(window, [](GLFWwindow* win, int a)
	{
		Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(win);
		tmp->onIconify(tmp, a);
	});
}
void Window_impl::SetOnPosition(OnPosition fnc)
{
	this->onPosition = fnc;
	if (!fnc)
	{
		glfwSetWindowPosCallback(window, nullptr);
		return;
	}
	
	glfwSetWindowPosCallback(window, [](GLFWwindow* win, int x, int y)
	{
		Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(win);
		tmp->onPosition(tmp, x, y);
	});
}
void Window_impl::SetOnRefresh(OnRefresh fnc)
{
	this->onRefresh = fnc;
	if (!fnc)
	{
		glfwSetWindowRefreshCallback(window, nullptr);
		return;
	}
	
	glfwSetWindowRefreshCallback(window, [](GLFWwindow* win)
	{
		Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(win);
		tmp->onRefresh(tmp);
	});
}
void Window_impl::SetOnSize(OnSize fnc)
{
	this->onSize = fnc;
	if (!fnc)
	{
		glfwSetWindowSizeCallback(window, nullptr);
		return;
	}
	
	glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height)
	{
		Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(win);
		tmp->onSize(tmp, width, height);
	});
}

void Window_impl::SetWindowTitle(const char* title)
{
	if (this->window)
	{
		glfwSetWindowTitle(this->window, title);
	}
}
void Window_impl::SetWindowSize(unsigned int width, unsigned int height)
{
	if (this->window)
	{
		glfwSetWindowSize(this->window, width, height);
	}
}
void Window_impl::SetWindowPosition(int x, int y)
{
	if (this->window)
	{
		glfwSetWindowPos(this->window, x, y);
	}
}
void Window_impl::SetWindowPosition(WindowPosition pos)
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
void Window_impl::SetAsMainWindow()
{
	glfwMakeContextCurrent(this->window);
}

unsigned int Window_impl::GetWidth() const
{
	int w,h;
	glfwGetWindowSize(this->window, &w, &h);
	return w;
}
unsigned int Window_impl::GetHeight() const									 
{
	int w, h;
	glfwGetWindowSize(this->window, &w, &h);
	return h;
}
void Window_impl::GetSize(unsigned int& width, unsigned int& height) const	 
{
	int w, h;
	glfwGetWindowSize(this->window, &w, &h);
	width = (unsigned int)w;
	height = (unsigned int)h;
}
int Window_impl::GetPosX() const												 
{
	int x, y;
	glfwGetWindowPos(this->window, &x, &y);
	return x;
}
int Window_impl::GetPosY() const												 
{
	int x, y;
	glfwGetWindowPos(this->window, &x, &y);
	return y;
}
void Window_impl::GetPosition(int& x, int& y) const							 
{
	glfwGetWindowPos(this->window, &x, &y);
}