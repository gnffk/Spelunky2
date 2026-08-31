#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:

	enum STATE { DISAPPEARED, IDLE,IDLE_FALLING, WALK, LOOKUP, LOOKUP_BACK,LOOKDOWN, LOOKDOWN_BACK, DOWNWALK, DOWNIDLE, JUMP, FALLING, ATTACK, 
		HITIDLE, BIGHIT_ONE_JUMP,BIGHIT_ONE_FALLING, BIGHIT_TWO_JUMP,BIGHIT_TWO_FALLING, SMALLHIT, LADDERIDLE,LADDERMOVE, DEAD, ST_END };


public:
	CPlayer();
	virtual ~CPlayer();



public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Key_Input();
	void Motion_Change();
	void Environment_Change(float deltatime);
	void Player_Move();

	void Jump(float deletatime);
	void HitBumping(float deletatime);


	void RemoteJump();



	void Hurt(float dir);

	void HeadBingMoveFrame();

	CObj* Create_Bomb(DIRECTION eDir, float m_fSpeed, float m_fAngle, float m_fJumpSpeed);

	CObj* Create_Tether( float m_fSpeed, float m_fAngle, float m_fJumpSpeed);


	STATE GetState() { 
		return m_eCurState; 
	}
	PlayerOwn GetOwn(){ return m_Own; }
	bool GetFalling() { return m_bFloor; }
	bool GetWallCollision() { return m_WallCollision; }
	CObj* Get_Weapon() { return m_Weapon; }
	CObj* Get_Hand() { return m_Hand; }
	bool  Get_Next() { return m_bNext; }
	bool  Get_Hurt() { return m_bHurt; }
	int	  Get_Key() { return m_iKey; }
	STATE GetCurHurtState() { return m_eCurHurtState; }
	void SetDead() { m_bDead = true; }
	void SetCurrentState(STATE a) { m_eCurState = a; }
	void SetFalling(bool floor) { m_bFloor = floor; }
	void SetWallCollision(bool wall) { m_WallCollision = wall; }
	void SetSpecialState(STATE a) { m_eSpecialState = a; }
	void SetLadder(bool Ladder) { m_bLadder = Ladder; }
	void SetHand(bool _bHand) { m_bHand = _bHand; }
	void SetHp(int _hp) { m_Own.m_iHp -= _hp; }
	void SetGold(int _gold) { m_Own.m_iMoney += _gold; }
	void SetBomb(int _bomb) { m_Own.m_iBomb += _bomb; }
	void SetRope(int _Rope) { m_Own.m_iRope += _Rope; }
	void SetNext(bool _bNext) { m_bNext = _bNext; }
	void SetHurt(bool _bHurt) { m_bHurt = _bHurt; }
	void SetJumpXSpeed(float _xSpeed) { m_fJumpXSpeed = _xSpeed; }
	void SetKey(int _key) { m_iKey += _key; }
private:
	// 이동
	STATE				m_ePreState;
	STATE				m_eCurState;
	// 공격, 사다리
	STATE				m_eSpecialState;
	STATE				m_ePrevSpecialState;
	
	// 다쳤을때
	STATE				m_ePreHurtState;
	STATE				m_eCurHurtState;

	FRAME				m_FHurtFrame;

	DIRECTION			m_PreDirection;


	PlayerOwn			m_Own;

	CObj*				m_Hand;
	CObj*				m_Weapon;
	bool				m_bSpecialPlaying;
	bool				m_bHurt;
	bool				m_WallCollision;
	bool				m_bLadder;
	bool				m_bHand;
	bool				m_bNext;

	bool  m_bShotgunRecoil;
	float m_fShotgunRecoilSpeed;
	DWORD m_dwShotgunRecoilTime;

	float				m_fJumpXSpeed;
	float				m_fJumpSpeed;
	float				m_fJumpTime;

	float				m_fHurtBumpingSpeed;
	float				m_fHurtBumpingAngle;

	float				m_fStartPosy;

	float				m_fWakeUpTime;

	int					m_iKey;


};

