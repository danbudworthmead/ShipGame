#include "BMTimer.h"


MonoTimer::MonoTimer() : m_iStartTicks(0), m_iPausedTicks(0), m_bStarted(false), m_bPaused(false)
{

}

MonoTimer::~MonoTimer()
{

}

void MonoTimer::Start()
{
	m_bStarted = true;
	m_bPaused = false;

	m_iStartTicks = SDL_GetPerformanceCounter();
	m_iPausedTicks = 0;
}

void MonoTimer::Stop()
{
	m_bStarted = false;
	m_bPaused = false;

	m_iStartTicks = 0;
	m_iPausedTicks = 0;
}

void MonoTimer::Pause()
{
	if (m_bStarted && !m_bPaused) 
	{
		m_bPaused = true;
		m_iPausedTicks = SDL_GetPerformanceCounter() - m_iStartTicks;
		m_iStartTicks = 0;
	}
}

void MonoTimer::Unpause()
{
	if (m_bStarted && m_bPaused)
	{
		m_bPaused = false;
		m_iStartTicks = SDL_GetPerformanceCounter() - m_iPausedTicks;
		m_iPausedTicks = 0;
	}
}

Uint64 MonoTimer::GetTicks()
{
	Uint64 time = 0;

	if (m_bStarted)
	{
		if (m_bPaused)
		{
			time = m_iPausedTicks;
		}
		else
		{
			time = SDL_GetPerformanceCounter() - m_iStartTicks;
		}
	}

	return time;
}

bool MonoTimer::IsStarted()
{
	return m_bStarted;
}

bool MonoTimer::IsPaused()
{
	return m_bPaused && m_bStarted;
}
