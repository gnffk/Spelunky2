#include "pch.h"
#include "MenuScene.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

#include "SoundManager.h"
CMenuScene::CMenuScene() 
{
}

CMenuScene::~CMenuScene()
{
	Release();
}

void CMenuScene::Initialize()
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Menu1.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item.bmp", L"Item");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave.bmp", L"Cave_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave2.bmp", L"Cave_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave3.bmp", L"Cave_3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave4.bmp", L"Cave_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/TileTop.bmp", L"TileTop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/map_Layer1.bmp", L"Cave_Layer1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/map_Layer.bmp", L"Cave_Layer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bomb.bmp", L"Bomb");
	m_bOnceBgm = 0;

}

void CMenuScene::Update(float deltatime)
{
	Key_Set();
	Mange_Bgm();
}

void CMenuScene::Late_Update(float deltatime)
{
	
}

void CMenuScene::Render(HDC hDC)
{

	HDC MenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
	GdiTransparentBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		MenuDC,
		0,
		0,
		(int)1890,
		(int)1056,
		RGB(255, 255, 255));
}

void CMenuScene::Release()
{
	
}

void CMenuScene::Key_Set() {
	if (CKeyManager::Get_Instance()->Key_Down(VK_RETURN)) {
		CSceneManager::Get_Instance()->Change_Scene(SCMAPEDIT);
		//CSceneManager::Get_Instance()->Change_Scene(SCMAPEDIT);

	}
	 
}

void CMenuScene::Mange_Bgm() {
	if (m_bOnceBgm == 0) {
		CSoundManager::Get_Instance()->PlaySound(L"BGM_Title_Intro.wav", SOUND_BGM, 0.5f);
		m_bOnceBgm++;
	}
	
}
