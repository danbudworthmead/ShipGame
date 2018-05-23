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

<<<<<<< HEAD
	pModel->SetPosition(viewportWidth / 2, viewportHeight / 2);
=======
	pModel->SetPosition(
		(windowWidth / 2)  - (pModel->GetSize().X / 2), 
		(windowHeight / 2) - (pModel->GetSize().Y / 2)
	);
>>>>>>> 261b22ded578216dadc6649d65d5fa8f8fd2e96c

	do
	{
		pModel->Update();
		window.Update();
	} while (!window.ShouldClose());

	window.Destroy();

	return 1;
}