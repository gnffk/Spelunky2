#include "pch.h"
#include "MainGame.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "ObjManager.h"
#include "CameraManager.h"
#include "TileManager.h"
#include "UIManager.h"
#include "SoundManager.h"


CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount()), m_deltatime(0)
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	hBackDC = CreateCompatibleDC(m_hDC);
	hBmpBack = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP prev = (HBITMAP)SelectObject(hBackDC, hBmpBack);
	DeleteObject(prev);


	CSceneManager::Get_Instance()->Initialize();
	CSoundManager::Get_Instance()->Initialize();
	//CSceneManager::Get_Instance()->Change_Scene(SCMAPEDIT);
	//CSceneManager::Get_Instance()->Change_Scene(SCMENU);

#ifdef _DEBU

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3]; 
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

}

void CMainGame::Update()
{
	
	CSceneManager::Get_Instance()->Update(m_deltatime);
	CKeyManager::Get_Instance()->Update(m_deltatime);
}

void CMainGame::Late_Update()
{
	CSceneManager::Get_Instance()->Late_Update(m_deltatime);
}

void CMainGame::Render()
{
	

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d || DeltaTime : %lf", m_iFPS, m_deltatime);
		m_iFPS = 0;

		SetWindowText(g_hWnd, m_szFPS);
		m_deltatime = (m_currtime - m_dwTime)/1000;
		m_dwTime = GetTickCount();
	}
	else {
		m_currtime = GetTickCount();
	}




	CSceneManager::Get_Instance()->Render(hBackDC);


	

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	PatBlt(hBackDC, 0, 0, WINCX, WINCY, WHITENESS);
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSceneManager::Destroy_Instance();
	CKeyManager::Destroy_Instacne();
	CObjManager::Destroy_Instacne();
	CBmpMgr::Destroy_Instacne();
	CCameraManager::Destroy_Instacne();
	CTileManager::Destroy_Instacne();
	CUIManager::Destroy_Instance();
	CSoundManager::Destroy_Instacne();
	ReleaseDC(g_hWnd, m_hDC);
}
