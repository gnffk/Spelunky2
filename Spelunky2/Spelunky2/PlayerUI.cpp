#include "pch.h"
#include "PlayerUI.h"
#include "BmpManager.h"
#include "Player.h"
#include "SceneManager.h"
CPlayerUI::CPlayerUI(): m_pTarget(nullptr)
{
	
}
CPlayerUI::~CPlayerUI()
{
	Release();
}
void CPlayerUI::Initialize()
{
	int result = AddFontResourceEx(L"../Font/FiraSans-ExtraBold.ttf", FR_PRIVATE, NULL);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BaseUI.bmp", L"Base_UI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BaseUI2.bmp", L"Base_UI2");

	m_tInfo = { 0,0,633,67 };

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
	SCENEID ID = CSceneManager::Get_Instance()->GetCurScene();
	switch (ID) {
	case SCMENU:

		break;

	case SCMAPEDIT:

		break;
	case SCSTAGE2:
		m_stageName = L"1-2";
		break;
	case SCSTAGE3:
		m_stageName = L"1-3";
		break;

	}


}

int CPlayerUI::Update(float deltatime)
{
	//__super::Update_Rect();

	return 0;
}

void CPlayerUI::Late_Update(float deltatime)
{
}

void CPlayerUI::Render(HDC hDC)
{
	HDC HDCBASEUI = CBmpMgr::Get_Instance()->Find_Image(L"Base_UI");
	HDC HDCBASEUI2 = CBmpMgr::Get_Instance()->Find_Image(L"Base_UI2");
	HDC HDCBaseUI3 = CBmpMgr::Get_Instance()->Find_Image(L"Item");

	GdiTransparentBlt(hDC,
		50,
		10,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		HDCBASEUI,
		0,
		0,
		633,
		67,
		RGB(255, 255, 255));

	GdiTransparentBlt(hDC,
		WINCX / 2 + 200,
		20,
		356,
		67,
		HDCBASEUI2,
		0,
		0,
		356,
		67,
		RGB(255, 255, 255));

	if (static_cast<CPlayer*>(m_pTarget)->Get_Key() >= 1) {
		GdiTransparentBlt(hDC,
			70,
			70,
			64,
			64,
			HDCBaseUI3,
			8 * 128,
			1 * 128,
			128,
			128,
			RGB(255, 255, 255));
	}

	if (static_cast<CPlayer*>(m_pTarget)->Get_Key() == 2) {
		GdiTransparentBlt(hDC,
			140,
			70,
			64,
			64,
			HDCBaseUI3,
			8 * 128,
			1 * 128,
			128,
			128,
			RGB(255, 255, 255));
	}




	HFONT old = (HFONT)SelectObject(hDC, m_hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	int hp = static_cast<CPlayer*>(m_pTarget)->GetOwn().m_iHp;
	wchar_t buff_1[32];
	swprintf_s(buff_1, L"%d", hp);

	TextOut(hDC, 110, 40, buff_1, wcslen(buff_1));

	int bomb = static_cast<CPlayer*>(m_pTarget)->GetOwn().m_iBomb;
	wchar_t buff_2[32];
	swprintf_s(buff_2, L"%d", bomb);

	TextOut(hDC, 230, 40, buff_2, wcslen(buff_2));

	int Roap = static_cast<CPlayer*>(m_pTarget)->GetOwn().m_iRope;
	wchar_t buff3[32];
	swprintf_s(buff3, L"%d", Roap);

	TextOut(hDC, 360, 40, buff3, wcslen(buff3));

	int Money = static_cast<CPlayer*>(m_pTarget)->GetOwn().m_iMoney;
	wchar_t buff4[32];
	swprintf_s(buff4, L"%d", Money);

	TextOut(hDC, 900, 40, buff4, wcslen(buff4));

	{
		int time_s = (m_pScene)->GetTime();
		wchar_t buff5_1[10];
		swprintf_s(buff5_1, L"%d", time_s / 60000);

		TextOut(hDC, 1040, 40, buff5_1, wcslen(buff5_1));

		wchar_t buff5_2[10];
	
		swprintf_s(buff5_2, L"%d", time_s / 6000);

		TextOut(hDC, 1055, 40, buff5_2, wcslen(buff5_2));

		wchar_t buff5_3[10];
		swprintf_s(buff5_3, L":");

		TextOut(hDC, 1075, 40, buff5_3, wcslen(buff5_3));

		wchar_t buff5_4[10];
		int time_4;

		if (time_s / 100 >= 60){
			time_4 = 0;
		}
		else {
			time_4 = time_s / 1000;
		}
		swprintf_s(buff5_4, L"%d", time_4);
		
		TextOut(hDC, 1085, 40, buff5_4, wcslen(buff5_4));

		wchar_t buff5_5[10];
		swprintf_s(buff5_5, L"%d", (time_s / 100)%10);

		TextOut(hDC, 1100, 40, buff5_5, wcslen(buff5_5));
	}
	
	
	wchar_t buff6[32];
	swprintf_s(buff6, L"%s", m_stageName.c_str());

	TextOut(hDC, 1180, 40, buff6, wcslen(buff6));


	SelectObject(hDC, old);


}

void CPlayerUI::Release()
{
	DeleteObject(m_hFont);
}

