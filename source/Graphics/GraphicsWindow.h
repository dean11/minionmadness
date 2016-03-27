#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <glfw3.h>
#include <vector>

#include "include/MinionWindow.h"
#include <GID.h>

using namespace Minion;

class GraphicsWindow	:public MinionWindow
{
public:
	GraphicsWindow(GLFWwindow*);
	virtual~GraphicsWindow();

	operator GLFWwindow*() { return this->window; }
	void Release() override;
	int ProcessEvents() override;

	void SetCallbackData(void*) override;
	void SetOnClose(OnClose) override;
	void SetOnFocus(OnFocus) override;
	void SetOnIconify(OnIconify) override;
	void SetOnPosition(OnPosition) override;
	void SetOnRefresh(OnRefresh) override;
	void SetOnSize(OnSize) override;

	void SetWindowTitle(const char* title) override;
	void SetWindowSize(unsigned int width, unsigned int height) override;
	void SetWindowPosition(int x, int y) override;
	void SetAsMainWindow() override;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	void GetSize(unsigned int& width, unsigned int& height) const;
	int GetPosX() const;
	int GetPosY() const;
	void GetPosition(int& x, int& y) const;

private:
	static void _OnClose(GLFWwindow* win);
	static void _OnFocus(GLFWwindow*, int);
	static void _OnIconify(GLFWwindow*, int);
	static void _OnPos(GLFWwindow*, int x, int y);
	static void _OnRefresh(GLFWwindow*);
	static void _OnSize(GLFWwindow*, int, int);
	static std::vector<GraphicsWindow*> windowCollection;

private:
	GLFWwindow* window;
	void* data;

	OnClose onClose;
	OnFocus onFocus;
	OnIconify onIconify;
	OnPosition onPosition;
	OnRefresh onRefresh;
	OnSize onSize;

	GraphicsWindow* self = 0;
};


#endif // !GRAPHICS_WINDOW
