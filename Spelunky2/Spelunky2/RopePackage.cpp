#include "pch.h"
#include "RopePackage.h"
#include "BmpManager.h"
#include "StoreUI.h"
#include "UIManager.h"
#include "SoundManager.h"
CRopePackage::CRopePackage() : m_pStoreUI(nullptr)
{
}

CRopePackage::~CRopePackage()
{
}

void CRopePackage::Initialize()
{
	m_eCollisionType = C_ITEM;
	m_eItemType = ITEM_ROPE_PACKAGE;
	m_eRender = GAMEOBJECT;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	m_tInfo.fX = 1300.f;
	m_tInfo.fY = 150.f;
	m_fRealSize = { 40.f, 40.f };


	m_bStore = false;

	m_hDCRopePackage = CBmpMgr::Get_Instance()->Find_Image(L"Item");
}

int CRopePackage::Update(float deltatime)
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

void CRopePackage::Late_Update(float deltatime)
{
}

void CRopePackage::Render(HDC hDC)
{
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hDCRopePackage,
		0 * 128,
		6 * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void CRopePackage::Release()
{
}
void CRopePackage::IsPurChase() {
	if (m_bStore && m_pStoreUI == nullptr) {
		m_pStoreUI = new CStoreUI;
		m_pStoreUI->Initialize();
		CUIManager::Get_Instance()->Add_UI(m_pStoreUI);
		dynamic_cast<CStoreUI*>(m_pStoreUI)->Set_Target(this);
	}
}