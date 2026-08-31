#include "pch.h"

#include "CBomb.h"
#include "BmpManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "TileManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
CBomb::CBomb() : m_bTrigger(false)
{
}

CBomb::~CBomb()
{
}

void CBomb::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_BombDC = CBmpMgr::Get_Instance()->Find_Image(L"Item");

	m_tInfo = { 0,0,70,70 };
	m_fRealSize = { 35, 35 };
	m_invincibility = 0;
	m_fBombSize = { 35,35 };

	m_pFrameKey = L"Item";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iMotion = 5;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.bLoop = true;


	m_bCollision = false;
	m_fSpeed = 0;
	m_fJumpSpeed = 50.f;
	m_fJumpTime = 0.f;
	m_fAngle = 90.f;
	m_tGravity = 9.8f;
	m_bombState = JUMP;

	m_eItemType = ITEM_BOBM;
	m_bTrigger = true;

	m_eCollisionType = C_BOMB;
	m_bBobmbing = false;
}

int CBomb::Update(float deltatime)
{
	Vec2 cameraPos = CCameraManager::Get_Instance()->GetDistance();

	m_BOMBRECT.left = LONG(m_tInfo.fX - (m_fBombSize.x / 2.f)) - cameraPos.x;
	m_BOMBRECT.top = LONG(m_tInfo.fY - (m_fBombSize.y / 2.f)) - cameraPos.y;
	m_BOMBRECT.right = LONG(m_tInfo.fX + (m_fBombSize.x / 2.f)) - cameraPos.x;
	m_BOMBRECT.bottom = LONG(m_tInfo.fY + (m_fBombSize.y / 2.f)) - cameraPos.y;


	__super::Update_Rect();
	State_Gravity(deltatime);
	if (m_bTrigger) {
		Move_Frame();
		m_tFrame.dwSpeed -= deltatime;

		if (m_tFrame.dwSpeed < 1.f) {
			CCameraManager::Get_Instance()->Shake(5.f, 10.f);
			m_fBombSize.x *= 8;
			m_fBombSize.y *= 8;

			CCollisionManager::Collision_RectEx_Bomb(this, CTileManager::Get_Instance()->GetTile());
			if (m_fBombSize.x >= 280) {
				CEffectManager::Get_Instance()->ADD_Effect({ m_tInfo.fX ,m_tInfo.fY }, 2);
				CSoundManager::Get_Instance()->PlaySound(L"shotgun_fire01.wav", SOUND_EFFECT, 0.5f);
		
				return OBJ_DEAD;
			}
		
		}
	}
	


	return OBJ_NOEVENT;
}

void CBomb::Late_Update(float deltatime)
{
}

void CBomb::Render(HDC hDC)
{
	//Ellipse(hDC, m_BOMBRECT.left, m_BOMBRECT.top, m_BOMBRECT.right, m_BOMBRECT.bottom);
	

	
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_BombDC,
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,
		128,
		RGB(255, 255, 255));


}

void CBomb::Release()
{
}

void CBomb::State_Gravity(float deltatime) {
	// 조건이 바뀔때만
	if (m_prebombState != m_bombState) {
		switch (m_bombState) {
		case JUMPFALLING:

			break;
		case JUMP:
			m_fJumpTime = 0.f;
			m_fStartPosx = m_tInfo.fX ;
			m_fStartPosy = m_tInfo.fY ;
		
			break;

		case FALLING:
			
			break;


		case BOMB:
		/*	m_BombDC = CBmpMgr::Get_Instance()->Find_Image(L"Bomb");
			m_tFrame.iStart = 0;
			m_tFrame.iBegin = 0;
			m_tFrame.iEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bLoop = false;*/
			break;

		}

		m_prebombState = m_bombState;
	}
	// 상시 업데이트
	switch (m_bombState) {
	case JUMP: {
	
		Jump(deltatime);
	}
		
		break;
		 
	case JUMPFALLING:
	{
		Jump(deltatime);
	}
		break;
	case FALLING: {
		m_tInfo.fX += m_fJumpSpeed* 0.2f * m_fAcceleration;
		m_tInfo.fY += m_tGravity * deltatime;
	}
		break;
	case BOMB:
		if (m_tFrame.iStart == m_tFrame.iEnd) {
			m_bBobmbing = true;
		}
		break;

	}

	if (m_bCollision == true) {
		m_fJumpSpeed *= 0.8f;
		m_bombState = JUMP;
		m_bCollision = false;
		if (m_eDir == DIR_LEFT) {
			m_fAcceleration = -1;
		}
		else if (m_eDir == DIR_RIGHT) {
			m_fAcceleration = 1;
		}

		if (m_fJumpSpeed < 1) {
			m_fJumpSpeed = 0;
			m_bombState = BOMB;
		}
	}
}

void CBomb::Jump(float deltatime)
{
	if (deltatime < 0) {
		return;
	}


	m_fJumpTime += (deltatime * 0.2f);
	float v0_y = m_fJumpSpeed * sin(m_fAngle * PI / 180.f);

	float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;

	
	float v_y = v0_y - m_tGravity * m_fJumpTime;

	m_tInfo.fX += v0_y* 0.2f * m_fAcceleration;
	m_tInfo.fY = m_fStartPosy - _newPos_y;

	if (m_fJumpSpeed < 1.f) {
		m_fJumpSpeed = 0.f;
	}

	if (v_y < 0.f)
		m_bombState = JUMPFALLING;
		
	// 이게 점프가 완료되었을때 상태 
	if ( m_tInfo.fY >= m_fStartPosy  )
	{
		m_fStartPosy = m_tInfo.fY;
		m_fJumpTime = 0.f;
		m_bombState = FALLING;

	}
}


void CBomb::SetJump_Info(float speed, float angle, float jumpSpeed)
{
	m_fAcceleration = speed;
	if (m_eDir == DIR_LEFT) {
		m_fAcceleration *= -1;
	}
	if (m_eDir == DIR_RIGHT) {
		m_fAcceleration *= 1;
	}
	m_fAngle = angle;
	m_fJumpSpeed = jumpSpeed;
}

