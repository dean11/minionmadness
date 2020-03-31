#include "include/MinionGraphics.h"

#if defined _WIN32 || defined WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <cstdio>
#include <vector>
#include <iostream>
#include <chrono>
#include <Timer.h>
#include <logger.h>

class Application
{
public:
	Application()
		:logger("GraphicsDemo","./demo.log" )
	{
		this->gfx = nullptr;
		
	}
	virtual~Application()
	{
		this->Destroy();
	}
	bool Init()
	{		
		try
		{
			minion::MinionGraphics::GetGraphicsHandle(&this->gfx);
			gfx->InitializeGraphics(&this->window, 640, 420, "Minion Graphics Development");

			if (!gfx || !window)
			{
				return false;
			}

			this->camera = minion::MinionCamera::CreateCamera(45.0f, (float)this->window->GetWidth() / this->window->GetHeight(), 0.1f, 100.0f, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f });
			this->gfx->System_SetDefaultCamera(this->camera);
			this->window->SetOnKeyboardEvent([this](minion::MinionWindow* sender, int key, int scancode, int action, int mods)
			{
				if (key == 81)
					sender->Close();
				else if (key == 83)
					camera->SetPosition({ 0.0f, 0.0f, 2.0f });
				else if (key == 68)
					camera->SetPosition({ 0.0f, 0.0f, -2.0f });
			});
			
			camera->SetPosition({ 0.0f, 0.0f, 0.0f });
			CreateModels();
		}
		catch (minion::MinionGraphicsException& e)
		{
			logger.Debug(e.what());
			return false;
		}
		return true;
	}
	void RunApplication()
	{
		utilities::Time::Timer clock;
		
		const int kMaxDeltatime = ((int)((1.0f / 60.0f) * 1000.0f));

		auto lastEndTime = clock.ElapsedMilliseconds();
		window->Run([this, &clock, &lastEndTime, &kMaxDeltatime](minion::MinionWindow*)->minion::MinionWindow::CallbackReturnCode
		{
			// How long did the last update take?
			auto frameTime = clock.ElapsedMilliseconds() - lastEndTime;
			// Mark the last update time
			lastEndTime = clock.ElapsedMilliseconds();
			
			while (frameTime > 0)
			{
				auto deltaTime = std::min(frameTime, kMaxDeltatime);
				gfx->UpdateGraphics(deltaTime);
				
				frameTime -= deltaTime;
			}

			for (minion::MinionModel* model : this->models)
			{
				gfx->QueueForRendering(model);
			}

			gfx->RenderGraphics();

			

			return minion::MinionWindow::CallbackReturnCode_Continue;
		});

		
	}
	void Destroy()
	{
		gfx->ReleaseGraphicsHandle(&gfx);
	}
	
private:
	bool CreateModels()
	{
		minion::MinionModel* triangle = gfx->CreateModel_Triangle({ -0.1f, 0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f });
		triangle->SetPosition(0.0f, 0.0f, 2.0f);
		if (!triangle)	
			return false;
		models.push_back(triangle);

		return true;
	}

private:
	utilities::Logger logger;
	minion::MinionWindow* window;
	minion::MinionGraphics* gfx;
	std::shared_ptr<minion::MinionCamera> camera;
	std::vector<minion::MinionModel*> models;
};


#if defined _WIN32 || defined WIN32
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
	int main(int argc, char** argv)
#endif
{
	
	Application app;
	try
	{
		if (app.Init())
		{
			app.RunApplication();
		}
	}
	catch (minion::MinionGraphicsException& e)
	{
		std::cout << e << std::endl;
	}
	app.Destroy();

	return 0;
}
