#include "pch.h"
#include "UI.h"

#include "CameraManager.h"
CUI::CUI() : m_bRemain(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CUI::~CUI()
{
}

void CUI::Update_Rect()
{

	//CCameraManager::Get_Instance()->GetCameraPos();
	//m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	//m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	//m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	//m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
	/*Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();

	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f)) - cameraPos.x;
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f)) - cameraPos.y;
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f)) - cameraPos.x;
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f)) - cameraPos.y;*/



}
