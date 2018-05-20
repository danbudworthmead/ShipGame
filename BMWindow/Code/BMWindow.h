#ifndef __BMWINDOW_H_
#define __BMWINDOW_H_

#include <vector>

struct SDL_Window;
struct SDL_Renderer;
class BMSprite;

class BMWindow
{
public:
	BMWindow();
	~BMWindow();

	bool Init();
	bool Update();
	bool Destroy();

	bool ShouldClose();

	void OverrideWindowSize(const int a_iWidth, const int a_iHeight);
	void OverrideWindowTitle(const char* a_szTitle);

	void AddSpriteToRenderQueue(BMSprite* m_pSprite);

	BMSprite* CreateSprite(const char* m_pName);

private:
	void HandleEvents();
	void UnloadAllLoadedSprites();
	void RenderSprites();

	bool m_bShouldClose;
	SDL_Window* m_pWindow;

	int m_iWindowWidth, m_iWindowHeight;
	const char* m_szWindowTitle;

	SDL_Renderer* m_pRenderer;

	// Textures which will be rendered
	std::vector<BMSprite*> m_pRenderQueue;

	// Currently loaded sprites
	std::vector<BMSprite*> m_pLoadedSprites;

	// File buffer
	char m_pFileBuffer[128];
};

#endif //__BMWINDOW_H_