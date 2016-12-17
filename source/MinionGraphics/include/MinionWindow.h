#ifndef MINION_WINDOW_H
#define MINION_WINDOW_H

#include <functional>
#include <memory>

namespace Minion
{
	/*
	*	MinionWindow is a window wrapper (that uses GLFW) used to create a window and manage event related to the created window.
	*	Create a window by calling CreateWindow method
	*/
	class MinionWindow
	{
	public:
		enum WindowPosition
		{
			WindowPosition_TopLeft,
			WindowPosition_TopRight,
			WindowPosition_Center,
			WindowPosition_BottomLeft,
			WindowPosition_BottomRight,
			WindowPosition_Left,
			WindowPosition_Right,
			WindowPosition_Top,
			WindowPosition_Bottom,
		};
		enum WindowReturnCode
		{
			WindowReturnCode_Success,
			WindowReturnCode_Failed,
		};
		enum CallbackReturnCode
		{
			CallbackReturnCode_Close,
			CallbackReturnCode_Continue,
		};

	protected:
		virtual~MinionWindow();

	public:
		typedef std::function<void(MinionWindow* sender)> OnClose;
		typedef std::function<void(MinionWindow* sender, int focus)> OnFocus;
		typedef std::function<void(MinionWindow* sender, int iconify)> OnIconify;
		typedef std::function<void(MinionWindow* sender, int x, int y)> OnPosition;
		typedef std::function<void(MinionWindow* sender)> OnRefresh;
		typedef std::function<void(MinionWindow* sender, int width, int height)> OnSize;

	public:

		/*
		* Starts processing window events and calls callback each frame.
		* This function is blocking.
		* Return value of the callback will tell the window what to do next.
		*/
		virtual WindowReturnCode Run(std::function<CallbackReturnCode(MinionWindow*)>) = 0;

		virtual void SetOnClose(OnClose) = 0;
		virtual void SetOnFocus(OnFocus) = 0;
		virtual void SetOnIconify(OnIconify) = 0;
		virtual void SetOnPosition(OnPosition) = 0;
		virtual void SetOnRefresh(OnRefresh) = 0;
		virtual void SetOnSize(OnSize) = 0;

		virtual void SetWindowTitle(const char* title) = 0;
		virtual void SetWindowSize(unsigned int width, unsigned int height) = 0;
		virtual void SetWindowPosition(int x, int y) = 0;
		virtual void SetWindowPosition(WindowPosition) = 0;
		virtual void SetAsMainWindow() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void GetSize(unsigned int& width, unsigned int& height) const = 0;
		virtual int GetPosX() const = 0;
		virtual int GetPosY() const = 0;
		virtual void GetPosition(int& x, int& y) const = 0;
	};
}



#endif // !MINION_WINDOW
