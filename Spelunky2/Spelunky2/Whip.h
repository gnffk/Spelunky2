#pragma once
#include "Obj.h"

class CWhip : public CObj
{
public:
	enum State{ ATTACKREADY,ATTACKGO,ATTACKEND, NONE};
public:
	CWhip();
	virtual ~CWhip();

	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void CWhip_Move();

	void Whip_Enviornment();
	State Get_State() { return m_eState; }

	void Set_Target(CObj* _target) { m_pTarget = _target; }
	void Set_State(State _eState) { m_eState = _eState; }
private:
	CObj* m_pTarget;
	State m_eState;
	State m_ePreState;

	HDC hMemDC;
	HDC Right;
	HDC Left;

	float m_fDistance;
	float m_fDistance_Y;

	float m_fTime;
};

