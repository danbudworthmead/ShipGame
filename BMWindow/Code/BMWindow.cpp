#include "BMWindow.h"
#include <SDL.h>
#include <SDL_events.h>
#include <stdio.h>

BMWindow::BMWindow()
	: m_bShouldClose(false)
	, m_pWindow(nullptr)
	, m_iWindowHeight(480)
	, m_iWindowWidth(640)
	, m_szWindowTitle("BMWindow")
{
}

BMWindow::~BMWindow()
{
}

bool BMWindow::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	m_pWindow = SDL_CreateWindow (
		m_szWindowTitle, 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		m_iWindowWidth, 
		m_iWindowHeight, 
		SDL_WINDOW_OPENGL
	);

	if (m_pWindow == nullptr)
	{
		// Faliled to create window!
		return false;
	}

	// Everything was fine!
	return true;
}

bool BMWindow::Update()
{
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
		{
			m_bShouldClose = true;
		}
	}
	return true;
}

bool BMWindow::Destroy()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
	return true;
}

bool BMWindow::ShouldClose()
{
	return m_bShouldClose;
}

void BMWindow::OverrideWindowSize(const int a_iWidth, const int a_iHeight)
{
	if (m_pWindow)
	{
		SDL_Log("Cannot override window size as window has already been created.");
		return;
	}
	m_iWindowWidth = a_iWidth;
	m_iWindowHeight = a_iHeight;
}

void BMWindow::OverrideWindowTitle(const char* a_szTitle)
{
	if (m_pWindow)
	{
		SDL_Log("Cannot override window title as window has already been created.");
		return;
	}
	m_szWindowTitle = a_szTitle;
}
