#include "include/MinionGraphics.h"
#include "include/MinionWindow.h"

#define PYTHON_OUTPUT

#if defined _WIN32 || defined WIN32
#include <Windows.h>
#endif

#include <cstdio>
#include <vector>

class Application
{
public:
	Application()
	{
		this->gfx = 0;
		this->window = 0;
		
	}
	virtual~Application()
	{
		if (gfx)	gfx->Release();
		gfx = 0;
		window->Release();	
	}
	static void OnCloseWin(Minion::MinionWindow* win, void* data)
	{
		if (data)
			data = 0;
	}
	bool Init()
	{
		this->window = Minion::MinionWindow::CreateMinionWindow(640, 420, "MininonMADAFACKA!", true);

		if (!this->window) return false;
		window->SetOnClose(OnCloseWin);
		
		gfx = Minion::MinionGraphics::GetGraphicsHandle();
		gfx->SetEnableLogging(true);
		if (gfx && !gfx->InitiateGraphics(this->window))
		{
			printf(gfx->GetLastError().c_str());
			return false;
		}
		

		//CreateModels();

		return true;
	}
	void RunApplication()
	{
		bool quit = false;
		gfx->SetClearColor(0.0f, 1.0f, 1.0f);
		float r = 0.0f;
		float delta = -0.01f;
		//Run program
		while (!quit)
		{
			quit = window->ProcessEvents() == 0;

			gfx->UpdateGraphics(0.1f);
			
			for (Minion::MinionModel* model : this->models)
			{
				gfx->QueueForRendering(model);
			}
			gfx->RenderGraphics();
			
			gfx->SetClearColor(0, r, 0);
			r += delta;
			if (r > 1.0f)	delta = delta*-1;
			else if (r < 0.0f) delta = delta*-1;
		}
	}
	
	
private:
	bool CreateModels()
	{
		Minion::MinionModel* triangle = gfx->CreateModel_Triangle(1, 1);
		
		if (!triangle)	
			return false;
		models.push_back(triangle);

		return true;
	}

private:
	Minion::MinionWindow* window;
	Minion::MinionGraphics* gfx;
	std::vector<Minion::MinionModel*> models;
};


#if defined _WIN32 || defined WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Application app;
	if (app.Init())
	{
		app.RunApplication();
	}

	return 0;
}
#else
int main(int argc, char** argv)
{
	Application app;
	if (app.Init())
	{
		app.RunApplication();
	}
}
#endif