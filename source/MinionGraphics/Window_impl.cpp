#include "Window_impl.h"

#include <algorithm>


//------------------- From MinionWindow --------------------------
MinionWindow::~MinionWindow(){}
//------------------- MinionWindow End ---------------------------


Window_impl::Window_impl(GLFWwindow* window)
{
	if (!window) return;
	
	this->window = window;
	glfwSetWindowUserPointer(window, this);
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
void Window_impl::Run(std::function<MinionWindow::CallbackReturnCode(MinionWindow*)> fnc)
{
	if (!fnc)
		throw exception::MinionWindowException("Must specify a callback function when creating a window", WindowErrorCode_Failed_NoCallback);

	bool runing = true;

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
				if (res == minion::MinionWindow::CallbackReturnCode_Close)
						runing = false;
			}
		}
		catch (std::exception& e)
		{
			throw exception::MinionWindowException(std::string("LINE " + std::to_string(__LINE__) + " - Exception message: " + e.what()).c_str(), WindowErrorCode_UNKNOWN);
		}
	} while (runing);

}
void Window_impl::Close()
{
	glfwSetWindowShouldClose(this->window, 1);
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
	case minion::MinionWindow::WindowPosition_TopLeft:
		break;
	case minion::MinionWindow::WindowPosition_TopRight:
		break;
	case minion::MinionWindow::WindowPosition_Center:
		break;
	case minion::MinionWindow::WindowPosition_BottomLeft:
		break;
	case minion::MinionWindow::WindowPosition_BottomRight:
		break;
	case minion::MinionWindow::WindowPosition_Left:
		break;
	case minion::MinionWindow::WindowPosition_Right:
		break;
	case minion::MinionWindow::WindowPosition_Top:
		break;
	case minion::MinionWindow::WindowPosition_Bottom:
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
void Window_impl::SetOnKeyboardEvent(OnKey fnc)
{
	this->onKey = fnc;
	if (!fnc)
	{
		glfwSetKeyCallback(window, nullptr);
		return;
	}

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window_impl *tmp = (Window_impl*)glfwGetWindowUserPointer(window);
		tmp->onKey(tmp, key, scancode, action, mods);
	});
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