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

	float Delta() const;
	Uint64 FrameTicks() const;


	bool DidKeyUp(Uint8 key) const;
	bool DidKeyDown(Uint8 key) const;

	bool IsKeyUp(Uint8 key) const;
	bool IsKeyDown(Uint8 key) const;
private:

	void RunPostKeyUpdate();

	MonoTimer m_tFrameTimer;

	Uint64 m_uDeltaTicks;
	float m_fDeltaTime;

	Uint8 m_uaPreviousKeyState[SDL_NUM_SCANCODES];
	Uint8 m_uaCurrentKeyState[SDL_NUM_SCANCODES];
};