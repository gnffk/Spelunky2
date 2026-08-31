#include "pch.h"
#include "ReadyUI.h"
CReadyUI::CReadyUI()
{
}

CReadyUI::~CReadyUI()
{
}

void CReadyUI::Initialize()
{
	int result = AddFontResourceEx(L"../Font/FiraSans-ExtraBold.ttf", FR_PRIVATE, NULL);

	m_hFont = CreateFont(
		50, 0, 0, 0,
		FW_HEAVY, FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		L"Fira Sans ExtraBold"
	);
	m_fColor1 = 255;
	m_fColor2 = 255;
	m_vStart = { WINCX / 2 - 50, 300 };
}

int CReadyUI::Update(float deltatime)
{
	if(m_vStart.x)
	return 0;
}

void CReadyUI::Late_Update(float deltatime)
{
}

void CReadyUI::Render(HDC hDC)
{
	HFONT old = (HFONT)SelectObject(hDC, m_hFont);
	SetTextColor(hDC, RGB(m_fColor1, m_fColor1, m_fColor1));
	SetBkMode(hDC, TRANSPARENT);
	wchar_t buff_1[32];
	swprintf_s(buff_1, L"Start");
	TextOut(hDC, m_vStart.x, m_vStart.y, buff_1, wcslen(buff_1));

	SetTextColor(hDC, RGB(m_fColor2, m_fColor2, m_fColor2));
	SetBkMode(hDC, TRANSPARENT);
	wchar_t buff_2[32];
	swprintf_s(buff_2, L"EXIT");
	TextOut(hDC, WINCX / 2 - 40, 400, buff_2, wcslen(buff_2));

	SelectObject(hDC, old);

}

void CReadyUI::Release()
{
}

void CReadyUI::Choice_Menu(int choice)
{
	switch (choice) {
	case 1:
		m_fColor1 = 127;
		m_fColor2 = 255;
		break;

	case 2:
		m_fColor1 = 255;
		m_fColor2 = 127;
		break;
	default:
		m_fColor1 = 255;
		m_fColor2 = 255;
		break;

	}
}