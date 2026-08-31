#include "pch.h"
#include "BombPackage.h"
#include "BmpManager.h"
#include "UIManager.h"
#include "StoreUI.h"
#include "SoundManager.h"
CBombPackage::CBombPackage() : m_pStoreUI(nullptr)
{
}

CBombPackage::~CBombPackage()
{
}

void CBombPackage::Initialize()
{
	m_eCollisionType = C_ITEM;
	m_eItemType = ITEM_BOMB_PACKAGE;
	m_eRender = GAMEOBJECT;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	m_tInfo.fX = 1200.f;
	m_tInfo.fY = 150.f;
	m_fRealSize = { 40.f, 50.f };
	m_bStore = false;



	m_hDCBombPackage = CBmpMgr::Get_Instance()->Find_Image(L"Item");
}

int CBombPackage::Update(float deltatime)
{
	if (m_bDead) {
		CSoundManager::Get_Instance()->PlaySound(L"shop_buy.wav", SOUND_EFFECT, 1.f);

		return OBJ_DEAD;
	}
	__super::Update_Rect();
	m_tInfo.fY += m_tGravity;
	IsPurChase();
	return OBJ_NOEVENT;
}

void CBombPackage::Late_Update(float deltatime)
{
}

void CBombPackage::Render(HDC hDC)
{
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hDCBombPackage,
		1 * 128,
		2 * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void CBombPackage::Release()
{
}
void CBombPackage::IsPurChase() {
	if (m_bStore && m_pStoreUI == nullptr) {
		m_pStoreUI = new CStoreUI;
		m_pStoreUI->Initialize();
		CUIManager::Get_Instance()->Add_UI(m_pStoreUI);
		dynamic_cast<CStoreUI*>(m_pStoreUI)->Set_Target(this);
	}
}