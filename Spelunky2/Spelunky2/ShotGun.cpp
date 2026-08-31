#include "pch.h"
#include "ShotGun.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "Bullet.h"
#include "StoreUI.h"
#include "UIManager.h"
#include "SoundManager.h"
CShotGun::CShotGun()
{
}

CShotGun::~CShotGun()
{
}

void CShotGun::Initialize()
{
	m_eCollisionType = C_ITEM;
	m_eItemType = ITEM_SHOTGUN;
	m_eRender = SHOTGUN;
	m_fSpeed = 10;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 150.f;
	m_fRealSize = { 40.f, 30.f };
	
	m_eDir = DIRECTION::DIR_RIGHT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RightItem.bmp", L"LeftShotGun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LeftItem.bmp", L"RightShotGun");
	m_tGravity = 9.8f;
	m_ShotgunState = IDLE;
	m_pStoreUI = nullptr;
	m_bStore = false;
}

int CShotGun::Update(float deltatime)
{
	__super::Update_Rect();

	Change_enviornment();
	IsPurChase();
	return 0;
}

void CShotGun::Late_Update(float deltatime)
{
}

void CShotGun::Render(HDC hDC)
{
	if (m_eDir == DIR_RIGHT) {
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RightShotGun");
		m_tFrame.iStart = 0;
	}
	else {
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LeftShotGun");
		m_tFrame.iStart = 15;
	}

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * 128,
		3 * 128,
		128,
		128,
		RGB(255, 255, 255));
	                        

}

void CShotGun::Release()
{
}

void CShotGun::Change_enviornment() {
	switch (m_ShotgunState) {
	case IDLE:
		m_tInfo.fY += m_tGravity;
		break;

	case GRAB:

		break;
	}
}

void CShotGun::Shot()
{
	CSoundManager::Get_Instance()->PlaySound(L"shotgun_fire01.wav", SOUND_EFFECT, 0.5f);
	for (int i = 0; i < 8; ++i) {

		CObjManager::Get_Instance()->AddObject(OBJ_BULLET,Create_Bullet());
	}
}

void CShotGun::IsPurChase() {
	if (m_bStore && m_pStoreUI == nullptr) {
		m_pStoreUI = new CStoreUI;
		m_pStoreUI->Initialize();
		CUIManager::Get_Instance()->Add_UI(m_pStoreUI);
		dynamic_cast<CStoreUI*>(m_pStoreUI)->Set_Target(this);
		
	}
}

CObj* CShotGun::Create_Bullet()
{
	CObj* bullet = new CBullet;
	bullet->Set_Direction(m_eDir);
	bullet->Set_Angle((rand() % 11) - 5);
	bullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	bullet->Initialize();
	return bullet;
}
