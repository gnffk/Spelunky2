#include "pch.h"
#include "DeadUI.h"
CDeadUI::CDeadUI() : m_pTarget(nullptr), m_pScene(nullptr), m_bDead(false)
{
}
CDeadUI::~CDeadUI()
{
}
void CDeadUI::Initialize()
{
	m_tInfo.fCX = 800;
	m_tInfo.fCY = 400;
	m_tInfo.fX = WINCX/2;
	m_tInfo.fY = -200;
	m_bDead = false;
	m_bReverse = false;
	m_fAcceleration = 0;
	m_fSpeed = 10;

	m_fDistance = 30;
}

int CDeadUI::Update(float deltatime)
{
	Player_Dead(deltatime);

	return 0;
}

void CDeadUI::Late_Update(float deltatime)
{
}

void CDeadUI::Render(HDC hDC)
{
	Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fX + m_tInfo.fCX / 2, m_tInfo.fY + m_tInfo.fCY / 2);
}

void CDeadUI::Release()
{
}

void CDeadUI::Player_Dead(float deltatime) {
	if (m_bDead) {
		if (!m_bReverse) {
			m_tInfo.fY += m_fSpeed * m_fAcceleration;
			m_fAcceleration += deltatime * 0.3f;
												
			if (m_tInfo.fY > WINCY / 2) {
				m_bReverse = true;
				m_fAcceleration = 0;
				m_ReversePos.y = m_tInfo.fY;
			
			}

			if (m_fDistance < 1.f) {
				m_fDistance = 0.f;
				m_bDead = false;
			}

			if (m_fAcceleration > 10) {
				m_fAcceleration = 10;
			}
		}

		if (m_bReverse) {
			m_tInfo.fY += m_fSpeed * m_fAcceleration;
			m_fAcceleration -= deltatime * 0.3f;
			if (m_ReversePos.y - m_tInfo.fY > m_fDistance) {
				m_ReversePos.y = m_tInfo.fY;
				m_bReverse = false;
			
				m_fDistance /= 3;
			}
		}
	
		
	
	}
}