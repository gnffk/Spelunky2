#include "pch.h"
#include "Bullet.h"
#include "BmpManager.h"
CBullet::CBullet()
{
}
CBullet::~CBullet()
{
}
void CBullet::Initialize()
{
	m_eCollisionType = C_BULLET;
	m_eRender = GAMEOBJECT;
	m_fSpeed = 20.f;

	if (m_eDir == DIR_RIGHT) {
		m_fSpeed *= 1;
	}
	else {
		m_fSpeed *= -1;
	}
	m_fRealSize = { 10.f, 10.f };
	firstPos = { m_tInfo.fX, m_tInfo.fY };
}

int CBullet::Update(float deltatime)
{
	__super::Update_Rect();
	if (fabsf(fabsf(firstPos.x) - fabsf(m_tInfo.fX)) > 400) {
		return OBJ_DEAD;
	}
	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY = m_tInfo.fY * cosf(m_fAngle * PI / 180);
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(float deltatime)
{//14
}

void CBullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);

	HDC hMemDc = CBmpMgr::Get_Instance()->Find_Image(L"Item");
	GdiTransparentBlt(hDC,
		m_tRect.left-50,
		m_tRect.top- 50,
		(int)m_tInfo.fCX + 100,
		(int)m_tInfo.fCY + 100,
		hMemDc,
		0 * 128,
		14 * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void CBullet::Release()
{
}
