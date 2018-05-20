#ifndef __BMSPRITE_H_
#define __BMSPRITE_H_

struct SDL_Texture;

class BMSprite
{
public:
	BMSprite(SDL_Texture* pTexture) : m_pTexture(pTexture) {}
	~BMSprite() {}

	SDL_Texture* GetTexture() { return m_pTexture; }

private:
	SDL_Texture* m_pTexture;
};

#endif //__BMSPRITE_H_