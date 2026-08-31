#include "pch.h"
#include "Tether.h"
#include "BmpManager.h"
#include "CameraManager.h"

CTether::CTether()
{
}

CTether::~CTether()
{
}
// 씬전환 하면서 끝까지 되는거 확인하는거 
void CTether::Initialize()
{
	m_eCollisionType = LADDER;
	m_eRender = TETHER;
	m_fSpeed = 10;
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fRealSize = { 40.f, 40.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/player/right_character.bmp", L"Tether");

	m_tFrame.iStart = 12;
	m_tFrame.iEnd = 12;
	m_tFrame.iMotion = 9;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.bLoop = true;

	m_bCollision = false;
	m_eTetherState = UP;
	m_fDistance = 500.f;
	m_VMovePos = {0,0};
	m_iCount = 0;
}

int CTether::Update(float deltatime)
{

	__super::Update_Rect();

	Change_State();
	Move_Frame_Tether();
	Environment_State();
	return OBJ_NOEVENT;
}

void CTether::Late_Update(float deltatime)
{
}

void CTether::Render(HDC hDC)
{
	HDC hTetherDC = CBmpMgr::Get_Instance()->Find_Image(L"Tether");

	//Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hTetherDC,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));


		for (int i = 0; i < m_iSize; ++i) {
			if (m_vecRenderTrue[i].bEnd == false && m_vecRenderTrue[i].bRender == true ) {
				GdiTransparentBlt(hDC,
					m_tRect.left,
					m_tRect.top + 40.f * (i+1) ,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					hTetherDC,
					m_MoveFrame.iStart * 128,
					12 * 128,
					128,
					128,
					RGB(255, 255, 255));
			}
			else if (m_vecRenderTrue[i].bEnd == true && m_vecRenderTrue[i].bRender == true) {
				GdiTransparentBlt(hDC,
					m_tRect.left,
					m_tRect.top + 40.f * (i+1),
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					hTetherDC,
					0 * 128,
					12 * 128,
					128,
					128,
					RGB(255, 255, 255));
			}
		}

	
	
	
}

void CTether::Release()
{
}

void CTether::Change_State() {
	if (m_ePreTetherState != m_eTetherState) {
		switch (m_eTetherState) {
		case UP:
		{
			m_tFrame.iStart = 12;
			m_tFrame.iEnd = 12;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bLoop = true;
		}
		break;

		case STOP:
		{
			m_tFrame.iStart = 13;
			m_tFrame.iEnd = 13;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bLoop = false;

			m_iSize = (m_vFirstPos.y - m_tInfo.fY) / 40;
			m_fRealSize.y = 40 * m_iSize;
			m_vecRenderTrue.reserve(m_iSize);
			for (int i = 0; i < m_iSize; ++i) {
				m_vecRenderTrue.push_back({false, false});
			}
		}
		break;

		case DOWN:
		{
			m_MoveFrame.iStart = 3;
			m_MoveFrame.iBegin = 3;
			m_MoveFrame.iEnd = 3;
			m_MoveFrame.iMotion = 12;
			m_MoveFrame.dwSpeed = 10;
			m_MoveFrame.dwTime = GetTickCount();
			m_MoveFrame.bLoop = false;
		
		}
		break;
		case COMPLETE:
		{

		}
		break;
		}

		m_ePreTetherState = m_eTetherState;
	}

	
}

void CTether::Environment_State() {
	switch (m_eTetherState) {
	case UP:
	{
		m_tInfo.fY -= m_fSpeed;
		if (m_vFirstPos.y - m_tInfo.fY > m_fDistance || m_bCollision) {
			m_eTetherState = STOP;
		}
	}
	break;

	case STOP:
	{
		m_eTetherState = DOWN;
	
		m_iCount++;
		if (m_iCount-1 == m_iSize) {
			m_eTetherState = COMPLETE;
		}

		m_vecRenderTrue[m_iCount-1] = {true, false};
		m_fTime = GetTickCount();
	}
	break;

	case DOWN:
	{
		if (m_MoveFrame.iStart == m_MoveFrame.iEnd) {
			if (m_fTime + 1 < GetTickCount()) {
				m_vecRenderTrue[m_iCount - 1] = { true, true };
				m_eTetherState = STOP;
			}
			
		}
		
	}
	break;
	case COMPLETE:
	{

	}
	break;
	}
}

void CTether::Move_Frame_Tether() {
	if (m_eTetherState == DOWN) {
		if (m_fTime + 1 < GetTickCount()) {
			++m_MoveFrame.iStart;
			m_MoveFrame.dwTime = GetTickCount();

			if (m_MoveFrame.iStart > m_MoveFrame.iEnd && !(m_MoveFrame.bLoop)) {
				m_MoveFrame.iStart = m_MoveFrame.iEnd;
			}



			if (m_MoveFrame.iStart > m_MoveFrame.iEnd && (m_MoveFrame.bLoop))
				m_MoveFrame.iStart = m_MoveFrame.iBegin;


			}
			
	}

}