#pragma once
#include <SDL.h>
#include <BMTimer.h>

bool IsValidKey(Uint8 key);

class GameState
{
public:
	GameState();
	~GameState();

	void ProcessSDLEvent(const SDL_Event *sdl_event);

	void RunUpdate();
	void RunPostUpdate();

	float Delta();
	Uint64 FrameTicks();


	bool DidKeyUp(Uint8 key);
	bool DidKeyDown(Uint8 key);

	bool IsKeyUp(Uint8 key);
	bool IsKeyDown(Uint8 key);
private:

	void RunPostKeyUpdate();

	MonoTimer m_tFrameTimer;

	Uint64 m_uDeltaTicks;
	float m_fDeltaTime;

	Uint8 m_uaPreviousKeyState[SDL_NUM_SCANCODES];
	Uint8 m_uaCurrentKeyState[SDL_NUM_SCANCODES];
};