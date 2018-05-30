#include "BMModel.h"
#include <BMSprite.h>
#include <SDL_rect.h>

// TODO: Data define this in .bmm files
#define MODEL_SPRITE_OFFSET 4

BMModel::BMModel()
	: m_x(0)
	, m_y(0)
	, m_iLayerOffset(4)
	, m_vSize(0, 0)
	, m_uZLevel(0)
	, m_fRotation(0.0f)
{
}

BMModel::~BMModel()
{
}

void BMModel::Update(float deltaTime)
{
	double deltaInSeconds = deltaTime * 0.001;
	double moveAmount = 20 * deltaInSeconds;
	for (auto s : m_pSprites)
	{
		s->SetRotation(s->GetRotation() + moveAmount);
	}
}

void BMModel::SetPosition(const int x, const int y)
{
	m_x = x;
	m_y = y;

	for (unsigned int i = 0; i < m_pSprites.size(); ++i)
	{
		m_pSprites[i]->GetRect()->x = x;
		m_pSprites[i]->GetRect()->y = y - i * m_iLayerOffset;
	}
}

void BMModel::SetRotation(const float rot)
{
	m_fRotation = rot;
	for (auto sprite : m_pSprites)
	{
		sprite->SetRotation(rot);
	}
}

float BMModel::GetRotation() const
{
	return m_fRotation;
}

void BMModel::SetLayerOffset(const int offset)
{
	m_iLayerOffset = offset;
}

void BMModel::SetSize(const Vector2D& a_v2)
{
	m_vSize = a_v2;
}

Vector2D& BMModel::GetSize()
{
	return m_vSize;
}

void BMModel::AddSprite(BMSprite* pSprite)
{
	pSprite->GetRect()->y -= m_pSprites.size() * m_iLayerOffset;
	pSprite->SetZLevel(m_pSprites.size() + this->GetZLevel());
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

void BMModel::SetZLevel(const unsigned int z)
{
	m_uZLevel = z;

	for (unsigned int uSprite = 0; uSprite < this->GetNumSprites(); ++uSprite)
	{
		this->GetSprite(uSprite)->SetZLevel(m_uZLevel);
	}
}

unsigned int BMModel::GetZLevel() const
{
	return m_uZLevel;
}