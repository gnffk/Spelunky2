#pragma once
#include "UI.h"
#include "Obj.h"
#include "Scene.h"


class CDeadUI : public CUI
{
public:
	CDeadUI();
	virtual ~CDeadUI();

	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Player_Dead(float deltatime);

	void Set_Targert(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Scene(CScene* _pScene) { m_pScene = _pScene; }

public:
	CScene* m_pScene;
	CObj*	m_pTarget;
	bool	m_bDead;
	bool    m_bReverse;
	Vec2	m_ReversePos;
	float   m_fDistance;
	float m_fAcceleration;
};

