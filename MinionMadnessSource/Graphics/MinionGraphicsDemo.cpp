#include "include/MinionGraphics.h"

#include <cstdio>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	MinionGraphicsInitDesc data;
	data.windowX = 50;
	data.windowY = 50;

	MinionGraphics* gfx = MinionGraphics::GetGraphicsPointer();
	
	if (!gfx)									std::printf("%s", "Failed to create MinionGraphics instance");
	else if (!gfx->InitiateMinionGraphics(data))		std::printf("%s", gfx->GetLastError());

	MinionModel *plane = gfx->CreateModel_Plane(100, 100, 10, 10);

	bool quit = false;
	
	//Run program
	while (!quit)
	{
		gfx->BeginScene();
			plane->Render();
		gfx->EndScene();
	}


	gfx->Release();
	return 0;
}
