#pragma once
#include "Obj.h"

class CParticle : public CObj
{
public:
	CParticle();
	virtual ~CParticle();

public:
	void Initialize() override;
	void InitValue(Vec2 pos, Vec2 vel, float life, int gen, int type);
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	bool IsDead() const { return m_fLife <= 0.f; }
	bool NeedSplit() const { return m_bSplit; }
	void SetSplit() { m_bSplit = true; }

	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetVel() const { return m_vVel; }
	int GetGen() const { return m_iGen; }
	int GetType() const { return m_iType; }

protected:
	HDC  m_hDC;
	Vec2  m_vPos;
	Vec2  m_vVel;
	float m_fLife;
	int   m_iGen;
	int	  m_iType;
	Vec2  m_iTypeXY;
	bool  m_bSplit;
	float m_fJumpTime;
	float m_fStartPosy;
	float RandJump;
	
};

