#include "include/MinionGraphics.h"

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
		this->gfx = nullptr;
		
	}
	virtual~Application()
	{
		this->Destroy();
	}
	bool Init()
	{		
		Minion::MinionGraphics::GetGraphicsHandle(&gfx);
		gfx->SetEnableLogging(true);
		if (gfx && !gfx->InitializeRenderWindow(&this->window))
		{
			printf(gfx->GetLastError().c_str());
			return false;
		}
		
		//CreateModels();

		return true;
	}
	void RunApplication()
	{
		gfx->SetClearColor(0.0f, 1.0f, 1.0f);

		window->Run([this](Minion::MinionWindow*)->Minion::MinionWindow::CallbackReturnCode
		{
			gfx->UpdateGraphics(0.1f);

			for (Minion::MinionModel* model : this->models)
			{
				gfx->QueueForRendering(model);
			}
			gfx->RenderGraphics();

			static float r = 0.0f;
			static float delta = -0.01f;
			gfx->SetClearColor(0, r, 0);
			r += delta;
			if (r > 1.0f)	delta = delta*-1;
			else if (r < 0.0f) delta = delta*-1;

			return Minion::MinionWindow::CallbackReturnCode_Continue; 
		});

		
	}
	void Destroy()
	{
		Minion::MinionGraphics::ReleaseGraphicsHandle(&gfx);
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

	app.Destroy();

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