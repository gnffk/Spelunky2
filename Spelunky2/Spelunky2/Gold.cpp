#include "pch.h"
#include "Gold.h"
#include "BmpManager.h"
#include "SoundManager.h"
CGold::CGold()
{
}

CGold::~CGold()
{
}

void CGold::Initialize()
{
	m_eCollisionType = C_ITEM;
	m_eItemType = ITEM_GOLD;
	m_eRender = GAMEOBJECT;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	m_tInfo.fX = 1100.f;
	m_tInfo.fY = 150.f;
	m_fRealSize = { 40.f, 30.f };

	m_tFrame.bLoop = true;
	m_tFrame.iBegin = 11;
	m_tFrame.iStart = 11;
	m_tFrame.iEnd = 15;
	m_tFrame.iMotion = 9;
	m_tFrame.dwSpeed = 150;
	m_tFrame.dwTime = GetTickCount();
	

	m_hDCGold = CBmpMgr::Get_Instance()->Find_Image(L"Item");
}

int CGold::Update(float deltatime)
{

	if (m_bDead) {
		CSoundManager::Get_Instance()->PlaySound(L"gold01.wav", SOUND_EFFECT, 1.f);

		return OBJ_DEAD;
	}
	__super::Update_Rect();
	m_tInfo.fY += m_tGravity;
	Move_Frame_Right();
	return OBJ_NOEVENT;
}

void CGold::Late_Update(float deltatime)
{
}

void CGold::Render(HDC hDC)
{
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hDCGold,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void CGold::Release()
{
}
