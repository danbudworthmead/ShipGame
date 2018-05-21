#ifndef __BMSPRITE_H_
#define __BMSPRITE_H_

struct SDL_Texture;
struct SDL_Rect;

class BMSprite
{
public:
	BMSprite(SDL_Texture* pTexture, const SDL_Rect& rRect, const unsigned int hash);
	~BMSprite();

	SDL_Texture*	GetTexture();
	SDL_Rect*		GetRect();

	unsigned int GetRotation();
	void SetRotation(unsigned int rot);

	unsigned int GetHash() const;

private:
	SDL_Texture* m_pTexture;
	SDL_Rect* m_pRect;

	unsigned int m_uRotation;
	unsigned int m_uHash;
};

#endif //__BMSPRITE_H_