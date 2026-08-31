#include "pch.h"
#include "ReadyScene.h"
#include "BmpManager.h"
#include "SoundManager.h"
#include "ReadyUI.h"
#include "UIManager.h"
#include "Mouse.h"
#include "ObjManager.h"
#include "AbstractFactory.h"
#include "CameraManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "TileManager.h"

CReadyScene::CReadyScene() : m_pMouse(nullptr)
{
}
CReadyScene::~CReadyScene()
{
	Release();
}
void CReadyScene::Initialize()
{
 
	CTileManager::Get_Instance()->Initialize();


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Ready.bmp", L"Ready");

	m_pUI = new CReadyUI;
	CUIManager::Get_Instance()->Add_UI(m_pUI);
	CUIManager::Get_Instance()->Initialize();

	m_pMouse = CAbstractFactory<CMouse>::Create();
	CObjManager::Get_Instance()->AddObject(OBJ_MOUSE, m_pMouse);
	m_bOnceBgm = 0;
	
	CCameraManager::Get_Instance()->Initialize();
	m_iChoice = 0;
}

void CReadyScene::Update(float deltatime)
{
	CUIManager::Get_Instance()->Update(deltatime);
	CObjManager::Get_Instance()->Update(deltatime);
	
	Check_Mouse();
	Mange_Bgm();
}

void CReadyScene::Late_Update(float deltatime)
{
	CUIManager::Get_Instance()->Late_Update(deltatime);
	CObjManager::Get_Instance()->Late_Update(deltatime);
}

void CReadyScene::Render(HDC hDC)
{
	HDC ReadyDC = CBmpMgr::Get_Instance()->Find_Image(L"Ready");
	GdiTransparentBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		ReadyDC,
		0,
		0,
		(int)1890,
		(int)1056,
		RGB(255, 255, 255));
	CUIManager::Get_Instance()->Render(hDC);
	CObjManager::Get_Instance()->Render(hDC);

}

void CReadyScene::Release()
{
	CUIManager::Get_Instance()->Release();
	CObjManager::Get_Instance()->Release();
	CKeyManager::Get_Instance()->Release();
	CTileManager::Get_Instance()->Release();
}

void CReadyScene::Mange_Bgm() {
	if (m_bOnceBgm == 0) {
		CSoundManager::Get_Instance()->PlayBGM(L"BGM_Menu_Main_A.wav", 0.5f);
		m_bOnceBgm++;
	}
}

void CReadyScene::Check_Mouse() {
	Vec2 MousePos = { m_pMouse->Get_Info()->fX , m_pMouse->Get_Info()->fY };

	if (MousePos.x >= WINCX / 2 - 100 && MousePos.x <= WINCX / 2 + 100 &&
		MousePos.y >= 270 - 30 && MousePos.y <= 270 + 80) {
		m_iChoice = 1;
		dynamic_cast<CReadyUI*>(m_pUI)->Choice_Menu(m_iChoice);
	}
	else if (MousePos.x >= WINCX / 2 - 100 && MousePos.x <= WINCX / 2 + 100 &&
		MousePos.y >= 370 - 30 && MousePos.y <= 370 + 80) {
		m_iChoice = 2;
		dynamic_cast<CReadyUI*>(m_pUI)->Choice_Menu(m_iChoice);
	}
	else {
		m_iChoice = 3;
		dynamic_cast<CReadyUI*>(m_pUI)->Choice_Menu(m_iChoice);
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON)) {
		switch (m_iChoice) {
		case 1:
			CSceneManager::Get_Instance()->Change_Scene(SCSTAGE2);
			//CSceneManager::Get_Instance()->Change_Scene(SCMAPEDIT);
			break;

		case 2:
			g_Off = true;
			
			break;

		default:

			break;
		}
	}

}

