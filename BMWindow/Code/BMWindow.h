#ifndef __BMWINDOW_H_
#define __BMWINDOW_H_

#include <vector>
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;
union SDL_Event;

class BMSprite;
class BMModel;

void SortSprites(std::vector<BMSprite*>& data);

class BMWindow
{
public:
	BMWindow();
	~BMWindow();

	bool Init();
	void ProcessSDLEvent(const SDL_Event *sdlEvent);
	bool Update(const float delta);
	bool Destroy();

	bool ShouldClose();

	void OverrideWindowSize(const int a_iWidth, const int a_iHeight);
	void OverrideWindowTitle(const char* a_szTitle);
	void OverrideWindowProjection(const int a_iWidth, const int a_iHeight);

	void AddSpriteToRenderQueue(BMSprite* m_pSprite);
	void AddModelToRenderQueue(BMModel* m_pModel);

	BMSprite* CreateSprite(const char* szName, const SDL_Rect& rRect);
	BMModel* CreateModel(const char* szName);

private:

	void UnloadAllLoadedSprites();
	void UnloadAllLoadedModels();
	void RenderSprites();

	bool m_bShouldClose;
	SDL_Window* m_pWindow;

	int m_iWindowWidth, m_iWindowHeight;
	int m_iProjectionWidth, m_iProjectionHeight;

	const char* m_szWindowTitle;

	SDL_Renderer* m_pRenderer;

	// Textures which will be rendered
	std::vector<BMSprite*> m_pRenderQueue;

	// Currently loaded sprites
	std::vector<BMSprite*> m_pLoadedSprites;

	// Currently loaded models
	std::vector<BMModel*> m_pLoadedModels;

	// File buffer
	char m_pFileBuffer[128];
};

#endif //__BMWINDOW_H_