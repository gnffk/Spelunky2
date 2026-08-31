#include "pch.h"
#include "Tile.h"
#include "bmpManager.h"
#include "ObjManager.h"
#include "AbstractFactory.h"
#include "Bat.h"
CTile::CTile() : m_iMemDCTile{0,0}, m_floorx(false), m_Bomb(false)
{
	
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	m_eRender = TILE;
	m_eCollisionType = END;
	g_viewCollisionBox = TRUE;
	m_tInfo.fCX = TILEX;
	m_tInfo.fCY = TILEY;

	m_iDrawID = 0;
	m_iOption = 0;
	m_iLayer = 0;
	
	m_bDead = false;
	m_UP = false;
	m_DOWN = false;
	m_RIGHT = false;
	m_LEFT = false;
	m_hMemDC = nullptr;
}

int CTile::Update(float deltatime)
{
	// Layer = 1 iDrawID = 0~3 iOption 0~6 ≈∏¿œ
	
	if (m_bDead) {
		return OBJ_DEAD;
	}
	return 0;
}

void CTile::Late_Update(float deltatime)
{
}

void CTile::Render(HDC hDC)
{
	__super::Update_Rect();


	
	
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_hMemDC,
		m_iDrawID * 128,
		m_iOption * 128,
		m_iMemDCTile.x,
		m_iMemDCTile.y,
		RGB(255, 255, 255));

	if (m_eCollisionType == CollisionType::FLOOR && m_iLayer == 1) {
		if (m_UP) {
			// m_iDrawID <= 3 && m_iOption <= 6
			GdiTransparentBlt(hDC,
				m_tRect.left,
				m_tRect.top-40,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				m_hMemDC,
				5 * 128,
				6 * 128,
				m_iMemDCTile.x,
				m_iMemDCTile.y,
				RGB(255, 255, 255));
		}
		if (m_DOWN) {
			GdiTransparentBlt(hDC,
				m_tRect.left,
				m_tRect.top+40,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				m_hMemDC,
				5 * 128,
				7 * 128,
				m_iMemDCTile.x,
				m_iMemDCTile.y,
				RGB(255, 255, 255));
		}
		if (m_RIGHT) {
			GdiTransparentBlt(hDC,
				m_tRect.left+40,
				m_tRect.top,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				m_hMemDC,
				7 * 128,
				5 * 128,
				m_iMemDCTile.x,
				m_iMemDCTile.y,
				RGB(255, 255, 255));
		}
		if (m_LEFT) {
			GdiTransparentBlt(hDC,
				m_tRect.left-40,
				m_tRect.top,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				m_hMemDC,
				6 * 128,
				5 * 128,
				m_iMemDCTile.x,
				m_iMemDCTile.y,
				RGB(255, 255, 255));
		}
	}

	if (!g_viewCollisionBox) {

		if (m_tInfo.fX >= 0 && m_tInfo.fX <= MAPCX &&
			m_tInfo.fY >= 0 && m_tInfo.fY <= MAPCY) {



			HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);


			MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
			LineTo(hDC, m_tRect.right, m_tRect.top);

			LineTo(hDC, m_tRect.right, m_tRect.bottom);

			LineTo(hDC, m_tRect.left, m_tRect.bottom);

			LineTo(hDC, m_tRect.left, m_tRect.top);

			SelectObject(hDC, hOldPen);
			SelectObject(hDC, hOldBrush);


			DeleteObject(hPen);
			DeleteObject(hBrush);

			RECT   rcUI{ m_tRect.left, m_tRect.top , m_tRect.right, m_tRect.bottom };
			TCHAR   szbuffer[128];
			int      iTemp{};
			iTemp = swprintf_s(szbuffer, 128, L" x : %d \n y : %d \n", (int)(m_tInfo.fX)-TILEX/2, (int)(m_tInfo.fY)-TILEY / 2);
			//iTemp = swprintf_s(szbuffer, 128, L"Count : %d", m_iCount);
			DrawText(hDC, szbuffer, lstrlen(szbuffer), &rcUI, DT_LEFT);


		}
		else {

			HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
			LineTo(hDC, m_tRect.right, m_tRect.top);

			LineTo(hDC, m_tRect.right, m_tRect.bottom);

			LineTo(hDC, m_tRect.left, m_tRect.bottom);

			LineTo(hDC, m_tRect.left, m_tRect.top);


			SelectObject(hDC, hOldPen);
			SelectObject(hDC, hOldBrush);


			DeleteObject(hPen);
			DeleteObject(hBrush);
		}

		
	}

}

void CTile::Release()
{
}

void CTile::DifferentTypeDraw() {

}

void CTile::CheckLayer() {
	if (m_iLayer == 0) {
		m_hMemDC = nullptr;
		m_eCollisionType = CollisionType::END;
	}
	if (m_iLayer == 1) {
		//m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cave_2");
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TileTop");
		m_iMemDCTile.x = 128.f;
		m_iMemDCTile.y = 128.f;
		m_Bomb = true;

		
	
		if (m_iDrawID >= 0 && m_iDrawID <= 3 && m_iOption <= 6 && m_iOption >= 0) {
			
			m_floorx = true;
			m_eCollisionType = CollisionType::FLOOR;
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		}

		else if (m_iDrawID >= 4 && m_iDrawID <= 6 && m_iOption <= 9 && m_iOption >= 8) {
			m_floorx = true;
			m_eCollisionType = CollisionType::PITFALL;
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		}	
		
		else if (m_iDrawID >= 4 && m_iDrawID <= 4 && m_iOption <= 6 && m_iOption >= 0) {
			if (m_iOption == 2) {
				m_Ladder = true;
			}
			else {
				m_Ladder = false;
			}
			m_floorx = true;
			m_eCollisionType = CollisionType::LADDER;
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		}
	
		else if (m_iDrawID >= 1 && m_iDrawID <= 1 && m_iOption <= 11 && m_iOption >= 11) {
			m_eCollisionType = CollisionType::NEXTSTAGE;
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		}
		
		

		
	}

	if (m_iLayer == 2) {
		//m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cave_2");
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cave_3");
		m_iMemDCTile.x = 128.f;
		m_iMemDCTile.y = 128.f;
		m_Bomb = false;
		if (m_iDrawID >= 0 && m_iDrawID <= 3 && m_iOption <= 6 && m_iOption >= 0) {

			m_floorx = true;
			m_eCollisionType = CollisionType::FLOOR;
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		}
	}

	if (m_iLayer == 3) {
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Border");
		m_iMemDCTile.x = 128.f;
		m_iMemDCTile.y = 128.f;
		if (m_iDrawID >= 0 && m_iDrawID <=1 ) {
		
			m_eCollisionType = CollisionType::FLOOR;
			hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
		}
	}


}

CObj* CTile::Spone() {
	if (m_iLayer == 3) {
		m_hMemDC = nullptr;
		CAbstractFactory<CBat>::Create()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		
		return 	CAbstractFactory<CBat>::Create();
		
	}
}