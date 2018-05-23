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

	void Update();

	void SetPosition(const int x, const int y);
	void SetLayerOffset(const int offset);

	void SetSize(const Vector2D& a_v2);
	Vector2D& const GetSize();

private:
	std::vector<BMSprite*> m_pSprites;

	int m_x, m_y, m_iLayerOffset;
	Vector2D m_vSize;
};

#endif //__BMSPRITE_H_