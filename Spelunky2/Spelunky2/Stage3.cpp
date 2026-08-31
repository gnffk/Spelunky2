#include "pch.h"
#include "Stage3.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "TileManager.h"
#include "CameraManager.h"
#include "Mouse.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "KeyManager.h"
#include "PlayerUI.h"
#include "DeadUI.h"
#include "Boss.h"
#include "SoundManager.h"
#include "EffectManager.h"

CStage3::CStage3() : m_pPlayer(nullptr), m_pBoss(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{

	CTileManager::Get_Instance()->Load_Tile(L"../Data/Stage3.dat");
	//m_pPlayer = CAbstractFactory<CDebugPlayer>::Create();
	//m_pPlayer = CAbstractFactory<CPlayer>::Create();
	//m_pPlayer->Initialize();
	//CObjManager::Get_Instance()->AddObject(OBJ_PLAYER, m_pPlayer);

	m_pPlayer = CObjManager::Get_Instance()->Get_TypeObj(OBJ_PLAYER).front();
	m_pPlayer->Set_Remain(false);
	m_pPlayer->Set_Pos(300.f, 150.f);
	if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hand()) {
		dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hand()->Set_Remain(false);
	}
	

	CCameraManager::Get_Instance()->Initialize();
	CCameraManager::Get_Instance()->SetTarget(m_pPlayer);

	CObjManager::Get_Instance()->AddObject(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());
	m_pBoss = CAbstractFactory<CBoss>::Create();
	CObjManager::Get_Instance()->AddObject(OBJ_BOSS, m_pBoss);
	dynamic_cast<CBoss*>(m_pBoss)->SetTarget(m_pPlayer);

	baseUI = CUIManager::Get_Instance()->Get_UI().front();
	dynamic_cast<CPlayerUI*>(baseUI)->Set_Targert(m_pPlayer);
	dynamic_cast<CPlayerUI*>(baseUI)->Set_Scene(this);
	baseUI->Set_Remain(false);

	DeadUI = new CDeadUI;
	dynamic_cast<CDeadUI*>(DeadUI)->Set_Targert(m_pPlayer);
	dynamic_cast<CDeadUI*>(DeadUI)->Set_Scene(this);
	CUIManager::Get_Instance()->Add_UI(DeadUI);

	CUIManager::Get_Instance()->Initialize();

	CTileManager::Get_Instance()->Check_Tile();

	
	m_StartTime = 0;
	m_CurrTime = 0;
	m_bOnceBgm = 0;
}

void CStage3::Update(float deltatime)
{
	m_CurrTime += deltatime;
	CCameraManager::Get_Instance()->Update(deltatime);

	CObjManager::Get_Instance()->Update(deltatime);

	CTileManager::Get_Instance()->Update(deltatime);
	CEffectManager::Get_Instance()->Update(deltatime);

	CUIManager::Get_Instance()->Update(deltatime);
	Mange_Bgm();
}

void CStage3::Late_Update(float deltatime)
{
	CObjManager::Get_Instance()->Late_Update(deltatime);
	CUIManager::Get_Instance()->Late_Update(deltatime);

	CCollisionManager::Collision_RectEx_Player(m_pPlayer, CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Boss(m_pBoss, CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Item(CObjManager::Get_Instance()->Get_TypeObj(OBJ_ITEM), CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Player_Boss(m_pPlayer, m_pBoss);

}

void CStage3::Render(HDC hDC)
{
	Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();
	HDC LAYERUI = CBmpMgr::Get_Instance()->Find_Image(L"Cave_Layer");
	GdiTransparentBlt(hDC,
		-cameraPos.x,
		-cameraPos.y,
		MAPCX,
		MAPCY,
		LAYERUI,
		0,
		0,
		(int)MAPCX,
		(int)MAPCY,
		RGB(255, 255, 255));


	CObjManager::Get_Instance()->Render(hDC);

	CTileManager::Get_Instance()->Render(hDC);
	CEffectManager::Get_Instance()->Render(hDC);

	CUIManager::Get_Instance()->Render(hDC);
}

void CStage3::Release()
{
	CObjManager::Get_Instance()->Release();
	CTileManager::Get_Instance()->Release();
	CUIManager::Get_Instance()->Release();
	CKeyManager::Get_Instance()->Release();
	CEffectManager::Get_Instance()->Release();
}

void CStage3::Mange_Bgm() {

	if (m_bOnceBgm == 0) {
		if (!CSoundManager::Get_Instance()->IsSoundFinished(SOUND_BGM)) {
			return;
		}
		else {
			CSoundManager::Get_Instance()->PlaySound(L"BGM_3_Intro.wav", SOUND_BGM, 0.5f);
			m_bOnceBgm++;
		}

	}
	if (m_bOnceBgm == 1) {
		if (!CSoundManager::Get_Instance()->IsSoundFinished(SOUND_BGM)) {
			return;
		}
		else {
			CSoundManager::Get_Instance()->PlaySound(L"BGM_3_P1_merged.wav", SOUND_BGM, 0.5f);

		}


	}
}
