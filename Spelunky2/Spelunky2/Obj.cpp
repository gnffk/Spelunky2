#include "pch.h"
#include "Obj.h"
#include "CameraManager.h"

CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_fDistance(0.f), m_tGravity(9.8f)
, m_pTarget(nullptr), m_pFrameKey(L""), m_bFloor(false), m_eRender(RENDER_END), m_bRemain(false), m_fStopCollision(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{

	//CCameraManager::Get_Instance()->GetCameraPos();
	//m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	//m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	//m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	//m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
	Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();

	m_tRect.left = LONG( m_tInfo.fX - (m_tInfo.fCX / 2.f)) - cameraPos.x;
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f)) - cameraPos.y;
	m_tRect.right = LONG( m_tInfo.fX + (m_tInfo.fCX / 2.f)) - cameraPos.x;
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f)) - cameraPos.y;

	m_CollisionRect.left = LONG(m_tInfo.fX - (m_fRealSize.x / 2.f)) - cameraPos.x;
	m_CollisionRect.top = LONG(m_tInfo.fY - (m_fRealSize.y / 2.f)) - cameraPos.y;
	m_CollisionRect.right = LONG(m_tInfo.fX + (m_fRealSize.x / 2.f)) - cameraPos.x;
	m_CollisionRect.bottom = LONG(m_tInfo.fY + (m_fRealSize.y / 2.f)) - cameraPos.y;

}

void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();


		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;

	}
}

void CObj::Move_Frame_Right()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStart > m_tFrame.iEnd && !(m_tFrame.bLoop)) {
			m_tFrame.iStart = m_tFrame.iEnd;
		}
			
		
			
		if (m_tFrame.iStart > m_tFrame.iEnd && (m_tFrame.bLoop))
			m_tFrame.iStart = m_tFrame.iBegin;

	}
}

void CObj::Move_Frame_Left()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		--m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStart < m_tFrame.iEnd && !(m_tFrame.bLoop)) {
			m_tFrame.iStart = m_tFrame.iEnd;
		}

		if (m_tFrame.iStart < m_tFrame.iEnd)
			m_tFrame.iStart = m_tFrame.iBegin;

	}
}

void CObj::Move_Frame_Free(int maxIndex, int firstMotion)
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
		if (maxIndex > m_tFrame.iStart) {
			++m_tFrame.iMotion;
			m_tFrame.iStart = 0;
		}

		if (m_tFrame.iStart > m_tFrame.iEnd) {
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = firstMotion;
		}
			

	}
}





