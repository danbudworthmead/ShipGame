#ifndef __BMMODEL_H_
#define __BMMODEL_H_

#include <vector>

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

private:
	std::vector<BMSprite*> m_pSprites;

	int m_x, m_y, m_layer_offset;
};

#endif //__BMSPRITE_H_