#pragma once

#include <SDL.h>

class MonoTimer
{
public:
	MonoTimer();
	~MonoTimer();

	void Start();
	void Stop();

	void Pause();
	void Unpause();

	Uint64 GetTicks();
		
	bool IsStarted();
	bool IsPaused();
private:
	Uint64 m_iStartTicks, m_iPausedTicks;
	bool m_bStarted, m_bPaused;
};