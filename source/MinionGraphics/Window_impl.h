#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H


#include <vector>

#include "include/MinionWindow.h"

#include <utilities.h>
#include <GID.h>
#include <GLFW/glfw3.h>

using namespace minion;

class Window_impl :public MinionWindow
{
public:
	Window_impl(GLFWwindow*);
	virtual~Window_impl();

	operator GLFWwindow*() { return this->window; }
	void Run(std::function<CallbackReturnCode(MinionWindow*)>) override;
	void Close() override;

	void SetOnClose(OnClose) override;
	void SetOnFocus(OnFocus) override;
	void SetOnIconify(OnIconify) override;
	void SetOnPosition(OnPosition) override;
	void SetOnRefresh(OnRefresh) override;
	void SetOnSize(OnSize) override;
	void SetOnKeyboardEvent(OnKey) override;

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
	OnKey onKey;
};


#endif // !GRAPHICS_WINDOW
