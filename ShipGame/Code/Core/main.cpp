#include <BMWindow.h>
#include <BMModel.h>
#include <BMTimer.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_rect.h>

const int FPS_CAP = 60;
const int TICKS_PER_FRAME = 1000 / FPS_CAP;

int main(int argc, char* argv[])
{
	const int windowWidth = 1280, windowHeight = 720;
	const int viewportWidth = 640, viewportHeight = 480;

	BMWindow window;
	window.OverrideWindowSize(windowWidth, windowHeight);
	window.OverrideWindowTitle("Ship Game");
	window.OverrideWindowProjection(viewportWidth, viewportHeight);

	if (!window.Init())
	{
		printf("Unable to create the window!");
		return 1;
	}

	BMModel* pModel = window.CreateModel("boat_simple");
	BMModel* sModel = window.CreateModel("boat_simple");

	pModel->SetZLevel(1);
	sModel->SetZLevel(2);

	window.AddModelToRenderQueue(pModel);
	window.AddModelToRenderQueue(sModel);

	pModel->SetPosition(
		(viewportWidth / 2)  - (pModel->GetSize().X / 2), 
		(viewportHeight / 2) - (pModel->GetSize().Y / 2)
	);

	sModel->SetPosition((viewportWidth / 2), (viewportHeight / 2));

	MonoTimer frameTimer;
	frameTimer.Start();

	do
	{
		Uint64 deltaTicks = frameTimer.GetTicks();
		frameTimer.Start();

		double delta = ((deltaTicks) * 1000 / (double)SDL_GetPerformanceFrequency());

		pModel->Update(delta);
		sModel->Update(delta);
		window.Update(delta);

		Uint64 frameTicks = ((deltaTicks) * 1000 / SDL_GetPerformanceFrequency());

		if (frameTicks < TICKS_PER_FRAME)
		{
			SDL_Delay((Uint32)(TICKS_PER_FRAME - frameTicks));
		}
	} while (!window.ShouldClose());

	window.Destroy();

	return 1;
}