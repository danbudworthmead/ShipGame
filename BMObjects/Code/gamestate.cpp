#include "gamestate.h"
#include <memory.h>
#include <iostream>



GameState::GameState() : m_fDeltaTime(0), m_uDeltaTicks(0)
{

}

GameState::~GameState()
{

}

void GameState::ProcessSDLEvent(const SDL_Event *sdlEvent)
{
	m_sKeyState.ProcessSDLEvent(sdlEvent);
	m_sMouseState.ProcessSDLEvent(sdlEvent);
}

void GameState::RunUpdate()
{
	m_uDeltaTicks = m_tFrameTimer.GetTicks();
	m_tFrameTimer.Start();

	m_fDeltaTime = ((m_uDeltaTicks) * 1000 / (float)SDL_GetPerformanceFrequency());
}

void GameState::RunPostUpdate()
{
	m_sKeyState.RunPostUpdate();
	m_sMouseState.RunPostUpdate();
}

float GameState::Delta() const
{
	return m_fDeltaTime;
}

Uint64 GameState::FrameTicks() const
{
	return ((m_uDeltaTicks) * 1000 / SDL_GetPerformanceFrequency());
}

const KeyboardState& GameState::GetKeys() const
{
	return m_sKeyState;
}

const MouseState& GameState::GetMouse() const
{
	return m_sMouseState;
}