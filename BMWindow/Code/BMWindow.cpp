#include "BMWindow.h"
#include <SDL.h>
#include <SDL_events.h>
#include <stdio.h>
#include <BMSprite.h>

BMWindow::BMWindow()
	: m_bShouldClose(false)
	, m_pRenderer(nullptr)
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

	// Create window
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

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer == nullptr)
	{
		// Faliled to create renderer!
		return false;
	}

	SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF);

	// Everything was fine!
	return true;
}

bool BMWindow::Update()
{
	HandleEvents();

	SDL_RenderClear(m_pRenderer);

	RenderSprites();

	SDL_RenderPresent(m_pRenderer);

	return true;
}

void BMWindow::HandleEvents()
{
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
		{
			m_bShouldClose = true;
		}
	}
}

bool BMWindow::Destroy()
{
	UnloadAllLoadedSprites();

	if (m_pWindow)
	{
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}

	if (m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}

	SDL_Quit();
	return true;
}

void BMWindow::UnloadAllLoadedSprites()
{
	for (auto pSprite : m_pLoadedSprites)
	{
		SDL_DestroyTexture(pSprite->GetTexture());
	}
}

void BMWindow::RenderSprites()
{
	// Render everything on screen
	for (auto sprite : m_pRenderQueue)
	{
		SDL_RenderCopy(m_pRenderer, sprite->GetTexture(), NULL, NULL);
	}
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

void BMWindow::AddSpriteToRenderQueue(BMSprite* m_pSprite)
{
	if (m_pSprite && m_pSprite->GetTexture())
	{
		m_pRenderQueue.push_back(m_pSprite);
	}
}

BMSprite* BMWindow::CreateSprite(const char* m_pName)
{
	SDL_Texture* pTexture = nullptr;

	SDL_snprintf(m_pFileBuffer, sizeof(m_pFileBuffer), "resources/images/%s", m_pName);

	// Load the image
	SDL_Surface* pSurface = SDL_LoadBMP(m_pFileBuffer);
	if (pSurface == nullptr)
	{
		// Unable to load the image!
		printf("Unable to load image %s! SDL_Error Error: %s\n", m_pFileBuffer, SDL_GetError());
	}
	else
	{
		pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
		if (pTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error Error: %s\n", m_pFileBuffer, SDL_GetError());
		}

		SDL_FreeSurface(pSurface);
	}

	BMSprite* pSprite = new BMSprite(pTexture);
	m_pLoadedSprites.push_back(pSprite);

	return pSprite;
}