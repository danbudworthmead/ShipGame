#pragma once
#include <SDL.h>

bool IsValidKey(Uint8 key);

class KeyboardState
{
public:
	KeyboardState();
	~KeyboardState();

	void ProcessSDLEvent(const SDL_Event *event);

	void RunPostUpdate();

	bool DidKeyUp(const Uint8 key) const;
	bool DidKeyDown(const Uint8 key) const;

	bool IsKeyUp(const Uint8 key) const;
	bool IsKeyDown(const Uint8 key) const;
private:
	Uint8 *m_uCurrentKeyState; // dynamically allocated array of Uint8[SDL_NUM_SCANCODES] that holds the key state from the current
	Uint8 *m_uPreviousKeyState; // dynamically allocated array of Uint8[SDL_NUM_SCANCODES] that holds the key state from the previous frame
};