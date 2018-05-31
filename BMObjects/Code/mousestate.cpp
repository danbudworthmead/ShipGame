#include "mousestate.h"
#include <memory.h>

bool IsValidMouseButton(const Uint8 button)
{
	return button >= 0 && button < SDL_NUM_MOUSEBUTTONS;
}

MouseState::MouseState()
{
	m_uCurrentButtons = new Uint8[SDL_NUM_MOUSEBUTTONS];
	m_uPreviousButtons = new Uint8[SDL_NUM_MOUSEBUTTONS];

	memset(m_uCurrentButtons, 0, sizeof(Uint8) * SDL_NUM_MOUSEBUTTONS);
	memset(m_uPreviousButtons, 0, sizeof(Uint8) * SDL_NUM_MOUSEBUTTONS);
}

MouseState::~MouseState()
{
	delete[] m_uCurrentButtons;
	delete[] m_uPreviousButtons;
}

void MouseState::ProcessSDLEvent(const SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		m_uCurrentButtons[event->button.button] = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		m_uCurrentButtons[event->button.button] = 0;
		break;
	case SDL_MOUSEMOTION:

		break;
	}
}

void MouseState::RunPostUpdate()
{
	memcpy(m_uPreviousButtons, m_uCurrentButtons, sizeof(Uint8) * SDL_NUM_MOUSEBUTTONS);
}

bool MouseState::DidMouseUp(const Uint8 button) const
{
	if (!IsValidMouseButton(button))
	{
		return false;
	}

	return m_uCurrentButtons[button] == 0 && m_uPreviousButtons[button] == 1;
}

bool MouseState::DidMouseDown(const Uint8 button) const
{
	if (!IsValidMouseButton(button))
	{
		return false;
	}

	return m_uCurrentButtons[button] == 1 && m_uPreviousButtons[button] == 0;
}

bool MouseState::IsMouseUp(const Uint8 button) const
{
	if (!IsValidMouseButton(button))
	{
		return false;
	}

	return m_uCurrentButtons[button] == 0;
}

bool MouseState::IsMouseDown(const Uint8 button) const
{
	if (!IsValidMouseButton(button))
	{
		return false;
	}

	return m_uCurrentButtons[button] == 1;
}