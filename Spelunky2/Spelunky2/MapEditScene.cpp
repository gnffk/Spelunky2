#include "pch.h"
#include "MapEditScene.h"
#include "BmpManager.h"
#include "CameraManager.h"
#include "ObjManager.h"
#include "TileManager.h"
#include "AbstractFactory.h"
#include "KeyManager.h"
#include "Player.h"
#include "Mouse.h"
#include "DebugPlayer.h"
#include "SceneManager.h"

CMapEditScene::CMapEditScene() : m_pPlayer(nullptr), m_pMouse(nullptr), m_CursorPos{0,0}, 
m_hTextureUI(NULL), m_TileSize{0.f, 0.f}, m_fMapType(NONE)
{

}

CMapEditScene::~CMapEditScene()
{
	Release();
}

void CMapEditScene::Initialize()
{
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave.bmp", L"Cave_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave2.bmp", L"Cave_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/bg_cave3.bmp", L"Cave_3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/border_main.bmp", L"Border");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/TileTop.bmp", L"TileTop");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/map_Layer.bmp", L"Cave_Layer");
	CCameraManager::Get_Instance()->Initialize();
	m_pPlayer = CAbstractFactory<CDebugPlayer>::Create();
	//m_pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjManager::Get_Instance()->AddObject(OBJ_PLAYER, m_pPlayer);
	CCameraManager::Get_Instance()->SetTarget(m_pPlayer);

	m_pMouse = CAbstractFactory<CMouse>::Create();
	CObjManager::Get_Instance()->AddObject(OBJ_MOUSE, m_pMouse);

	//CTileManager::Get_Instance()->Load_Tile(L"../Data/BossStage.dat");
	//CTileManager::Get_Instance()->Load_Tile(L"../Data/Tile.dat");
	CTileManager::Get_Instance()->Initialize();


	g_viewCollisionBox = TRUE;


}

void CMapEditScene::Update(float deltatime)
{
	KeyDown();

	CObjManager::Get_Instance()->Update(deltatime);
	CCameraManager::Get_Instance()->Update(deltatime);
	CTileManager::Get_Instance()->Update(deltatime);


}

void CMapEditScene::Late_Update(float deltatime)
{
	CObjManager::Get_Instance()->Late_Update(deltatime);

}

void CMapEditScene::Render(HDC hDC)
{


	Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();
	HDC LAYERUI = CBmpMgr::Get_Instance()->Find_Image(L"Cave_Layer");
	GdiTransparentBlt(hDC,
		-cameraPos.x ,
		-cameraPos.y ,
		MAPCX,
		MAPCY,
		LAYERUI,
		0,
		0,
		(int)MAPCX,
		(int)MAPCY,
		RGB(255, 255, 255));



	CTileManager::Get_Instance()->Render(hDC);



	GdiTransparentBlt(hDC,
		(int)(WINCX * 0.5 - m_TileSize.x / 6),
		(int)(WINCY * 0.5 - m_TileSize.y / 6),
		m_TileSize.x / 3,
		m_TileSize.y / 3,
		m_hTextureUI,
		0,
		0,
		(int)m_TileSize.x,
		(int)m_TileSize.y,
		RGB(255, 255, 255));
	CObjManager::Get_Instance()->Render(hDC);
}

void CMapEditScene::Release()
{
	m_pPlayer = nullptr;
	CObjManager::Get_Instance()->Release();
	CTileManager::Get_Instance()->Release();

}

void CMapEditScene::KeyDown()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_RETURN)) {
		CSceneManager::Get_Instance()->Change_Scene(SCSTAGE2);
	}


	if (CKeyManager::Get_Instance()->Key_Down('9')) {
		g_viewCollisionBox = !g_viewCollisionBox;
	}



	if (CKeyManager::Get_Instance()->Key_Down('1')) {
		m_hTextureUI = CBmpMgr::Get_Instance()->Find_Image(L"TileTop");
		m_TileSize.x = 1536;
		m_TileSize.y = 1536;
		m_fMapType = MAP1;
	}

	if (CKeyManager::Get_Instance()->Key_Down('2')) {
		m_hTextureUI = CBmpMgr::Get_Instance()->Find_Image(L"Cave_3");
		m_TileSize.x = 1280;
		m_TileSize.y = 1280;
		m_fMapType = MAP2;
	}

	if (CKeyManager::Get_Instance()->Key_Down('3')) {
		m_hTextureUI = CBmpMgr::Get_Instance()->Find_Image(L"Border");
		m_TileSize.x = 1280;
		m_TileSize.y = 1280;
		m_fMapType = MAP3;
	}




	if (CKeyManager::Get_Instance()->Key_Down('4')) {
		m_hTextureUI = NULL;
		m_fMapType = NONE;
	}

	if (CKeyManager::Get_Instance()->Key_Down('5')) {
		m_hTextureUI = NULL;
		m_fMapType = ERASE;
	}

	if (CKeyManager::Get_Instance()->Key_Down('o') || CKeyManager::Get_Instance()->Key_Down('O')) {
		CTileManager::Get_Instance()->Save_Tile();
	}
	if (CKeyManager::Get_Instance()->Key_Down('p') || CKeyManager::Get_Instance()->Key_Down('P')) {
		CTileManager::Get_Instance()->Load_Tile();
	}
	
	switch (m_fMapType) {
	case NONE:
		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
			CTileManager::Get_Instance()->Pick_Tile({ m_pMouse->Get_Info()->fX,m_pMouse->Get_Info()->fY });
			
		}
		break;

	case MAP1:
		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
			Vec2 WinMouse = dynamic_cast<CMouse*>(m_pMouse)->GetWinPos();
			int index_x = int((WinMouse.x- 384.f) / 42.7f);
			int index_y = int((WinMouse.y-104.f) / 42.7f);
			CTileManager::Get_Instance()->Choice_Tile(index_x, index_y, 1);
	
		}
		break;

	case MAP2:
		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
			Vec2 WinMouse = dynamic_cast<CMouse*>(m_pMouse)->GetWinPos();
			int index_x = int((WinMouse.x - 427.f) / 42.7f);
			int index_y = int((WinMouse.y - 147.f) / 42.7f);
			CTileManager::Get_Instance()->Choice_Tile(index_x, index_y, 2);
		}
		break;

	case MAP3:
		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
			Vec2 WinMouse = dynamic_cast<CMouse*>(m_pMouse)->GetWinPos();
			int index_x = int((WinMouse.x - 427) / 42.7f);
			int index_y = int((WinMouse.y - 147.f) / 42.7f);
			CTileManager::Get_Instance()->Choice_Tile(index_x, index_y, 3);
		}
		break;

	case ERASE:
		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON)) {
			CTileManager::Get_Instance()->Choice_Tile(1, 1, 0);
			CTileManager::Get_Instance()->Pick_Tile({ m_pMouse->Get_Info()->fX,m_pMouse->Get_Info()->fY });
		}
		break;

	default:

		break;
	}


}
