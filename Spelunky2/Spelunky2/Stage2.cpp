#include "pch.h"
#include "Stage2.h"
#include "Obj.h"
#include "TileManager.h"
#include "CameraManager.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "UIManager.h"
#include "KeyManager.h"

#include "CollisionManager.h"

#include "Player.h"
#include "AbstractFactory.h"
#include "PlayerUI.h"
#include "DeadUI.h"
#include "SceneManager.h"

#include "ShotGun.h"
#include "Gold.h"
#include "BombPackage.h"
#include "RopePackage.h"
#include "SoundManager.h"

#include "Bat.h"
#include "Snake.h"
#include "Tile.h"
#include "Whip.h"
#include "ShopMan.h"

#include "EffectManager.h"
#include "Openkey.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Bat_IDLE.bmp", L"Bat_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Bat_Right.bmp", L"Bat_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Bat_Left.bmp", L"Bat_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Snake_Right.bmp", L"Snake_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Snake_Left.bmp", L"Snake_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Man_Left.bmp", L"Man_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Man_Right.bmp", L"Man_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/border_main.bmp", L"Border");

	CKeyManager::Get_Instance()->Initialize();
	CTileManager::Get_Instance()->Load_Tile(L"../Data/Stage_Dum.dat");
	//CTileManager::Get_Instance()->Load_Tile(L"../Data/Stage2.dat");

	m_pPlayer = CAbstractFactory<CPlayer>::Create();
	m_pPlayer->Initialize();
	CObjManager::Get_Instance()->AddObject(OBJ_PLAYER, m_pPlayer);
	
	CCameraManager::Get_Instance()->Initialize();
	CCameraManager::Get_Instance()->SetTarget(m_pPlayer);


	baseUI = new CPlayerUI;
	dynamic_cast<CPlayerUI*>(baseUI)->Set_Targert(m_pPlayer);
	dynamic_cast<CPlayerUI*>(baseUI)->Set_Scene(this);
	CUIManager::Get_Instance()->Add_UI(baseUI);

	DeadUI = new CDeadUI;
	//dynamic_cast<CPlayerUI*>(DeadUI)->Set_Targert(m_pPlayer);
	dynamic_cast<CDeadUI*>(DeadUI)->Set_Scene(this);
	CUIManager::Get_Instance()->Add_UI(DeadUI);
	
	CUIManager::Get_Instance()->Initialize();




	m_StartTime = 0;
	m_CurrTime = 0;

	m_bOnceBgm = 0;

	CTileManager::Get_Instance()->Check_Tile();
	CEffectManager::Get_Instance()->Initialize();
	Spone();



}
	
void CStage2::Update(float deltatime)
{
	m_CurrTime += deltatime;
	CCameraManager::Get_Instance()->Update(deltatime);

	CObjManager::Get_Instance()->Update(deltatime);

	CTileManager::Get_Instance()->Update(deltatime);
	CUIManager::Get_Instance()->Update(deltatime);
	CEffectManager::Get_Instance()->Update(deltatime);
	Key_Set();
	Mange_Bgm();
}

void CStage2::Late_Update(float deltatime)
{
	CObjManager::Get_Instance()->Late_Update(deltatime);
	CUIManager::Get_Instance()->Late_Update(deltatime);
	CEffectManager::Get_Instance()->Late_Update(deltatime);
	
	CCollisionManager::Collision_RectEx_Player(m_pPlayer, CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Item(CObjManager::Get_Instance()->Get_TypeObj(OBJ_ITEM), CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Player_Item(m_pPlayer, CObjManager::Get_Instance()->Get_TypeObj(OBJ_ITEM));
	CCollisionManager::Collision_RectEx_Enemy(CObjManager::Get_Instance()->Get_TypeObj(OBJ_MONSTER), CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Player_Enemy(m_pPlayer, CObjManager::Get_Instance()->Get_TypeObj(OBJ_MONSTER));
	CCollisionManager::Collision_RectEx_Particle(CEffectManager::Get_Instance()->GetParticle(), CTileManager::Get_Instance()->GetTile());
	CCollisionManager::Collision_RectEx_Bullet_ENEMY(CObjManager::Get_Instance()->Get_TypeObj(OBJ_BULLET),CObjManager::Get_Instance()->Get_TypeObj(OBJ_MONSTER) );

	if(static_cast<CWhip*>(static_cast<CPlayer*>(m_pPlayer)->Get_Weapon())->Get_State() ==  CWhip::ATTACKGO){
		CCollisionManager::Collision_RectEx_Weapon_Enemy(static_cast<CPlayer*>(m_pPlayer)->Get_Weapon(), CObjManager::Get_Instance()->Get_TypeObj(OBJ_MONSTER));
	}
	
}

void CStage2::Render(HDC hDC)
{
	Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();
	//HDC LAYERUI = CBmpMgr::Get_Instance()->Find_Image(L"Cave_Layer");
	//GdiTransparentBlt(hDC,
	//	-cameraPos.x,
	//	-cameraPos.y,
	//	4000,
	//	4000,
	//	LAYERUI,
	//	0,
	//	0,
	//	(int)4000,
	//	(int)4000,
	//	RGB(255, 255, 255));

	HDC LAYERUI = CBmpMgr::Get_Instance()->Find_Image(L"Cave_Layer");
	GdiTransparentBlt(hDC,
		-cameraPos.x,
		-cameraPos.y,
		4000,
		4000,
		LAYERUI,
		0,
		0,
		(int)4000,
		(int)4000,
		RGB(255, 255, 255));
	CTileManager::Get_Instance()->Render(hDC);
	CObjManager::Get_Instance()->Render(hDC);

	CEffectManager::Get_Instance()->Render(hDC);

	CUIManager::Get_Instance()->Render(hDC);
}

void CStage2::Release()
{
	CObjManager::Get_Instance()->Release();
	CTileManager::Get_Instance()->Release();
	CUIManager::Get_Instance()->Release();
	CKeyManager::Get_Instance()->Release();
	CEffectManager::Get_Instance()->Release();
}

void CStage2::Spone()
{
	CObj* obj = CAbstractFactory<CBat>::Create(2000,100);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3520, 1680);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(880,1380);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(560, 2180);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(560, 2740);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3200, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3250, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3300, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3350, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3400, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3450, 1120);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);


	obj = CAbstractFactory<CBat>::Create(2340, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(2440, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(2540, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);


	obj = CAbstractFactory<CBat>::Create(2640, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);


	obj = CAbstractFactory<CBat>::Create(2740, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(2840, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(2940, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3040, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3140, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3240, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);

	obj = CAbstractFactory<CBat>::Create(3340, 3400);
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, obj);
	dynamic_cast<CBat*>(obj)->Set_Target(m_pPlayer);


	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1040, 2040));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(3120, 840));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1600, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1500, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1400, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1300, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1200, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1100, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1000, 3720));
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(900, 3720));
	//CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CShopMan>::Create(3140, 3360));
	
	
	CObjManager::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CShopMan>::Create(3750, 400));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CShotGun>::Create(3250,400,true));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<COpenKey>::Create(640,2880,true));
	//CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<COpenKey>::Create(200,200,true));
	//CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<COpenKey>::Create(100,300,true));
	//CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CShotGun>::Create(1300, 100,true));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CBombPackage>::Create(3400, 400, true));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CRopePackage>::Create(3550, 400, true));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CRopePackage>::Create(3680, 800, false));

	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(2270, 1100));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(1090, 920));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3680, 400));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3680, 2480));

	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3200, 1280));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3300, 1280));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3400, 1280));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(3500, 1280));
	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(320, 1600));

	CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CGold>::Create(240, 1920));

	
	//3040 3360
}

void CStage2::Key_Set() {
	if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Next() && CKeyManager::Get_Instance()->Key_Up(VK_RETURN)) {
		m_pPlayer->Set_Remain(true);
		if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hand()) {
			dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hand()->Set_Remain(true);
		}
		dynamic_cast<CPlayer*>(m_pPlayer)->SetCurrentState(CPlayer::DISAPPEARED);
		baseUI->Set_Remain(true);
	
		CSceneManager::Get_Instance()->Change_Scene(SCSTAGE3);
	}

	if (CKeyManager::Get_Instance()->Key_Down('9')) {
		g_viewCollisionBox = !g_viewCollisionBox;
	}
	if (CKeyManager::Get_Instance()->Key_Down('8')) {
		for (int i = 0; i < 5; ++i) {
			CEffectManager::Get_Instance()->Paricle_Effect({ m_pPlayer->Get_Info()->fX, m_pPlayer->Get_Info()->fY },1);

		}
	}

}

void CStage2::Mange_Bgm() {

	if (m_bOnceBgm == 0) {
		if (!CSoundManager::Get_Instance()->IsSoundFinished(SOUND_BGM)) {
			return;
		}
		else {
			CSoundManager::Get_Instance()->PlaySound(L"BGM_1_Adventure.wav", SOUND_BGM, 0.5f);
			m_bOnceBgm++;
		}
		
	}
	if (m_bOnceBgm == 1) {
		if (!CSoundManager::Get_Instance()->IsSoundFinished(SOUND_BGM)) {
			return;
		}
		else {
			CSoundManager::Get_Instance()->PlaySound(L"BGM_Combined_SuperSmooth.wav", SOUND_BGM, 0.5f);
		
		}
		
		
	}
}
