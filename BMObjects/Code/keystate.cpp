#include "keystate.h"
#include <memory.h>

bool IsValidKey(Uint8 key)
{
	return key >= 0 && key < SDL_NUM_SCANCODES;
}

KeyboardState::KeyboardState()
{
	m_uCurrentKeyState = new Uint8[SDL_NUM_SCANCODES];
	m_uPreviousKeyState = new Uint8[SDL_NUM_SCANCODES];

	memset(m_uCurrentKeyState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memset(m_uPreviousKeyState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
}

KeyboardState::~KeyboardState()
{
	delete[] m_uCurrentKeyState;
	delete[] m_uPreviousKeyState;
}

void KeyboardState::ProcessSDLEvent(const SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		m_uCurrentKeyState[event->key.keysym.scancode] = 1;
		break;
	case SDL_KEYUP:
		m_uCurrentKeyState[event->key.keysym.scancode] = 0;
		break;
	}
}

void KeyboardState::RunPostUpdate()
{
	memcpy(m_uPreviousKeyState, m_uCurrentKeyState, sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool KeyboardState::DidKeyUp(const Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}
	return m_uCurrentKeyState[key] == 0 && m_uPreviousKeyState[key] == 1;
}

bool KeyboardState::DidKeyDown(const Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}

	return m_uCurrentKeyState[key] == 1 && m_uPreviousKeyState[key] == 0;
}

bool KeyboardState::IsKeyUp(const Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}
	return m_uCurrentKeyState[key] == 0;
}

bool KeyboardState::IsKeyDown(const Uint8 key) const
{
	if (!IsValidKey(key))
	{
		return false;
	}

	return m_uCurrentKeyState[key] == 1;
}
