#pragma once

#include "define.h"

#include "SceneManager.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

private:
	HDC			m_hDC;
	HDC			hBackDC;
	HBITMAP		hBmpBack;
	TCHAR		m_szFPS[128];
	int			m_iFPS;
	DWORD		m_dwTime;
	float		m_deltatime;
	float		m_currtime;

};

