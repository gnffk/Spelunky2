#include "pch.h"
#include "Mouse.h"
#include "CameraManager.h"
#include "KeyManager.h"
#include "TileManager.h"
CMouse::CMouse()
{
}
CMouse::~CMouse()
{
    Release();
}
void CMouse::Initialize()
{
	m_eRender = GAMEOBJECT;
    m_tInfo.fCX = 20.f;
    m_tInfo.fCY = 20.f;
	WindowPos.x = WINCX / 2;
	WindowPos.y = WINCY / 2;
}

int CMouse::Update(float deltatime)
{
	
	POINT		ptMouse{};

	// 화면 자체(모니터)를 기준으로 얻어옴
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);
	Vec2 Camera = CCameraManager::Get_Instance()->GetDistance();
	m_tInfo.fX = (float)ptMouse.x + Camera.x;
	m_tInfo.fY = (float)ptMouse.y + Camera.y;

	WindowPos.x = ptMouse.x;
	WindowPos.y = ptMouse.y;


	ShowCursor(false);
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(float deltatime)
{
}

void CMouse::Render(HDC hDC)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(127, 127, 127));

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);


	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	SelectObject(hDC, hOldBrush);

	DeleteObject(hBrush);

	RECT   rcUI{ m_tRect.left+20, m_tRect.top, m_tRect.right+400, m_tRect.bottom };
	TCHAR   szbuffer[128];
	int      iTemp{};
	//iTemp = swprintf_s(szbuffer, 128, L" x : %d  y : %d\n", (int)(WindowPos.x), (int)(WindowPos.y));
	iTemp = swprintf_s(szbuffer, 128, L" x : %d  y : %d\n", (int)(m_tInfo.fX), (int)(m_tInfo.fY));
	//iTemp = swprintf_s(szbuffer, 128, L"Count : %d", (((int)(m_tInfo.fY )/TILENUMY)));
	DrawText(hDC, szbuffer, lstrlen(szbuffer), &rcUI, DT_LEFT);

}

void CMouse::Release()
{
}


