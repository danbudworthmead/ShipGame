#pragma once
#include <SDL.h>
#include <BMTimer.h>
#include "keystate.h"
#include "mousestate.h"

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

	const KeyboardState& GetKeys() const ;
	const MouseState& GetMouse() const;

private:
	KeyboardState m_sKeyState;
	MouseState m_sMouseState;

	MonoTimer m_tFrameTimer;

	Uint64 m_uDeltaTicks;
	float m_fDeltaTime;
};