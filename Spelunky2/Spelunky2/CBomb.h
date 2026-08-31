#pragma once
#include "Obj.h"
class CBomb : public CObj
{
public:
	enum STATE{JUMP, FALLING,JUMPFALLING,DONE, BOMB, BOMBANIM};
public:
	CBomb();
	~CBomb();


	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void State_Gravity(float deltatime);
	void Jump(float deltatime);
	void SetJump_Info(float speed, float angle, float jumpSpeed);
	void MoveFrame1();
	void Set_State(STATE _bombState) { m_bombState = _bombState; }

	RECT Get_BombRect() { return m_BOMBRECT; }
	Vec2 Get_BombSize() { return m_fBombSize; }
private:
	HDC m_BombDC;
	STATE m_bombState;
	STATE m_prebombState;

	float m_fAcceleration;

	bool m_bTrigger;
	
	float m_fJumpTime;
	float m_fJumpSpeed;
	float m_fStartPosy;
	float m_fStartPosx;

	float m_vx;

	RECT m_BOMBRECT;

	bool m_bBobmbing;
	bool m_bBobmKeep;

	HDC m_BombingDC;
	FRAME m_tFrame1;


};

