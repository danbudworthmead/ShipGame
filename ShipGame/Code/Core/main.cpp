#include <BMWindow.h>
#include <BMModel.h>
#include <stdio.h>
#include <SDL_rect.h>

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
	}

	BMModel* pModel = window.CreateModel("boat_simple");
	window.AddModelToRenderQueue(pModel);

	pModel->SetPosition(viewportWidth / 2, viewportHeight / 2);

	do
	{
		pModel->Update();
		window.Update();
	} while (!window.ShouldClose());

	window.Destroy();

	return 1;
}