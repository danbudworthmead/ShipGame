#ifndef __BMWINDOW_H_
#define __BMWINDOW_H_

struct SDL_Window;

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

private:
	bool m_bShouldClose;
	SDL_Window* m_pWindow;

	int m_iWindowWidth, m_iWindowHeight;
	const char* m_szWindowTitle;
};

#endif //__BMWINDOW_H_