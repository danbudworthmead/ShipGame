#include <BMWindow.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	BMWindow window;
	window.OverrideWindowSize(1280, 720);
	window.OverrideWindowTitle("Ship Game");

	if (!window.Init())
	{
		printf("Unable to create the window!");
	}

	do
	{
		window.Update();
	} while (!window.ShouldClose());

	window.Destroy();

	return 1;
}