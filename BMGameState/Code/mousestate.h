#pragma once
#include <SDL.h>

#define SDL_NUM_MOUSEBUTTONS 5

bool IsValidMouseButton(const Uint8 button);

class MouseState
{
public:
	MouseState();
	~MouseState();

	void ProcessSDLEvent(const SDL_Event *sdl_event);
	void RunPostUpdate();

	bool DidMouseUp(const Uint8 button) const;
	bool DidMouseDown(const Uint8 button) const;

	bool IsMouseUp(const Uint8 button) const;
	bool IsMouseDown(const Uint8 button) const;
private:
	Uint8 *m_uCurrentButtons;
	Uint8 *m_uPreviousButtons;
};