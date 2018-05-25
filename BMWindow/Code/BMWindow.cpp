#include "BMWindow.h"
#include <SDL.h>
#include <SDL_events.h>
#include <stdio.h>
#include <BMSprite.h>
#include <BMModel.h>
#include <SDL_image.h>
#include <tinyxml2.h>

#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>


void SortSprites(std::vector<BMSprite*>& data)
{
	unsigned int count;
	unsigned int countMinusOne;

	BMSprite* key = NULL;

	std::size_t size = data.size();

	for (count = 1; count < size; count++)
	{
		key = data[count];
		countMinusOne = count - 1;

		while (countMinusOne >= 0 && data[countMinusOne]->GetZLevel() > key->GetZLevel())
		{
			data[countMinusOne + 1] = data[countMinusOne];
			countMinusOne -= 1;
		}

		data[countMinusOne + 1] = key;
	}
}

BMWindow::BMWindow()
	: m_bShouldClose(false)
	, m_pRenderer(nullptr)
	, m_pWindow(nullptr)
	, m_iWindowHeight(480)
	, m_iWindowWidth(640)
	, m_iProjectionHeight(480)
	, m_iProjectionWidth(640)
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

	// init IMG
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF);

	// Everything was fine!
	return true;
}

bool BMWindow::Update(double delta)
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
	UnloadAllLoadedModels();
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

void BMWindow::UnloadAllLoadedModels()
{
	for (auto pModel : m_pLoadedModels)
	{
		delete pModel;
		pModel = nullptr;
	}
}

void BMWindow::RenderSprites()
{
	// Render everything on screen
	for (auto sprite : m_pRenderQueue)
	{
		float viewportWidthRatio = (float)m_iWindowWidth / (float)m_iProjectionWidth;
		float viewportHeightRatio = (float)m_iWindowHeight / (float)m_iProjectionHeight;

		SDL_Rect destinationRect;
		SDL_Rect *sourceRect = sprite->GetRect();
		SDL_Texture *sourceTexture = sprite->GetTexture();

		destinationRect.x = sourceRect->x * viewportWidthRatio;
		destinationRect.y = sourceRect->y * viewportHeightRatio;
		destinationRect.w = sourceRect->w * viewportWidthRatio;
		destinationRect.h = sourceRect->h * viewportHeightRatio;

		SDL_RenderCopyEx(m_pRenderer, sprite->GetTexture(), NULL, &destinationRect, sprite->GetRotation(), NULL, SDL_RendererFlip::SDL_FLIP_NONE);
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

void BMWindow::OverrideWindowProjection(const int a_iWidth, const int a_iHeight)
{
	m_iProjectionWidth = a_iWidth;
	m_iProjectionHeight = a_iHeight;
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

	SortSprites(m_pRenderQueue);
}

void BMWindow::AddModelToRenderQueue(BMModel* m_pModel)
{
	for (unsigned int uSprite = 0; uSprite < m_pModel->GetNumSprites(); ++uSprite)
	{
		AddSpriteToRenderQueue(m_pModel->GetSprite(uSprite));
	}
}

unsigned int Hash(const char* szName)
{
	unsigned int ret = 0;
	for (unsigned int i = 0; i < strlen(szName); ++i)
	{
		ret += szName[i];
	}
	return ret;
}

BMSprite* BMWindow::CreateSprite(const char* szName, const SDL_Rect& rRect)
{
	BMSprite* pSprite = nullptr;
	const unsigned int uHash = Hash(szName);

	// Check if the sprite we want already exists
	for (auto s : m_pLoadedSprites)
	{
		if (s->GetHash() == uHash)
		{
			pSprite = new BMSprite(s->GetTexture(), rRect, uHash);
		}
	}

	// Do we still need to create the sprite?
	if (pSprite == nullptr)
	{
		SDL_Texture* pTexture = nullptr;

		SDL_snprintf(m_pFileBuffer, sizeof(m_pFileBuffer), "resources/images/%s.png", szName);

		// Load the image
		SDL_Surface* pSurface = IMG_Load(m_pFileBuffer);
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

		pSprite = new BMSprite(pTexture, rRect, uHash);
	}
	
	m_pLoadedSprites.push_back(pSprite);
	return pSprite;
}

BMModel* BMWindow::CreateModel(const char* pName)
{
	using namespace tinyxml2;
	XMLDocument xmlDoc;

	SDL_snprintf(m_pFileBuffer, sizeof(m_pFileBuffer), "resources/models/%s.bmm", pName);
	if (XMLError xmlError = xmlDoc.LoadFile(m_pFileBuffer))
	{
		printf("Unable to load model %s! TinyXMLError: %s\n", m_pFileBuffer, XMLDocument::ErrorIDToName(xmlError));
		return nullptr;
	}

	BMModel* pModel = new BMModel();

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 10;

	int layerOffset = 0;

	XMLElement *layerElem = xmlDoc.FirstChildElement("LayerOffset");

	if (layerElem == nullptr)
	{
		printf("LayerOffset tag for resources/models/%s.bmm undefined\n", pName);
	}
	else 
	{
		if (XMLError xmlError = layerElem->QueryIntText(&layerOffset))
		{
			printf("Invalid LayerOffset for resources/models/%s.bmm\n", pName);
		}
		else
		{
			pModel->SetLayerOffset(layerOffset);
		}
	}

	XMLElement *widthElem = xmlDoc.FirstChildElement("Width");

	if (widthElem == nullptr)
	{
		printf("No width specified for resources/models/%s.bmm\n", pName);
		return nullptr;
	}

	if (XMLError xmlError = widthElem->QueryIntText(&rect.w))
	{
		printf("Invalid width specified for resources/models/%s.bmm\n", pName);
		return nullptr;
	}

	XMLElement *heightElem = xmlDoc.FirstChildElement("Height");

	if (heightElem == nullptr)
	{
		printf("No height specified for resources/models/%s.bmm\n", pName);
		return nullptr;
	}

	if (XMLError xmlError = heightElem->QueryIntText(&rect.h))
	{
		printf("Invalid height specified for resources/models/%s.bmm\n", pName);
		return nullptr;
	}

	pModel->SetSize(Vector2D(rect.w, rect.h));

	XMLElement *spritesElem = xmlDoc.FirstChildElement("Sprites");

	if (spritesElem == nullptr)
	{
		printf("Sprites tag for resources/models/%s.bmm undefined- cannot continue loading model\n", pName);
		return nullptr;
	}

	for (XMLElement *pElement = spritesElem->FirstChildElement(); pElement != spritesElem->LastChildElement(); ++pElement)
	{
		pModel->AddSprite(CreateSprite(pElement->GetText(), rect));
	}

	m_pLoadedModels.push_back(pModel);

	return pModel;
}
