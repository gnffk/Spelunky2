#include "pch.h"
#include "Boss.h"
#include "Player.h"
#include "CBomb.h"
#include "BmpManager.h"
#include "CameraManager.h"
#include "ObjManager.h"
CBoss::CBoss() : m_pTarget(nullptr), m_bBroke(false)
{
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_eRender = GAMEOBJECT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss.bmp",L"Boss");
	m_tInfo = {1000, 1000,300,300};
	m_fRealSize = { 300,300 };
	m_eBossPattern = Pattern1;
	m_eBossState = IDLE;
	m_tGravity = 9.8f;
	m_dir = RIGHT;
	m_fSpeed = 0;
	m_vChangeMask = { 0,0 };
	m_iBombCount = 0;
}

int CBoss::Update(float deltatime)
{
	__super::Update_Rect();

	Check_Pattern(deltatime);
	return OBJ_NOEVENT;
}

void CBoss::Late_Update(float deltatime)
{
}

void CBoss::Render(HDC hDC)
{
	HDC BOSSDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss");

	if (m_eBossPattern == Pattern1 || ((m_eBossPattern == Pattern2)&&(m_eBossState== READYSTAGE))) {
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			BOSSDC,
			0,
			0,
			512,
			512,
			RGB(255, 255, 255));

		
	

			
	}
	else {


		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top + 50,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY / 2,
			BOSSDC,
			512,
			512,
			512,
			256,

			RGB(255, 255, 255));

		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top + 160,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY / 2,
			BOSSDC,
			512,
			768,
			512,
			256,

			RGB(255, 255, 255));
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top + 12 - m_vChangeMask.y,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY / 2,
			BOSSDC,
			0,
			512,
			512,
			256,
			RGB(255, 255, 255));

		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top + 110,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY / 2,
			BOSSDC,
			0,
			768,
			512,
			256,
			RGB(255, 255, 255));


		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top + 180 + m_vChangeMask.y,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY / 2,
			BOSSDC,
			0,
			1024,
			512,
			256,
			RGB(255, 255, 255));

		
	}
	



}

void CBoss::Release()
{
}

void CBoss::Check_Pattern(float deltatime) {
	switch (m_eBossPattern) {
	case Pattern1:
		Simple_Attack(deltatime);
		break;
	case Pattern2:
		ComPlexAttack(deltatime);
		break;
	}
}

void CBoss::Simple_Attack(float deltatime) {
	switch (m_eBossState) {
	case ATTACKDONE:
	{
		m_tInfo.fY += m_tGravity;
		int targety = m_tInfo.fY + m_tInfo.fCY / 2;
		if ((1520.f <= targety && 1680.f >= targety) ||
			(2560.f <= targety && 2800.f >= targety)) {
			m_eBossState = IDLE;
		}

		if (2800.f <= targety) {
			m_eBossPattern = Pattern2;
			m_eBossState = READYSTAGE;
		}
	}
		break;
	
	case IDLE: {
		m_tInfo.fY += m_tGravity;
		int x = (m_tInfo.fX - m_pTarget->Get_Info()->fX )* (m_tInfo.fX - m_pTarget->Get_Info()->fX);
		int y = (m_tInfo.fY - m_pTarget->Get_Info()->fY) * (m_tInfo.fY - m_pTarget->Get_Info()->fY);
		int distance = sqrt(x + y );

		if (m_StartAttackTime + 1000 < GetTickCount()) {
		
			
				if (distance <= 500.f) {
					m_eBossState = JUMP;
					m_fJumpTime = 0;
					m_fStartPosy = m_tInfo.fY;
					m_fStartPosx = m_tInfo.fX;
					m_fAngle = 90.f;
					m_fJumpSpeed = 80.f;
				}

			
		}
	}
		
		break;

	case JUMP:
		Jump(deltatime);
		break;

	case ATTACK:
		Attack();
		break;
	}
}

void CBoss::Jump(float deltatime) {
	m_fJumpTime += (deltatime * 0.2f);
	float v0_y = m_fJumpSpeed * sin(m_fAngle * PI / 180.f);


	float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;


	float v_y = v0_y - m_tGravity * m_fJumpTime;

	if (m_pTarget->Get_Info()->fX - m_tInfo.fX > 0) {
		m_dir = RIGHT;
	}
	else if (m_pTarget->Get_Info()->fX - m_tInfo.fX  <= 0) {
		m_dir = LEFT;
	}


	if (fabsf(m_pTarget->Get_Info()->fX - m_tInfo.fX) > 10.f) {
		m_tInfo.fX += deltatime*10 * m_dir;
	}
	else {
		m_tInfo.fX = m_pTarget->Get_Info()->fX;
	}
	

	m_tInfo.fY = m_fStartPosy - (_newPos_y);

	
	if (v_y < 0.f)
		m_eBossState = ATTACK;
		m_StartAttackTime = GetTickCount();
	
	
}

void CBoss::Attack() {

	if (m_StartAttackTime + 500 < GetTickCount()) {

		m_tInfo.fY += m_tGravity * 1.5f; 


		if (m_bBroke) {
			m_fJumpTime = 0.f;
			m_eBossState = ATTACKDONE;
			m_StartAttackTime = GetTickCount();
			m_bBroke = false;
			CCameraManager::Get_Instance()->Shake(10.f, 8.f);
		}
		
	}
	

	
}

void CBoss::ComPlexAttack(float deltatime) {
	switch (m_eBossState) {
	case READYSTAGE:
	{
		m_tInfo.fY += m_tGravity;
		int x = (m_tInfo.fX - m_pTarget->Get_Info()->fX) * (m_tInfo.fX - m_pTarget->Get_Info()->fX);
		int y = (m_tInfo.fY - m_pTarget->Get_Info()->fY) * (m_tInfo.fY - m_pTarget->Get_Info()->fY);
		int distance = sqrt(x + y);


		if ((3680.f <= m_tInfo.fY + m_tInfo.fCY/2)&& distance <=600) {
			m_eBossState = OPENMASK;
		}
	}
	break;
	case OPENMASK:
		if (m_tInfo.fY <= 3300.f) {
			m_vChangeMask.y += deltatime * 0.8f;

			if (m_vChangeMask.y >= 40.f) {
				m_eBossState = IDLE;
				m_fStartTime = GetTickCount();
			}
		}
		else {
			m_tInfo.fY -= deltatime * 1.f;
		}
		
		break;
		//IDLE로 돌아오기전 무조건 m_fStartTime 이거 초기화 했는지 확인
	case IDLE: {
	
		if (m_fStartTime + 2000 <= GetTickCount()) {
			m_eBossState = CHASE;
		}
		
	}
		break;

	case CHASE:
	{
		Chase_Target(deltatime);
	}
		break;
	case BOMB: {
		if (m_tInfo.fY <= 3300.f) {
			Bomb_Attack(deltatime);
		}
		else {
			m_tInfo.fY -= deltatime * 10.f;
		}
	}
		break;
			
	}
}

void CBoss::Chase_Target(float deltatime) {

	float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);
	m_fSpeed += deltatime * 0.3f;

	if (m_fSpeed >= 13) {
		m_fSpeed = 13;
	}
	if (m_pTarget)
	{

		fWidth = m_pTarget->Get_Info()->fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info()->fY - m_tInfo.fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		if (m_pTarget->Get_Info()->fY > m_tInfo.fY)
			fRadian = 2.f * PI - fRadian;
	}

	m_tInfo.fX += cosf(fRadian) * m_fSpeed;
	m_tInfo.fY -= sinf(fRadian) * m_fSpeed;

	if (m_pTarget) {
		int x = (m_tInfo.fX - m_pTarget->Get_Info()->fX) * (m_tInfo.fX - m_pTarget->Get_Info()->fX);
		int y = (m_tInfo.fY - m_pTarget->Get_Info()->fY) * (m_tInfo.fY - m_pTarget->Get_Info()->fY);
		int distance = sqrt(x + y);


		if (distance <= 200) {
			m_eBossState = BOMB;
			m_fSpeed = 0;
		}
	}
	


	

}

void CBoss::Bomb_Attack(float deltatime)
{
	if (!m_iBombCount) {
		for (int i = 0; i < 10; ++i) {
			float randOffset = (rand() % 100) - 50;
			if (i % 2 == 0) {
				CObjManager::Get_Instance()->AddObject(OBJ_ITEM, Create_Bomb(DIR_LEFT, 1, 90, randOffset, randOffset));
			}
			else {
				CObjManager::Get_Instance()->AddObject(OBJ_ITEM, Create_Bomb(DIR_RIGHT, 1, 90, randOffset, randOffset));
			}
			m_iBombCount++;
		}
	}

	if (m_iBombCount >= 10) {
		m_eBossState = IDLE;
		m_iBombCount = 0;
		m_fStartTime = GetTickCount();
	}
	
	
}

CObj* CBoss::Create_Bomb(DIRECTION eDir, float m_fSpeed, float m_fAngle, float m_fJumpSpeed, float m_fRand)
{
	CObj* pBomb = new CBomb;
	pBomb->Initialize();
	pBomb->Set_Direction(eDir);
	static_cast<CBomb*>(pBomb)->SetJump_Info(m_fSpeed, m_fAngle, m_fJumpSpeed);
	pBomb->Set_Pos(m_tInfo.fX, m_tInfo.fY + m_fRand);


	return pBomb;
}