#ifndef MINION_WINDOW_H
#define MINION_WINDOW_H


namespace Minion
{
	/*
	*	MinionWindow is a window wrapper used to create a window and manage event related to the created window.
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
	public:
		static MinionWindow* CreateMinionWindow(unsigned int width, unsigned int height, const char* title, bool mainWindow);

	public:
		typedef void(*OnClose)(MinionWindow*, void* data);
		typedef void(*OnFocus)(MinionWindow*, bool focus, void* data);
		typedef void(*OnIconify)(MinionWindow*, bool iconify, void* data);
		typedef void(*OnPosition)(MinionWindow*, int x, int y, void* data);
		typedef void(*OnRefresh)(MinionWindow*, void* data);
		typedef void(*OnSize)(MinionWindow*, int w, int h, void* data);

	public:
		virtual void Release() = 0;

		virtual int ProcessEvents() = 0;

		virtual void SetCallbackData(void*) = 0;
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
