#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "autolink_windows.h"

#include <GL/glfw3.h>
#include <vector>

#include "include/MinionWindow.h"
#include <NoEdgeUtilities.h>
#include <GID.h>

using namespace Minion;

class Window_impl :public MinionWindow
{
public:
	Window_impl(GLFWwindow*);
	virtual~Window_impl();

	operator GLFWwindow*() { return this->window; }
	WindowReturnCode Run(std::function<CallbackReturnCode(MinionWindow*)>) override;

	void SetOnClose(OnClose) override;
	void SetOnFocus(OnFocus) override;
	void SetOnIconify(OnIconify) override;
	void SetOnPosition(OnPosition) override;
	void SetOnRefresh(OnRefresh) override;
	void SetOnSize(OnSize) override;

	void SetWindowTitle(const char* title) override;
	void SetWindowSize(unsigned int width, unsigned int height) override;
	void SetWindowPosition(int x, int y) override;
	void SetWindowPosition(WindowPosition);
	void SetAsMainWindow() override;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	void GetSize(unsigned int& width, unsigned int& height) const;
	int GetPosX() const;
	int GetPosY() const;
	void GetPosition(int& x, int& y) const;

private:
	GLFWwindow* window;

	OnClose onClose;
	OnFocus onFocus;
	OnIconify onIconify;
	OnPosition onPosition;
	OnRefresh onRefresh;
	OnSize onSize;
};


#endif // !GRAPHICS_WINDOW
