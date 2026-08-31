#include "pch.h"
#include "StoreUI.h"
#include "BmpManager.h"
#include "CameraManager.h"
#include "Obj.h"

CStoreUI::CStoreUI()
{
}
CStoreUI::~CStoreUI()
{
}

void CStoreUI::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/StoreUI.bmp", L"StoreUI");

	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 96.f;
	m_bIN = false;
	int result = AddFontResourceEx(L"../Font/FiraSans-ExtraBold.ttf", FR_PRIVATE, NULL);
	m_bChange = 0;
	m_hFont = CreateFont(
		30, 0, 0, 0,
		FW_ULTRABOLD, FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		L"Fira Sans ExtraBold"
	);
}

int CStoreUI::Update(float deltatime)
{
	if (m_pTarget) {
		Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();

		m_tRect.left = LONG(m_pTarget->Get_Info()->fX - (m_tInfo.fCX / 2.f)) - cameraPos.x;
		m_tRect.top = LONG(m_pTarget->Get_Info()->fY - (m_tInfo.fCY / 2.f)) - cameraPos.y;
		m_tRect.right = LONG(m_pTarget->Get_Info()->fX + (m_tInfo.fCX / 2.f)) - cameraPos.x;
		m_tRect.bottom = LONG(m_pTarget->Get_Info()->fY + (m_tInfo.fCY / 2.f)) - cameraPos.y;
	}



    return 0;
}

void CStoreUI::Late_Update(float deltatime)
{
}

void CStoreUI::Render(HDC hDC)
{
	if (m_bIN && m_pTarget->Get_Store()) {
		
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top - 100,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			HDCUI,
			0,
			0,
			256,
			128,
			RGB(255, 255, 255));

		Target_Write(hDC);

	}
	
	
}

void CStoreUI::Release()
{
}

void CStoreUI::Target_Write(HDC hDC) {
	if (m_pTarget->Get_ItemType() == ITEM_SHOTGUN) {
		HDCUI = CBmpMgr::Get_Instance()->Find_Image(L"StoreUI");
		HFONT old = (HFONT)SelectObject(hDC, m_hFont);
		SetTextColor(hDC, RGB(0, 0, 0));
	
		SetBkMode(hDC, TRANSPARENT);
		wchar_t buff_1[32];
		swprintf_s(buff_1, L"SHOTGUN");

		TextOut(hDC, m_tRect.left+40, m_tRect.top-90, buff_1, wcslen(buff_1));
		SetTextColor(hDC, RGB(255, 201, 14));
		wchar_t buff_2[32];
		swprintf_s(buff_2, L"5000¿ø");

		TextOut(hDC, m_tRect.left + 60, m_tRect.top - 60, buff_2, wcslen(buff_2));

		SelectObject(hDC, old);
	}

	if (m_pTarget->Get_ItemType() == ITEM_BOMB_PACKAGE) {
		HDCUI = CBmpMgr::Get_Instance()->Find_Image(L"StoreUI");
		HFONT old = (HFONT)SelectObject(hDC, m_hFont);
		SetTextColor(hDC, RGB(0, 0, 0));

		SetBkMode(hDC, TRANSPARENT);
		wchar_t buff_1[32];
		swprintf_s(buff_1, L"BOMB_PACKAGE");

		TextOut(hDC, m_tRect.left + 5, m_tRect.top - 90, buff_1, wcslen(buff_1));
		SetTextColor(hDC, RGB(255, 201, 14));
		wchar_t buff_2[32];
		swprintf_s(buff_2, L"1000¿ø");

		TextOut(hDC, m_tRect.left + 60, m_tRect.top - 60, buff_2, wcslen(buff_2));

		SelectObject(hDC, old);
	}

	if (m_pTarget->Get_ItemType() == ITEM_ROPE_PACKAGE) {
		HDCUI = CBmpMgr::Get_Instance()->Find_Image(L"StoreUI");
		HFONT old = (HFONT)SelectObject(hDC, m_hFont);
		SetTextColor(hDC, RGB(0, 0, 0));

		SetBkMode(hDC, TRANSPARENT);
		wchar_t buff_1[32];
		swprintf_s(buff_1, L"ROPE_PACKAGE");

		TextOut(hDC, m_tRect.left + 5, m_tRect.top - 90, buff_1, wcslen(buff_1));
		SetTextColor(hDC, RGB(255, 201, 14));
		wchar_t buff_2[32];
		swprintf_s(buff_2, L"1000¿ø");

		TextOut(hDC, m_tRect.left + 60, m_tRect.top - 60, buff_2, wcslen(buff_2));

		SelectObject(hDC, old);
	}

	if (m_pTarget->Get_EnemyType() == ENEMY_SHOPMAN) {
		HDCUI = CBmpMgr::Get_Instance()->Find_Image(L"AnswerUI");
		HFONT old = (HFONT)SelectObject(hDC, m_hFont);
		SetTextColor(hDC, RGB(0, 0, 0));

		SetBkMode(hDC, TRANSPARENT);
	
		if (m_bChange == 0) {
			wchar_t buff_1[32];
			swprintf_s(buff_1, L"µ·À»ÁÖ¸é ¿­¼è¸¦ÁÖÁö");
			TextOut(hDC, m_tRect.left, m_tRect.top - 90, buff_1, wcslen(buff_1));
			SetTextColor(hDC, RGB(255, 201, 14));
			wchar_t buff_2[32];
			swprintf_s(buff_2, L"5000¿ø");

			TextOut(hDC, m_tRect.left + 60, m_tRect.top - 60, buff_2, wcslen(buff_2));
		}
		if (m_bChange == 1) {
			wchar_t buff_1[32];
			swprintf_s(buff_1, L"¸ÛÃ»ÇÑ ³ð");
			TextOut(hDC, m_tRect.left+50, m_tRect.top - 80, buff_1, wcslen(buff_1));
		}

	

		SelectObject(hDC, old);
	}
}