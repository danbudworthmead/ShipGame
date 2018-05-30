#ifndef __BMMODEL_H_
#define __BMMODEL_H_

#include <vector>
#include <vec2D.h>

class BMSprite;

class BMModel
{
public:
	BMModel();
	~BMModel();

	void AddSprite(BMSprite* pSprite);

	BMSprite* GetSprite(unsigned int index);
	unsigned int GetNumSprites() const;

	void Update(float deltaTime);

	void SetPosition(const int x, const int y);
	void SetRotation(const float rotation);

	float GetRotation() const;

	void SetLayerOffset(const int offset);

	void SetSize(const Vector2D& a_v2);
	Vector2D& GetSize();

	void SetZLevel(const unsigned int z);
	unsigned int GetZLevel() const;

private:
	std::vector<BMSprite*> m_pSprites;
	float m_fRotation;

	int m_x, m_y, m_iLayerOffset;
	unsigned int m_uZLevel;
	Vector2D m_vSize;
};

#endif //__BMSPRITE_H_