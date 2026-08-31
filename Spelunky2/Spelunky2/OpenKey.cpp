#include "pch.h"

#include "OpenKey.h"
#include "BmpManager.h"
#include "SoundManager.h"
COpenKey::COpenKey()
{
}

COpenKey::~COpenKey()
{
}

void COpenKey::Initialize()
{
	m_eCollisionType = C_ITEM;
	m_eItemType = ITEM_KEY;
	m_eRender = GAMEOBJECT;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	m_tInfo.fX = 1200.f;
	m_tInfo.fY = 150.f;
	m_fRealSize = { 40.f, 30.f };
	m_bStore = false;


	m_tGravity = 9.8f;
	m_hDCOpenKey = CBmpMgr::Get_Instance()->Find_Image(L"Item");
}

int COpenKey::Update(float deltatime)
{
	if (m_bDead) {
		CSoundManager::Get_Instance()->PlaySound(L"gold01.wav", SOUND_EFFECT, 1.f);

		return OBJ_DEAD;
	}

	__super::Update_Rect();

	m_tInfo.fY += m_tGravity * deltatime;

	return OBJ_NOEVENT;
}

void COpenKey::Late_Update(float deltatime)
{

}

void COpenKey::Render(HDC hDC)
{
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hDCOpenKey,
		8 * 128,
		1 * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void COpenKey::Release()
{
}
