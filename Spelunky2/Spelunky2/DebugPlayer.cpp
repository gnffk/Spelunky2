#include "pch.h"
#include "DebugPlayer.h"
#include "KeyManager.h"

CDebugPlayer::CDebugPlayer()
{
	
}

CDebugPlayer::~CDebugPlayer()
{
	Release();
}

void CDebugPlayer::Initialize()
{
	m_eRender = TILE;
	m_tInfo = { 500, 500, 50, 50 };
	m_fSpeed = 10.f;
}

int CDebugPlayer::Update(float deltatime)
{


	__super::Update_Rect();
	Key_Input();
	
	return 0;
}

void CDebugPlayer::Late_Update(float deltatime)
{

}

void CDebugPlayer::Render(HDC hDC)
{

	
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CDebugPlayer::Release()
{
}

void CDebugPlayer::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Pressing('w') || CKeyManager::Get_Instance()->Key_Pressing('W')) {
		m_tInfo.fY -= m_fSpeed;
	}
	if (CKeyManager::Get_Instance()->Key_Pressing('a') || CKeyManager::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.fX -= m_fSpeed;
	}
	if (CKeyManager::Get_Instance()->Key_Pressing('s') || CKeyManager::Get_Instance()->Key_Pressing('S')) {
		m_tInfo.fY += m_fSpeed;
	}
	if (CKeyManager::Get_Instance()->Key_Pressing('d') || CKeyManager::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.fX += m_fSpeed;
	}
}
