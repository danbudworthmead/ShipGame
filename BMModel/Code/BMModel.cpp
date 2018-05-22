#include "BMModel.h"
#include <BMSprite.h>
#include <SDL_rect.h>

// TODO: Data define this in .bmm files
#define MODEL_SPRITE_OFFSET 4

BMModel::BMModel()
	: m_x(0)
	, m_y(0)
	, m_layer_offset(4)
{
}

BMModel::~BMModel()
{
}

void BMModel::Update()
{
	for (auto s : m_pSprites)
	{
		s->SetRotation(s->GetRotation() + 1);
	}
}

void BMModel::SetPosition(const int x, const int y)
{
	m_x = x;
	m_y = y;

	for (unsigned int i = 0; i < m_pSprites.size(); ++i)
	{
		m_pSprites[i]->GetRect()->x = x;
		m_pSprites[i]->GetRect()->y = y - i * m_layer_offset;
	}
}

void BMModel::SetLayerOffset(const int offset)
{
	m_layer_offset = offset;
}

void BMModel::AddSprite(BMSprite* pSprite)
{
	pSprite->GetRect()->y -= m_pSprites.size() * m_layer_offset;
	m_pSprites.push_back(pSprite);
}

BMSprite * BMModel::GetSprite(unsigned int index)
{
	return m_pSprites.at(index);
}

unsigned int BMModel::GetNumSprites() const
{
	return m_pSprites.size();
}