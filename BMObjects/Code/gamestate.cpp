#include "gamestate.h"
#include <memory.h>
#include <iostream>

bool IsValidKey(Uint8 key)
{
	return key >= 0 && key < SDL_NUM_SCANCODES;
}

GameState::GameState() : m_fDeltaTime(0), m_uDeltaTicks(0)
{
	memset(m_uaPreviousKeyState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memset(m_uaCurrentKeyState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
}

GameState::~GameState()
{

}

void GameState::ProcessSDLEvent(const SDL_Event *sdlEvent)
{
	switch (sdlEvent->type)
	{
	case SDL_KEYDOWN:
		m_uaCurrentKeyState[sdlEvent->key.keysym.scancode] = 1;
		break;
	case SDL_KEYUP:
		m_uaCurrentKeyState[sdlEvent->key.keysym.scancode] = 0;
		break;
	}
}

void GameState::RunUpdate()
{
	m_uDeltaTicks = m_tFrameTimer.GetTicks();
	m_tFrameTimer.Start();

	m_fDeltaTime = ((m_uDeltaTicks) * 1000 / (float)SDL_GetPerformanceFrequency());
}

void GameState::RunPostUpdate()
{
	RunPostKeyUpdate();
}

float GameState::Delta() const
{
	return m_fDeltaTime;
}

Uint64 GameState::FrameTicks() const
{
	return ((m_uDeltaTicks) * 1000 / SDL_GetPerformanceFrequency());
}

bool GameState::DidKeyUp(Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}
	return m_uaCurrentKeyState[key] == 0 && m_uaPreviousKeyState[key] == 1;
}

bool GameState::DidKeyDown(Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}

	return m_uaCurrentKeyState[key] == 1 && m_uaPreviousKeyState[key] == 0;
}

bool GameState::IsKeyUp(Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}
	return m_uaCurrentKeyState[key] == 0;
}

bool GameState::IsKeyDown(Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}

	return m_uaCurrentKeyState[key] == 1;
}


void GameState::RunPostKeyUpdate()
{
	memcpy(m_uaPreviousKeyState, m_uaCurrentKeyState, sizeof(Uint8) * sizeof(m_uaCurrentKeyState));
	// memset(m_uaCurrentKeyState, 0, sizeof(Uint8) * sizeof(m_uaCurrentKeyState));
}