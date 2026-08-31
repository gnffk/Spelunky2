#include "pch.h"
#include "Whip.h"
#include "BmpManager.h"
#include "Player.h"
#include "SoundManager.h"
CWhip::CWhip() : m_pTarget(nullptr)
{
}
CWhip::~CWhip()
{
}
void CWhip::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_eState = NONE;
	m_fRealSize = { 40.f,  40.f };
	m_tInfo = { m_pTarget->Get_Info()->fX,m_pTarget->Get_Info()->fY, 80,80};

	m_tFrame.bLoop = false;
	m_tFrame.iBegin = 10;
	m_tFrame.iStart = 10;
	m_tFrame.iEnd = 15;
	m_tFrame.iMotion = 12;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CWhip::Update(float deltatime)
{
	__super::Update_Rect();

	if (m_eState != m_ePreState) {
		switch (m_eState) {
		case NONE:

			break;

		case ATTACKREADY: {
			if ((m_pTarget)->GetDirect() == DIR_RIGHT) {
				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 10;
				m_tFrame.iStart = 10;
				m_tFrame.iEnd = 13;
				m_tFrame.iMotion = 12; 
				m_tFrame.dwSpeed = 80;
				m_tFrame.dwTime = GetTickCount();
				m_fDistance = 60.f;
				m_fDistance_Y = 20.f;
			}
			if ((m_pTarget)->GetDirect() == DIR_LEFT) {
				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 5;
				m_tFrame.iStart = 5;
				m_tFrame.iEnd = 2;
				m_tFrame.iMotion = 12;
				m_tFrame.dwSpeed = 80;
				m_tFrame.dwTime = GetTickCount();
				m_fDistance = -60.f;
				m_fDistance_Y = 20.f;
			}
		}
				   break;

		case ATTACKGO: {
			if ((m_pTarget)->GetDirect() == DIR_RIGHT) {
				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 14;
				m_tFrame.iStart = 14;
				m_tFrame.iEnd = 15;
				m_tFrame.iMotion = 12;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				m_fDistance = -20.f;
				m_fDistance_Y = -5.f;
			}
			if ((m_pTarget)->GetDirect() == DIR_LEFT) {
				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 1;
				m_tFrame.iStart = 1;
				m_tFrame.iEnd = 0;
				m_tFrame.iMotion = 12;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				m_fDistance = 20.f;
				m_fDistance_Y = -5.f;
			}
		}
						break;
		}
		m_ePreState = m_eState;
	}
	
	CWhip_Move();
	Whip_Enviornment();
	return 0;
}

void CWhip::Late_Update(float deltatime)
{
}

void CWhip::Render(HDC hDC)
{
	//Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);

	if (m_eState != NONE) {
		if ((m_pTarget)->GetDirect() == DIR_RIGHT) {
			Right = CBmpMgr::Get_Instance()->Find_Image(L"Right_Player");
			GdiTransparentBlt(hDC,
				m_tRect.left + 30 -m_fDistance,
				m_tRect.top+10 - m_fDistance_Y,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				Right,
				m_tFrame.iStart * 128,
				m_tFrame.iMotion * 128,
				128,
				128,
				RGB(255, 255, 255));
		}
		if ((m_pTarget)->GetDirect() == DIR_LEFT) {
			Left = CBmpMgr::Get_Instance()->Find_Image(L"Left_Player");
			GdiTransparentBlt(hDC,
				m_tRect.left - 30 - m_fDistance,
				m_tRect.top+10 - m_fDistance_Y,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				Left,
				m_tFrame.iStart * 128,
				m_tFrame.iMotion * 128,
				128,
				128,
				RGB(255, 255, 255));
		}
	}


}

void CWhip::Release()
{
}

void CWhip::CWhip_Move() {
	if ((m_pTarget)->GetDirect() == DIR_RIGHT) {
		Move_Frame_Right();
	

	}
	else {
		Move_Frame_Left();
	
	}
}

void CWhip::Whip_Enviornment() {
	switch (m_eState) {
	case NONE:

		break;

	case ATTACKREADY: {
		if (m_tFrame.iStart == m_tFrame.iEnd) {
			m_eState = ATTACKGO;
			CSoundManager::Get_Instance()->PlaySound(L"whip01a.wav", SOUND_EFFECT, 1.f);
	
		}
	}
		break;

	case ATTACKGO:
		m_fRealSize = { 160.f,  40.f };
		if (m_tFrame.iStart == m_tFrame.iEnd) {
			m_fTime = GetTickCount();
			m_eState = ATTACKEND;
			CSoundManager::Get_Instance()->PlaySound(L"whip_snap.wav", SOUND_EFFECT, 1.f);
		}
		break;

	case ATTACKEND:
	{
		m_fRealSize = { 40.f,  40.f };
		if (m_fTime + 70 < GetTickCount()) {
			m_eState = NONE;

		}
	}
		break;
	}
}