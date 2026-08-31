#pragma once

#include "Obj.h"

class CBoss : public CObj 
{
public:
	enum BossPattern{ Pattern1, Pattern2};
	enum BossState {IDLE, MOVE, JUMP, ATTACK, ATTACKDONE,
					READYSTAGE, OPENMASK , BOMB, CHASE};
	enum DIR	{ LEFT = -1, RIGHT = 1};
public:
	CBoss();
	~CBoss();

public:
	
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Check_Pattern(float deltatime);
	void Simple_Attack(float deltatime);

	void Jump(float deltatime);

	void Attack();

	void ComPlexAttack(float deltatime);

	void Chase_Target(float deltatime);

	void Bomb_Attack(float deltatime);

	CObj* Create_Bomb(DIRECTION eDir, float m_fSpeed, float m_fAngle, float m_fJumpSpeed, float m_fRand);

	void SetTarget(CObj* _target) { m_pTarget = _target; }
	void SetBroke(bool bBroke) { m_bBroke = bBroke; }
	void	  SetBossState(BossState _eBossState) {
		m_eBossState = _eBossState;
	}
	BossState GetBossState() {
		return m_eBossState;
	}
	bool	 GetbBroke() { return m_bBroke; }
	
private:
	BossPattern		m_eBossPattern;
	BossState		m_eBossState;
	
	DIR				m_dir;

	float			m_bBroke;
	float			m_StartAttackTime;
	float			m_flowTime;
	
	float			m_fJumpTime;
	float			m_fJumpSpeed;
	float			m_fStartPosx;
	float			m_fStartPosy;

	float			m_fStartTime;

	int				m_iBombCount;
	Vec2			m_vChangeMask;


	CObj* m_pTarget;
};

