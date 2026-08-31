#include "pch.h"
#include "CEffect.h"
#include "BmpManager.h"
CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
}

void CEffect::InitValue(Vec2 pos, Vec2 vel, float life, int gen, int type)
{
	m_tInfo = { pos.x, pos.y, 210, 210 };
	
	switch (type) {
	case 1:
		m_hMiddleDC = CBmpMgr::Get_Instance()->Find_Image(L"Fire");
		m_tFrame.bLoop = false;
		m_tFrame.iBegin = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
		m_tInfo.fCX = 120;
		m_tInfo.fCY = 120;
		break;

	case 2:
		m_hMiddleDC = CBmpMgr::Get_Instance()->Find_Image(L"Bomb");
		m_tFrame.bLoop = false;
		m_tFrame.iBegin = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 10;
		m_tFrame.dwTime = GetTickCount();
		m_tInfo.fCX = 200;
		m_tInfo.fCY = 200;
		break;
	}
	
}

int CEffect::Update(float deltatime)
{
	__super::Update_Rect();
	if (m_tFrame.iStart == m_tFrame.iEnd) {
		return OBJ_DEAD;
	}

	Move_Frame();
	return OBJ_NOEVENT;
}

void CEffect::Late_Update(float deltatime)
{
}

void CEffect::Render(HDC hDC)
{
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hMiddleDC,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));
}

void CEffect::Release()
{
}
