#pragma once

#include "Obj.h"

class CSnake : public CObj
{
public:
	enum State {IDLE, MOVE, CHANGE, ATTACK, DEAD };
public:
	CSnake();
	virtual ~CSnake();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;
	
	void Set_State(State _state) { m_curState = _state; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	CObj* Get_Target() { return m_pTarget; }
	State Get_State() { return m_curState; }

	void Motion_Change();
	void Environment_Change(float deltatime);

	void Move_Dir();



public:
	CObj* m_pTarget;
	HDC	  m_MonsterHDC;
	DIRECTION m_eprevDir;
	State m_curState;
	State m_prevState;

	float m_fTime;
};

