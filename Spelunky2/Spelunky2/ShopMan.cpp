#include "pch.h"
#include "ShopMan.h"
#include "BmpManager.h"
#include "StoreUI.h"
#include "UIManager.h"
#include "ShotGun.h"
#include "ObjManager.h"
#include "AbstractFactory.h"
#include "OpenKey.h"

CShopMan::CShopMan()
{
}

CShopMan::~CShopMan()
{
}

void CShopMan::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_EnemyType = ENEMY_SHOPMAN;
	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;
	m_invincibility = false;
	m_fRealSize = { 40.f,  70.f };
	m_fStopCollision = 0.f;
	m_curState = IDLE;
	m_eDir = DIR_LEFT;
	m_fSpeed = 3.f;

	m_tGravity = 9.8f;

	m_Own.m_iHp = 5;
	m_dir = -1;
	m_fStopCollision = 0.f;
	m_fAngle = 90.f;

	m_bkind = true;
	m_pStoreUI = nullptr;
	m_bStore = true;
	m_Weapon = nullptr;

	m_fJumpTime = 0.f;

	m_fJumpSpeed = 30.f;
	m_fStartPosx = m_tInfo.fX;
	m_fStartPosy = m_tInfo.fY;
}

int CShopMan::Update(float deltatime)
{
	if (m_Own.m_iHp == 0) {
		CObjManager::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<COpenKey>::Create(m_tInfo.fX, m_tInfo.fY, true));
		m_Own.m_iHp = -1;
		//return OBJ_DEAD;
	}	
	__super::Update_Rect();

	Move_Dir();
	Motion_Change();
	Environment_Change(deltatime);


	if (m_bkind&& m_bStore && m_pStoreUI == nullptr) {
		m_pStoreUI = new CStoreUI;
		m_pStoreUI->Initialize();
		CUIManager::Get_Instance()->Add_UI(m_pStoreUI);
		dynamic_cast<CStoreUI*>(m_pStoreUI)->Set_Target(this);
	}

	return OBJ_NOEVENT;
}

void CShopMan::Late_Update(float deltatime)
{
}

void CShopMan::Render(HDC hDC)
{
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

void CShopMan::Release()
{
}

void CShopMan::Motion_Change() {
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
				m_tFrame.iBegin = 9;
				m_tFrame.iStart = 9;
				m_tFrame.iEnd = 9;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}
		}
		break;
		case HIT:
		{
			if (m_eDir == DIR_RIGHT) {
		
				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 1;
				m_tFrame.iStart = 1;
				m_tFrame.iEnd = 4;
				m_tFrame.iMotion = 1;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}

			if (m_eDir == DIR_LEFT) {

				m_tFrame.bLoop = false;
				m_tFrame.iBegin = 8;
				m_tFrame.iStart = 8;
				m_tFrame.iEnd = 5;
				m_tFrame.iMotion = 1;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}


			m_fJumpTime = 0.f;
			m_fStartPosx = m_tInfo.fX;
			m_fStartPosy = m_tInfo.fY;
			m_fJumpSpeed = 30.f;

		}
		break;
		case CHASE:
		{
			m_Weapon = new CShotGun;
			m_Weapon->Initialize();
			m_Weapon->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			m_Weapon->Set_Direction(m_eDir);
			CObjManager::Get_Instance()->AddObject(OBJ_WEAPON, m_Weapon);
			m_curState = RUN;
			m_fStartPosy = m_tInfo.fY;
		}
		break;

		case RUN:
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
				m_tFrame.iBegin = 9;
				m_tFrame.iStart = 9;
				m_tFrame.iEnd = 9;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		case ANSWER:
		{
			static_cast<CStoreUI*>(m_pStoreUI)->Set_Change(1);
			
		}
			break;

		}
		m_prevState = m_curState;
		m_eprevDir = m_eDir;
	}

}


void CShopMan::Environment_Change(float deltatime) {
	switch (m_curState)
	{
	case HITIDLE:
	{
		m_tInfo.fY += m_tGravity;
	}
		break;
	case IDLE:
	{
		m_tInfo.fY += m_tGravity;
	}
	break;
	case HIT:
	{
		RemoteHit(deltatime);
	}
	break;
	case ANSWER:
	{
		if (m_Time + 2000 < GetTickCount()) {
			m_curState = CHASE;
			static_cast<CStoreUI*>(m_pStoreUI)->Set_Change(2);
			m_bStore = false;
			ShotTime = GetTickCount();
			m_Time = GetTickCount();
		}
	}
		break;

	case RUN:
		m_tInfo.fX += 30.f * m_dir * 0.5f ;
		if (ShotTime + 1000 < GetTickCount()) {
			m_fJumpTime = 0.f;
			m_fStartPosy = m_tInfo.fY;
			m_fJumpSpeed = 50.f;
			m_dir *= -1;
			ShotTime = GetTickCount();
			m_curState = JUMP;
		}

		break;

	case JUMP:
		RemoteJump(deltatime);
		break;
	}
	if (m_curState == JUMP || m_curState == RUN) {
		if (m_Weapon) {
			if (m_Time + 2000 < GetTickCount()) {
				static_cast<CShotGun*>(m_Weapon)->Shot();
				m_Time = GetTickCount();
			}
		}
	}

	

}

void CShopMan::Move_Dir() {
	if (m_dir == 1) {
		m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Man_Right");
		if (m_Weapon) {
			m_Weapon->Set_Pos(m_tInfo.fX + 40, m_tInfo.fY);
			m_Weapon->Set_Direction(DIR_RIGHT);

		}
		Move_Frame_Right();
	}

	else if (m_dir == -1) {

		m_MonsterHDC = CBmpMgr::Get_Instance()->Find_Image(L"Man_Left");
		if (m_Weapon) {
			
			m_Weapon->Set_Pos(m_tInfo.fX - 40, m_tInfo.fY);
			m_Weapon->Set_Direction(DIR_LEFT);
		}
		Move_Frame_Left();
	}
	

}

void CShopMan::RemoteHit(float deltatime)
{
	// deletatime ->  한 프레임당 시간 값
	// m_fJumpTime -> 포물선의 공식이 진행되는 시간 

	m_fJumpTime += (deltatime * 0.2f);
	float v0_y = m_fJumpSpeed * sin(m_fAngle * PI / 180.f);

	// 여기까지가 포물선 공식
	float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;

	// 이건 찾아보니까 그 포물선 공식의 최고점 // 점프 최대 크기가 되었을 떄 조건 
	float v_y = v0_y - m_tGravity * m_fJumpTime;

	// 3880.f.f.f 점프키 누른 당시의 y값 // 점프 초기 값
	m_tInfo.fX += v0_y* m_dir * 0.2f;
  	m_tInfo.fY = m_fStartPosy - _newPos_y;


	// 이게 점프가 완료되었을때 상태 
	if (m_tInfo.fY >= m_fStartPosy)
	{
		m_invincibility = false;
		m_fJumpTime = 0.f;
		m_curState = HITIDLE;
		m_fJumpSpeed = 0.f;
	}
}



void CShopMan::RemoteJump(float deltatime) {
	// deletatime ->  한 프레임당 시간 값
	// m_fJumpTime -> 포물선의 공식이 진행되는 시간 

	m_fJumpTime += (deltatime * 0.2f);
	float v0_y = m_fJumpSpeed * sin(m_fAngle * PI / 180.f);

	// 여기까지가 포물선 공식
	float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;

	// 이건 찾아보니까 그 포물선 공식의 최고점 // 점프 최대 크기가 되었을 떄 조건 
	float v_y = v0_y - m_tGravity * m_fJumpTime;

	// 3880.f.f.f 점프키 누른 당시의 y값 // 점프 초기 값
	m_tInfo.fX += v0_y * m_dir * 0.2f;
	m_tInfo.fY = m_fStartPosy - _newPos_y;

	if (m_tInfo.fY >= m_fStartPosy)
	{
		m_curState = RUN;

	}
	

}