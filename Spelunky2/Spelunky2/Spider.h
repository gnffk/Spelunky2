#pragma once
#include "Obj.h"

class CSpider : public CObj
{
public:
	enum State { IDLE, CHASE, DEAD };
public:
	CSpider();
	virtual ~CSpider();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	CObj* Get_Target() { return m_pTarget; }
	void Search_Target();
	void Chase_Target(float deltatime);
	void Motion_Change();
	void Environment_Change(float deltatime);

	void Move_Dir();

	void Check_Dir();

public:
	CObj* m_pTarget;
	HDC	  m_MonsterHDC;
	DIRECTION m_eprevDir;
	State m_curState;
	State m_prevState;
};

