#include "pch.h"
#include "Snake.h"
#include "BmpManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
CSnake::CSnake() : m_pTarget(nullptr)
{
}
CSnake::~CSnake()
{
}
void CSnake::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_EnemyType = ENEMY_SNAKE;

	m_tInfo = { 100, 100,80,80 };
	m_fRealSize = { 40.f, 40.f };


	
	m_curState = IDLE;
	m_eDir = DIR_RIGHT;
	m_fSpeed = 3.f;
	m_fTime = GetTickCount();
}

int CSnake::Update(float deltatime)
{
	if (m_bDead) {
		for (int i = 0; i < 4; ++i) {
			CEffectManager::Get_Instance()->Paricle_Effect({ m_tInfo.fX, m_tInfo.fY }, 2);
			CEffectManager::Get_Instance()->ADD_Effect({ m_tInfo.fX ,m_tInfo.fY }, 1);
		}
		CSoundManager::Get_Instance()->PlaySound(L"snake_die01.wav", SOUND_EFFECT, 1.f);

		return OBJ_DEAD;
	}
	__super::Update_Rect();

	Move_Dir();
	Motion_Change();
	Environment_Change(deltatime);
	return OBJ_NOEVENT;
}

void CSnake::Late_Update(float deltatime)
{
}

void CSnake::Render(HDC hDC)
{

	//Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_MonsterHDC,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));


}

void CSnake::Release()
{
}



void CSnake::Motion_Change() {
	if (m_curState != m_prevState || m_eDir != m_eprevDir) {
		switch (m_curState)
		{
		case IDLE:
		{
			if (m_eDir == DIR_RIGHT) {
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 0;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}
			if (m_eDir == DIR_LEFT) {
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 5;
				m_tFrame.iStart = 5;
				m_tFrame.iEnd = 5;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}
			
		}
		break;
		case MOVE:
		{
			if (m_eDir == DIR_RIGHT) {
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 0;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 5;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

			if (m_eDir == DIR_LEFT) {
		
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 5;
				m_tFrame.iStart = 5;
				m_tFrame.iEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

		}
		break;

		case ATTACK:
		{
			if (m_eDir == DIR_RIGHT) {
		
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 0;
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 5;
				m_tFrame.iMotion = 1;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

			if (m_eDir == DIR_LEFT) {
			
				m_tFrame.bLoop = true;
				m_tFrame.iBegin = 5;
				m_tFrame.iStart = 5;
				m_tFrame.iEnd = 0;
				m_tFrame.iMotion = 1;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}

		}
		break;

		case CHANGE:
		{
			if (m_eDir == DIR_RIGHT) {
				m_eDir = DIR_LEFT;
			}

			else if (m_eDir == DIR_LEFT) {
				m_eDir = DIR_RIGHT;
			}
			m_fSpeed *= -1;
		}
		break;

		}
		m_prevState = m_curState;
		m_eprevDir = m_eDir;
	}

}


void CSnake::Environment_Change(float deltatime) {
	switch (m_curState)
	{
	case IDLE:
	{
		if (m_fTime + 1000 < GetTickCount()) {
			m_curState = MOVE;
			m_fTime = GetTickCount();
		}
		
	}
	break;
	case MOVE:
	{
		m_tInfo.fX += m_fSpeed;
	}
	break;

	case ATTACK:
	{

	}
	break;
	case CHANGE:
	{
		m_fTime = GetTickCount();
		m_curState = IDLE;
	}
	break;
	}
}

void CSnake::Move_Dir() {
	if (m_eDir == DIR_RIGHT) {
		m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Snake_Right");
		Move_Frame_Right();
	}

	else if (m_eDir == DIR_LEFT) {
		m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Snake_Left");
		Move_Frame_Left();
	}


}

