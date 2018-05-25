#include "BMSprite.h"
#include <SDL_rect.h>

BMSprite::BMSprite(SDL_Texture* pTexture, const SDL_Rect& rRect, const unsigned int hash)
	: m_pTexture(pTexture)
	, m_dRotation(0)
	, m_uHash(hash)
	, m_uZLevel(0)
{
	m_pRect = new SDL_Rect(rRect);
}

BMSprite::~BMSprite()
{
	delete m_pRect;
	m_pRect = nullptr;
}

SDL_Texture* BMSprite::GetTexture()
{
	return m_pTexture;
}

SDL_Rect* BMSprite::GetRect()
{
	return m_pRect;
}

double BMSprite::GetRotation()
{
	return m_dRotation;
}

void BMSprite::SetRotation(double rot)
{
	m_dRotation = rot;
}

unsigned int BMSprite::GetHash() const
{
	return m_uHash;
}

void BMSprite::SetZLevel(const unsigned int z)
{
	m_uZLevel = z;
}

unsigned int BMSprite::GetZLevel() const
{
	return m_uZLevel;
}