#pragma once
#include "Obj.h"
#include "UI.h"
class CShopMan : public CObj
{
public:

	enum State { IDLE,HIT, HITIDLE, RUN,JUMP, CHASE, ANSWER, DEAD };
public:
	CShopMan();
	virtual ~CShopMan();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;


	void Motion_Change();
	void Environment_Change(float deltatime);

	void Move_Dir();

	void RemoteHit(float deltatime);

	void RemoteJump(float deltatime);

	void Set_Hp(int _hp) { m_Own.m_iHp -= _hp; }
	int  Get_Hp() { return m_Own.m_iHp; }

	void Set_State(State _state) { m_curState = _state; }
	State Get_State() { return m_curState; }

	void Set_dir(float _dir) { m_dir = _dir; }
	CUI* GetUI() { return m_pStoreUI; }
	void RemoteJump();

	void Set_time(float _time) { m_Time = _time; }
	float Get_time() { return m_Time; }
public:
	HDC	  m_MonsterHDC;
	DIRECTION m_eprevDir;
	State m_curState;
	State m_prevState;
	EnemyOwn m_Own;
	CObj* m_Weapon;
public:
	bool  m_bkind;
	float m_fJumpTime;
	float m_fJumpSpeed;
	float m_fStartPosy;
	float m_fStartPosx;
	float m_dir;
	float ShotTime;

	float m_Time;
	CUI* m_pStoreUI;
};

