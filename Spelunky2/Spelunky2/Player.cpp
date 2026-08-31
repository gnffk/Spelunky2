#include "pch.h"

#include "Player.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "ObjManager.h"
#include "CollisionManager.h"
#include "CBomb.h"
#include "Tether.h"
#include "Whip.h"

#include "ShotGun.h"
#include "SoundManager.h"
// 메멘토 패턴 
// 플레이어 크기 80.f X 80.f
CPlayer::CPlayer() : m_ePreState(ST_END), m_eCurState(IDLE), m_bSpecialPlaying(false),
m_fJumpTime(0), m_fJumpSpeed(45.f), m_eSpecialState(ST_END), m_ePrevSpecialState(ST_END), m_bHurt(false),
m_fHurtBumpingSpeed(0), m_fHurtBumpingAngle(0), m_fStartPosy(0), m_WallCollision(false), m_bHand(false),m_bNext(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_eRender = GAMEOBJECT;
	m_tInfo = { 280.f, 370.f, 80.f, 80.f };
	m_iKey = 0;
	m_fRealSize = { 30.f,  70.f };
	m_bShotgunRecoil = false;

	m_fSpeed = 10.f;
	m_fDistance = 100.f;
	m_eDir = DIR_RIGHT;
	m_fAngle = 90.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/player/right_character.bmp", L"Right_Player");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/player/left_character.bmp", L"Left_Player");

	m_bCollision = false;
	m_pFrameKey = L"Right_Player";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();



	
	m_eCurState = IDLE;

	m_fJumpSpeed = 0;
	m_Own = {
	10,0,0,99999
	};
	m_Hand = nullptr;

	m_Weapon = new CWhip;
	CObjManager::Get_Instance()->AddObject(OBJ_WEAPON, m_Weapon);
	static_cast<CWhip*>(m_Weapon)->Set_Target(this);
	m_Weapon->Initialize();
	m_Weapon->Set_Remain(true);
}

int CPlayer::Update(float deltatime)
{

	static_cast<CWhip*>(m_Weapon)->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	if (m_Hand) {
		if (m_Hand->Get_ItemType() == ITEM_SHOTGUN) {
			if (m_eDir == DIR_RIGHT) {
				m_Hand->Set_Pos(m_tInfo.fX + 20, m_tInfo.fY + 20);
			}
			else {
				m_Hand->Set_Pos(m_tInfo.fX - 20, m_tInfo.fY + 20);
			}
		}
		m_Hand->Set_Direction(m_eDir);

	}

	__super::Update_Rect();

	Key_Input();

	//Jump();
	
	Motion_Change();
	Player_Move();
	Environment_Change(deltatime);
	


	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(float deltatime)
{

}

void CPlayer::Render(HDC hDC)
{

	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top , m_CollisionRect.right, m_CollisionRect.bottom );
	
	                                                                            
 
	GdiTransparentBlt(hDC,			
		m_tRect.left ,
		m_tRect.top,
		(int)m_tInfo.fCX,			
		(int)m_tInfo.fCY,			
		hMemDC,				
		m_tFrame.iStart * 128,
		m_tFrame.iMotion * 128,
		128,		
		128,
		RGB(255, 255, 255));	

	if (m_bHurt)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top - 20,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_FHurtFrame.iStart * 128,
			m_FHurtFrame.iMotion * 128,
			128,
			128,
			RGB(255, 255, 255));
	}
}

void CPlayer::Release()
{

	m_Weapon->Set_Remain(false);
	m_Weapon = nullptr;
}

void CPlayer::Key_Input()
{
	if (!m_bDead) {
		if (!m_bHurt) {
#pragma region 일반 키 움직임
			if (m_eCurState != JUMP && m_eCurState != FALLING && m_eCurState != IDLE_FALLING && m_eSpecialState != LADDERMOVE && m_eSpecialState != LADDERIDLE) {

				if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT) && m_eCurState != LOOKUP)
				{
					if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN)) {
						m_tInfo.fX += m_fSpeed / 2;
						m_eCurState = DOWNWALK;
					}
					else if (CKeyManager::Get_Instance()->Key_Up(VK_DOWN)) {
						m_eCurState = LOOKDOWN_BACK;
					}
					else {
						if (!m_bFloor) {
							m_tInfo.fX += m_fSpeed;

							m_eCurState = WALK;
						}

					}
				}
				else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT) && m_eCurState != LOOKUP)
				{

					if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN)) {
						m_tInfo.fX -= m_fSpeed / 2;
						m_eCurState = DOWNWALK;
					}
					else if (CKeyManager::Get_Instance()->Key_Up(VK_DOWN)) {
						m_eCurState = LOOKDOWN_BACK;
					}
					else {
						if (!m_bFloor) {
							m_tInfo.fX -= m_fSpeed;

							m_eCurState = WALK;
						}
					}


				}
				else if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP) && m_eCurState != LOOKDOWN_BACK)
				{
					if (!m_bLadder) {
						m_eCurState = LOOKUP;
					}
					else {
						m_eSpecialState = LADDERMOVE;
						m_bSpecialPlaying = true;
						
					}
					
				}
				else if (CKeyManager::Get_Instance()->Key_Up(VK_UP)) {
					if (!m_bLadder) {
						m_eCurState = LOOKUP_BACK;
					}
					else {
						m_eSpecialState = LADDERIDLE;
						m_bSpecialPlaying = true;
					}

				}
				else if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN) && m_eCurState != LOOKUP_BACK && m_eCurState != DOWNIDLE)
				{
					if (m_eCurState != DOWNWALK) {
						m_eCurState = LOOKDOWN;
					}
					else {
						m_eCurState = DOWNIDLE;
					}

				}
				else if (CKeyManager::Get_Instance()->Key_Up(VK_DOWN)) {
					m_eCurState = LOOKDOWN_BACK;

				}
				else if ((m_eCurState != LOOKUP_BACK) && (m_eCurState != LOOKDOWN_BACK) && m_eCurState != DOWNIDLE) {
					m_eCurState = IDLE;
				}



			}
			if( m_eSpecialState != LADDERMOVE && m_eSpecialState != LADDERIDLE) {
				if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP) )
				{
					if (m_bLadder) {
						m_eSpecialState = LADDERMOVE;
						m_bSpecialPlaying = true;
					}
				}
				else if (CKeyManager::Get_Instance()->Key_Up(VK_UP)) {
					if (m_bLadder) {
						m_eSpecialState = LADDERIDLE;
						m_bSpecialPlaying = true;
					}
				}
			}
#pragma endregion

#pragma region IDLE로 돌아가기
			if (m_eCurState == JUMP || m_eCurState == FALLING || m_eCurState == IDLE_FALLING) {
				if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT) && m_eCurState != LOOKUP && m_eSpecialState != LADDERMOVE && m_eSpecialState != LADDERIDLE)
				{
					m_pFrameKey = L"Right_Player";
					m_eDir = DIR_RIGHT;
					m_tInfo.fX += m_fSpeed;
				}
				else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT) && m_eCurState != LOOKUP && m_eSpecialState != LADDERMOVE && m_eSpecialState != LADDERIDLE)
				{
					m_pFrameKey = L"Left_Player";
					m_eDir = DIR_LEFT;
					m_tInfo.fX -= m_fSpeed;

				}
			}

#pragma endregion

#pragma region 점프
			if (CKeyManager::Get_Instance()->Key_Down('z') || CKeyManager::Get_Instance()->Key_Down('Z')) {
				m_eCurState = JUMP;
				m_fStartPosy = m_tInfo.fY;
				m_fJumpSpeed = 45.f;
				m_fJumpTime = 0.f;

				if (m_eSpecialState == LADDERMOVE || m_eSpecialState == LADDERIDLE) {
					m_eSpecialState = ST_END;
					m_eCurState = JUMP;
				}
			}
#pragma endregion
#pragma region 밧줄 올리기
			if (CKeyManager::Get_Instance()->Key_Up('S')) {
				if (m_Own.m_iRope > 0) {
					CObjManager::Get_Instance()->AddObject(OBJ_ITEM, Create_Tether(0.f, 0.f, 0.f));
					m_Own.m_iRope -= 1;
				}
				

			} // 이거 안됨
#pragma endregion
#pragma region 공격
			if ( CKeyManager::Get_Instance()->Key_Down('X')) {
				if (m_Hand == nullptr) {
					static_cast<CWhip*>(m_Weapon)->Set_State(CWhip::ATTACKREADY);
					
				}
				else {
					if (m_Hand->Get_ItemType() == ITEM_SHOTGUN) {
						static_cast<CShotGun*>(m_Hand)->Shot();
						m_bShotgunRecoil = true;
						m_fShotgunRecoilSpeed = 20.f;   
						m_dwShotgunRecoilTime = GetTickCount();
						
					}
				}
				m_eSpecialState = ATTACK;
				m_bSpecialPlaying = true;
			}
#pragma endregion
#pragma region 줍기
			if (CKeyManager::Get_Instance()->Key_Down('A')) {
				if (m_Hand == nullptr) {
					CCollisionManager::Collision_RectEx_Player_Item_Hand(this, CObjManager::Get_Instance()->Get_TypeObj(OBJ_ITEM), m_Hand);
				
				}
				else {
					m_Hand = nullptr;
				}
				
			}
#pragma endregion

#pragma region 퀘스트 수락
			if (CKeyManager::Get_Instance()->Key_Down('D')) {
				CCollisionManager::Collision_RectEx_Player_Item_Hand(this, CObjManager::Get_Instance()->Get_TypeObj(OBJ_MONSTER), m_Hand);

			}
#pragma endregion


#pragma region 폭탄 
			if (CKeyManager::Get_Instance()->Key_Down('C')) {

				if (m_Own.m_iBomb > 0) {
					if (m_eCurState == LOOKDOWN) {

						CObjManager::Get_Instance()->AddObject(OBJ_ITEM, Create_Bomb(m_eDir, 1.f, 0.f, 50.f));
					}
					else {
						m_eSpecialState = ATTACK;
						m_bSpecialPlaying = true;
						CObjManager::Get_Instance()->AddObject(OBJ_ITEM, Create_Bomb(m_eDir, 1.f, 90.f, 50.f));
					}
					m_Own.m_iBomb -= 1;
				}
			

			}
#pragma endregion
#pragma region 사다리 타기
			if (m_eSpecialState != ATTACK) {
				if (m_bLadder) {
					if (m_eSpecialState == LADDERMOVE) {
						if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT) && m_eCurState != LOOKUP)
						{
							if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN)) {
							
								m_tInfo.fY += m_fSpeed / 2;
							}
							else if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP)) {
							
								m_tInfo.fY -= m_fSpeed / 2;
							}
						

						}
						else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT) && m_eCurState != LOOKUP)
						{

							if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN)) {
							
								m_tInfo.fY += m_fSpeed / 2;
							}

							else if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP)) {
							
								m_tInfo.fY -= m_fSpeed / 2;
							}
						

						}
						else if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP) && m_eCurState != LOOKUP) {
							m_tInfo.fY -= m_fSpeed / 2;
						}
						else if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN) && m_eCurState != LOOKUP) {
							m_tInfo.fY += m_fSpeed / 2;
						}
						else {
							m_eSpecialState = LADDERIDLE;
						}
					}
					else if (m_eSpecialState == LADDERIDLE) {
						if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT) || CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT) ||
							CKeyManager::Get_Instance()->Key_Pressing(VK_UP) || CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN))
						{
							m_eSpecialState = LADDERMOVE;

						}

					}
				}
				else {
					m_eSpecialState = ST_END;
					m_bSpecialPlaying = false;
				}
			}
#pragma endregion
#pragma region 왼쪽 오른쪽 방향
			if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
			{
				m_pFrameKey = L"Right_Player";
				m_eDir = DIR_RIGHT;

			}
			else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
			{
				m_pFrameKey = L"Left_Player";
				m_eDir = DIR_LEFT;

			}
#pragma endregion


		}
	}
	

	


}

void CPlayer::Motion_Change()
{
	
	if (!m_bDead) {
		if (!m_bHurt) {
			if (!m_bSpecialPlaying && (m_ePreState != m_eCurState || m_PreDirection != m_eDir))
			{
				switch (m_eCurState)
				{
				case DISAPPEARED:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 5;
						m_tFrame.iMotion = 5;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 10;
						m_tFrame.iMotion = 5;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
				}
					break;
				case IDLE: {
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 0;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 15;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}
						 break;

				case WALK: {
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 1;
						m_tFrame.iStart = 1;
						m_tFrame.iEnd = 7;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 7;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}

						 break;
				case DOWNWALK: {
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 5;
						m_tFrame.iStart = 5;
						m_tFrame.iEnd = 11;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 10;
						m_tFrame.iStart = 10;
						m_tFrame.iEnd = 6;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
				}

							 break;
				case JUMP:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 4;
						m_tFrame.iMotion = 9;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 11;
						m_tFrame.iMotion = 9;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
				}

				break;
				case FALLING:
				case IDLE_FALLING:
				{
					
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 4;
						m_tFrame.iStart = 4;
						m_tFrame.iEnd = 7;
						m_tFrame.iMotion = 9;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 11;
						m_tFrame.iStart = 11;
						m_tFrame.iEnd = 8;
						m_tFrame.iMotion = 9;
						m_tFrame.dwSpeed = 100;
						m_tFrame.dwTime = GetTickCount();
					}
				}
				break;
				case LOOKUP:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 3;
						m_tFrame.iMotion = 8;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 12;
						m_tFrame.iMotion = 8;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}
				break;

				case LOOKUP_BACK:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 4;
						m_tFrame.iStart = 4;
						m_tFrame.iEnd = 6;
						m_tFrame.iMotion = 8;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 12;
						m_tFrame.iStart = 12;
						m_tFrame.iEnd = 9;
						m_tFrame.iMotion = 8;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}
				break;
				case LOOKDOWN:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 2;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 13;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}
				break;

				case LOOKDOWN_BACK:
				{
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 2;
						m_tFrame.iStart = 2;
						m_tFrame.iEnd = 4;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 13;
						m_tFrame.iStart = 13;
						m_tFrame.iEnd = 11;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}

				break;
				case DOWNIDLE: {
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 2;
						m_tFrame.iStart = 2;
						m_tFrame.iEnd = 2;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 13;
						m_tFrame.iStart = 13;
						m_tFrame.iEnd = 13;
						m_tFrame.iMotion = 1;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
				}
							 break;

							 break;
				}

				m_ePreState = m_eCurState;
				m_PreDirection = m_eDir;
			}

			if (m_eSpecialState != m_ePrevSpecialState || m_PreDirection != m_eDir) {
				switch (m_eSpecialState) {
				case ATTACK:
					if (m_Hand == nullptr) {
						if (m_eDir == DIR_RIGHT) {
							m_tFrame.bLoop = false;
							m_tFrame.iBegin = 0;
							m_tFrame.iStart = 0;
							m_tFrame.iEnd = 5;
							m_tFrame.iMotion = 4;
							m_tFrame.dwSpeed = 65;
							m_tFrame.dwTime = GetTickCount();
						}

						if (m_eDir == DIR_LEFT) {
							m_tFrame.bLoop = false;
							m_tFrame.iBegin = 15;
							m_tFrame.iStart = 15;
							m_tFrame.iEnd = 10;
							m_tFrame.iMotion = 4;
							m_tFrame.dwSpeed = 50;
							m_tFrame.dwTime = GetTickCount();
						}

					}
					else {

					}
					break;

				case LADDERIDLE:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 0;
						m_tFrame.iMotion = 7;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 15;
						m_tFrame.iMotion = 7;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

						
					

					break;

				case LADDERMOVE:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 9;
						m_tFrame.iMotion = 7;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = true;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 6;
						m_tFrame.iMotion = 7;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;
				}
				m_ePrevSpecialState = m_eSpecialState;
				m_PreDirection = m_eDir;
			}
		}


		if (m_bHurt) {
			if (m_eCurHurtState != m_ePreHurtState || m_PreDirection != m_eDir) {
				switch (m_eCurHurtState) {
				case HITIDLE:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 9;
						m_tFrame.iStart = 9;
						m_tFrame.iEnd = 9;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 6;
						m_tFrame.iStart = 6;
						m_tFrame.iEnd = 6;
						m_tFrame.iMotion = 0;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;
				case BIGHIT_ONE_JUMP:
					if (m_eDir == DIR_RIGHT) {
						m_FHurtFrame.bLoop = true;
						m_FHurtFrame.iBegin = 1;
						m_FHurtFrame.iStart = 1;
						m_FHurtFrame.iEnd = 11;
						m_FHurtFrame.iMotion = 13;
						m_FHurtFrame.dwSpeed = 30;
						m_FHurtFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_FHurtFrame.bLoop = true;
						m_FHurtFrame.iBegin = 14;
						m_FHurtFrame.iStart = 14;
						m_FHurtFrame.iEnd = 4;
						m_FHurtFrame.iMotion = 13;
						m_FHurtFrame.dwSpeed = 30;
						m_FHurtFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 0;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 15;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}



					break;
				case BIGHIT_ONE_FALLING:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 1;
						m_tFrame.iStart = 1;
						m_tFrame.iEnd = 1;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 65;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 15;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;
				case BIGHIT_TWO_JUMP:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 2;
						m_tFrame.iStart = 2;
						m_tFrame.iEnd = 2;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 13;
						m_tFrame.iStart = 13;
						m_tFrame.iEnd = 13;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;
				case BIGHIT_TWO_FALLING:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 3;
						m_tFrame.iStart = 3;
						m_tFrame.iEnd = 3;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 12;
						m_tFrame.iStart = 12;
						m_tFrame.iEnd = 12;
						m_tFrame.iMotion = 2;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;
				case SMALLHIT:
					if (m_eDir == DIR_RIGHT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 0;
						m_tFrame.iStart = 0;
						m_tFrame.iEnd = 1;
						m_tFrame.iMotion = 4;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}

					if (m_eDir == DIR_LEFT) {
						m_tFrame.bLoop = false;
						m_tFrame.iBegin = 15;
						m_tFrame.iStart = 15;
						m_tFrame.iEnd = 14;
						m_tFrame.iMotion = 4;
						m_tFrame.dwSpeed = 50;
						m_tFrame.dwTime = GetTickCount();
					}
					break;

					m_ePreHurtState = m_eCurHurtState;
					m_PreDirection = m_eDir;


				}
				


				
			}
				
		}
	}
	else {
		if (m_eDir == DIR_RIGHT) {
			m_tFrame.bLoop = false;
			m_tFrame.iBegin = 3;
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
		}
		if (m_eDir == DIR_LEFT) {
			m_tFrame.bLoop = false;
			m_tFrame.iBegin = 12;
			m_tFrame.iStart = 12;
			m_tFrame.iEnd = 12;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
		}
		m_Own.m_iHp = 0;
		
	}
}

void CPlayer::Environment_Change(float deltatime) {
	if (!m_bHurt) {
		if (m_eSpecialState == ST_END) {
			switch (m_eCurState)
			{
			case IDLE:
				
				if (!m_bFloor) {
					
					m_eCurState = IDLE_FALLING;
				}

			
				break;
			case IDLE_FALLING: {
			

			
				float _newPos_y = m_tGravity * deltatime * 0.8f;

				m_tInfo.fY += _newPos_y;
			
				if (m_bFloor) {
			
					m_eCurState = IDLE;
				
				}
			}
							
				break;

			case WALK:
				if (!m_bFloor) {
					m_eCurState = IDLE_FALLING;
					m_fJumpSpeed = 0.f;
					m_fJumpTime = 0.f;
					float _newPos_y = m_tGravity * deltatime * 0.8f;

					m_tInfo.fY += _newPos_y;
				} 
			

				
				
				
				break;
			case DOWNWALK:      
			case LOOKDOWN:  
			case DOWNIDLE:    
				if (!m_bFloor) { 
					m_eCurState = IDLE_FALLING;
					m_fJumpSpeed = 0.f;
					m_fJumpTime = 0.f;
				}
				break;
			case JUMP:
				Jump(deltatime);
				break;
			case FALLING:
				Jump(deltatime);
				break;
			case LOOKUP_BACK:
				if (m_tFrame.iEnd == m_tFrame.iStart) {

					m_eCurState = IDLE;
				}
				break;
			case LOOKDOWN_BACK:
				if (!m_bFloor) {
					m_eCurState = IDLE_FALLING;
					m_fJumpSpeed = 0.f;
					m_fJumpTime = 0.f;
				}
				if (m_tFrame.iEnd == m_tFrame.iStart) {
					m_eCurState = IDLE;
				}
				break;
			case ATTACK:

				break;
			case DEAD:

				break;
			}
		}
		else {
			if (m_eSpecialState != LADDERMOVE && m_eSpecialState != LADDERIDLE) {
				switch (m_eCurState)
				{
				case IDLE:
					if (!m_bFloor) {
						m_eCurState = IDLE_FALLING;
					}
					break;
				case IDLE_FALLING: {
					float _newPos_y = m_tGravity * deltatime * 0.8f;

					m_tInfo.fY += _newPos_y;
				}


								 break;

				case JUMP:
					Jump(deltatime);
					break;
				case FALLING:
					Jump(deltatime);
					break;

				}

			}
		
			switch (m_eSpecialState) {
			case ATTACK:
				if (m_tFrame.iEnd == m_tFrame.iStart) {
					m_ePreState = ST_END;
					m_eSpecialState = ST_END;
				
					m_bSpecialPlaying = false;
				}
				break;
			case LADDERMOVE:

				break;
			}
		}

		
	}

	if (m_bHurt) {
		switch (m_eCurHurtState) {
		case HITIDLE:
			m_tInfo.fY += m_tGravity * deltatime * 0.8f;
			if (m_fWakeUpTime + 1000 < GetTickCount()) {
				m_bHurt = false;
			}
			break;

		case BIGHIT_ONE_JUMP:
		case BIGHIT_ONE_FALLING:
			HitBumping(deltatime);
			
			break;

		case BIGHIT_TWO_JUMP:
		case BIGHIT_TWO_FALLING:
			HitBumping(deltatime);
			break;

		case SMALLHIT:
			HitBumping(deltatime);
			break;

		}
	}
	

	
}

void CPlayer::Player_Move() {

	if (m_bShotgunRecoil)
	{
		float recoilDir = (m_eDir == DIR_RIGHT) ? -1.f : 1.f;
		m_tInfo.fX += recoilDir * m_fShotgunRecoilSpeed;

		if (m_dwShotgunRecoilTime + 120 < GetTickCount())
		{
			m_bShotgunRecoil = false;
		}
	}


	if (m_eDir == DIR_RIGHT) {
		Move_Frame_Right();
	}
	else {
		Move_Frame_Left();
	}
	if (m_bHurt) {
		HeadBingMoveFrame();
	}
	
}

void CPlayer::Jump(float deletatime) {
	// deletatime ->  한 프레임당 시간 값
	// m_fJumpTime -> 포물선의 공식이 진행되는 시간 
	// 
	m_fJumpTime += (deletatime * 0.2f);
	float v0_y = m_fJumpSpeed * sin(m_fAngle * PI / 180.f);

	// 여기까지가 포물선 공식
	float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;

	// 이건 찾아보니까 그 포물선 공식의 최고점 // 점프 최대 크기가 되었을 떄 조건 
	float v_y = v0_y - m_tGravity * m_fJumpTime;

	// 3880.f.f.f 점프키 누른 당시의 y값 // 점프 초기 값
	m_tInfo.fY = m_fStartPosy - _newPos_y;
	
	// 이건 찾아보니까 그 포물선 공식의 최고점 // 점프 최대 크기가 되었을 떄 조건 
	if (v_y < 0.f)
		m_eCurState = FALLING;

	// 이게 점프가 완료되었을때 상태 
	if (m_tInfo.fY >= m_fStartPosy)
	{
		m_fJumpTime = 0.f;
		m_tInfo.fY = m_fStartPosy;
		m_eCurState = IDLE_FALLING;
		m_fJumpSpeed = 0.f;
	}

}

void CPlayer::HitBumping(float deletatime) {

	m_fJumpTime += (deletatime* 0.1f);
	float v0_x = m_fHurtBumpingSpeed * sin(m_fHurtBumpingAngle * PI / 180.f);

	float _newPos_y = fabsf(v0_x) * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;

	float v_y = fabsf(v0_x) - m_tGravity * m_fJumpTime;

	
	m_tInfo.fX += (deletatime*0.15f) * v0_x * m_fJumpXSpeed;
	m_tInfo.fY = m_fStartPosy - _newPos_y;


	switch (m_eCurHurtState) {
	case BIGHIT_ONE_JUMP:

		if (v_y < 0.f)
			m_eCurHurtState = BIGHIT_ONE_FALLING;
	
		break;

	case BIGHIT_ONE_FALLING:
		
		if (m_bCollision )
		{
			m_fJumpTime = 0.f;
			m_fStartPosy = m_tInfo.fY;
			m_eCurHurtState = BIGHIT_TWO_JUMP;
			m_fHurtBumpingSpeed = m_fHurtBumpingSpeed /2;
			m_bCollision = false;
		}
		break;
	case BIGHIT_TWO_JUMP:
		if (v_y < 0.f)
			m_eCurHurtState = BIGHIT_TWO_FALLING;
			m_bCollision = false;
		
		break;
	case BIGHIT_TWO_FALLING:
		if (m_bCollision)
		{
			m_fJumpTime = 0.f;
			m_fWakeUpTime = GetTickCount();
			m_eCurHurtState = HITIDLE;
			m_bCollision = false;

		}
		break;
		
	}
	

}

void CPlayer::RemoteJump() {
	m_eCurState = JUMP;
	m_fStartPosy = m_tInfo.fY;
	m_fJumpSpeed = 45.f;
	m_fJumpTime = 0.f;

}

void CPlayer::Hurt(float dir) {
	m_fHurtBumpingSpeed = 45.f;
	m_fHurtBumpingAngle = 90.f;
	m_eCurHurtState = BIGHIT_ONE_JUMP;
	m_fStartPosy = m_tInfo.fY;
	m_fJumpXSpeed = dir;
	if (m_eDir == DIR_RIGHT) {
		m_pFrameKey = L"Right_Player";
	}
	else if (m_eDir == DIR_LEFT) {
		m_pFrameKey = L"Left_Player";
	}
	m_bHurt = true;
}

void CPlayer::HeadBingMoveFrame() {
	if (m_eDir == DIR_RIGHT) {
		if (m_FHurtFrame.dwSpeed + m_FHurtFrame.dwTime < GetTickCount())
		{
			++m_FHurtFrame.iStart;
			m_FHurtFrame.dwTime = GetTickCount();

			if (m_FHurtFrame.iStart > m_FHurtFrame.iEnd && !(m_FHurtFrame.bLoop)) {
				m_FHurtFrame.iStart = m_FHurtFrame.iEnd;
			}



			if (m_FHurtFrame.iStart > m_FHurtFrame.iEnd && (m_FHurtFrame.bLoop))
				m_FHurtFrame.iStart = m_FHurtFrame.iBegin;

		}
	}
	else {
		if (m_FHurtFrame.dwSpeed + m_FHurtFrame.dwTime < GetTickCount())
		{
			--m_FHurtFrame.iStart;
			m_FHurtFrame.dwTime = GetTickCount();

			if (m_FHurtFrame.iStart < m_FHurtFrame.iEnd && !(m_FHurtFrame.bLoop)) {
				m_FHurtFrame.iStart = m_FHurtFrame.iEnd;
			}

			if (m_FHurtFrame.iStart < m_FHurtFrame.iEnd)
				m_FHurtFrame.iStart = m_FHurtFrame.iBegin;

		}
	}
}
CObj* CPlayer::Create_Bomb(DIRECTION eDir, float m_fSpeed, float m_fAngle, float m_fJumpSpeed)
{
	CObj* pBomb = new CBomb;
	pBomb->Initialize();
	pBomb->Set_Direction(eDir);
	static_cast<CBomb*>(pBomb)->SetJump_Info(m_fSpeed, m_fAngle, m_fJumpSpeed);
	pBomb->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	

	return pBomb;
}

CObj* CPlayer::Create_Tether(float m_fSpeed, float m_fAngle, float m_fJumpSpeed)
{
	CObj* pTether = new CTether;
	pTether->Initialize();
	pTether->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CTether*>(pTether)->Set_FirstPos({ m_tInfo.fX, m_tInfo.fY });

	return pTether;
}