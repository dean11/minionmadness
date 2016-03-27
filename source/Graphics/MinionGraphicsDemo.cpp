#include "include/MinionGraphics.h"
#include "include\MinionWindow.h"

#define PYTHON_OUTPUT

#include <cstdio>
#include <Windows.h>
#include <vector>
#include <glfw3.h>
#include <NoEdgeUtilities.h>

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
		this->window = Minion::MinionWindow::CreateMinionWindow(640, 420, 50, 50, "MininonMADAFACKA!", true);
		if (!this->window) return false;
		window->SetOnClose(OnCloseWin);
		
		gfx = Minion::MinionGraphics::GetGraphicsHandle();
		gfx->SetEnableLogging(true);
		if (gfx && !gfx->InitiateGraphics(this->window))
		{
			printf(gfx->GetLastError().c_str());
			return false;
		}
		

		CreateModels();

		return true;
	}
	void RunApplication()
	{
		bool quit = false;
		gfx->SetClearColor(0.0f, 1.0f, 1.0f);
		float r = 0.0f;
		float delta = -0.001;
		//Run program
		while (!quit)
		{
			quit = window->ProcessEvents() == 0;

			gfx->UpdateGraphics(0.1f);
			
			for (size_t i = 0; i < this->models.size(); i++)
			{
				gfx->QueueForRendering(this->models[i]);
			}
			gfx->RenderGraphics();

			gfx->SetClearColor(r, 0,0);
			r += delta;
			if (r > 1.0f)	delta = delta*-1;
			else if (r < 0.0f) delta = delta*-1;
		}
	}
	
	
private:
	bool CreateModels()
	{
		//Minion::MinionModel* plane = gfx->CreateModel_Plane(100, 100, 10, 10);
		//if (!plane)	return false;
		//models.push_back(plane);

		Minion::MinionModel* triangle = gfx->CreateModel_Triangle(1, 1);
		if (!triangle)	return false;
		models.push_back(triangle);

		return true;
	}

private:
	Minion::MinionWindow* window;
	Minion::MinionGraphics* gfx;
	std::vector<Minion::MinionModel*> models;
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Application app;
	if (app.Init())
	{
		app.RunApplication();
	}

	
	return 0;
}
