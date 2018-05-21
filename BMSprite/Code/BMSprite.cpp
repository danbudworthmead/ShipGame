#include "BMSprite.h"
#include <SDL_rect.h>

BMSprite::BMSprite(SDL_Texture* pTexture, const SDL_Rect& rRect, const unsigned int hash)
	: m_pTexture(pTexture)
	, m_uRotation(0)
	, m_uHash(hash)
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

unsigned int BMSprite::GetRotation()
{
	return m_uRotation;
}

void BMSprite::SetRotation(unsigned int rot)
{
	m_uRotation = rot;
}

unsigned int BMSprite::GetHash() const
{
	return m_uHash;
}