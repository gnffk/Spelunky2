#include "pch.h"
#include "Spider.h"
#include "BmpManager.h"
CSpider::CSpider() : m_pTarget(nullptr)
{
}

CSpider::~CSpider()
{
}


void CSpider::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_EnemyType = ENEMY_BAT;
	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_fRealSize = { 40.f, 40.f };



	m_curState = IDLE;
	m_eDir = DIR_RIGHT;
	m_fSpeed = 3.f;
}

int CSpider::Update(float deltatime)
{
	__super::Update_Rect();
	Check_Dir();
	Move_Dir();
	Motion_Change();
	Environment_Change(deltatime);
	return OBJ_NOEVENT;
}

void CSpider::Late_Update(float deltatime)
{
}

void CSpider::Render(HDC hDC)
{

	Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_MonsterHDC,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));


}

void CSpider::Release()
{
}

void CSpider::Search_Target()
{
	if (m_pTarget) {
		int x = (m_tInfo.fX - m_pTarget->Get_Info()->fX) * (m_tInfo.fX - m_pTarget->Get_Info()->fX);
		int y = (m_tInfo.fY - m_pTarget->Get_Info()->fY) * (m_tInfo.fY - m_pTarget->Get_Info()->fY);
		int distance = sqrt(x + y);


		if (distance <= 300) {
			m_curState = CHASE;
		}
	}
}

void CSpider::Chase_Target(float deltatime)
{
	float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);
	m_fSpeed += deltatime * 0.3f;

	if (m_fSpeed >= 3) {
		m_fSpeed = 3;
	}
	if (m_pTarget)
	{

		fWidth = m_pTarget->Get_Info()->fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info()->fY - m_tInfo.fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		if (m_pTarget->Get_Info()->fY > m_tInfo.fY)
			fRadian = 2.f * PI - fRadian;
	}

	m_tInfo.fX += cosf(fRadian) * m_fSpeed;
	m_tInfo.fY -= sinf(fRadian) * m_fSpeed;


}

void CSpider::Motion_Change() {
	if (m_curState != m_prevState || m_eDir != m_eprevDir) {
		switch (m_curState)
		{
		case IDLE:
		{
			m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Bat_IDLE");
			m_tFrame.bLoop = true;
			m_tFrame.iBegin = 0;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
		}
		break;
		case CHASE:
		{
			if (m_eDir == DIR_RIGHT) {
				m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Bat_Right");
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 0;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 5;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

			if (m_eDir == DIR_LEFT) {
				m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Bat_Left");
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 5;
				m_tFrame.iStart = 5;
				m_tFrame.iEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

		}
		break;

		}
		m_prevState = m_curState;
		m_eprevDir = m_eDir;
	}

}


void CSpider::Environment_Change(float deltatime) {
	switch (m_curState)
	{
	case IDLE:
	{
		Search_Target();
	}
	break;
	case CHASE:
	{
		Chase_Target(deltatime);

	}
	break;
	}
}

void CSpider::Move_Dir() {
	if (m_eDir == DIR_RIGHT) {
		Move_Frame_Right();
	}

	else if (m_eDir == DIR_LEFT) {
		Move_Frame_Left();
	}
	else {
		Move_Frame();
	}

}

void CSpider::Check_Dir() {
	if (m_pTarget) {
		if (m_pTarget->Get_Info()->fX > m_tInfo.fX) {
			m_eDir = DIR_RIGHT;
		}
		if (m_pTarget->Get_Info()->fX < m_tInfo.fX) {
			m_eDir = DIR_LEFT;
		}
	}
}