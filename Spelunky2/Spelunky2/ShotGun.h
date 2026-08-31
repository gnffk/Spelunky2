#pragma once
#include "Obj.h"

class CUI;

class CShotGun : public CObj
{
public:
	enum State{IDLE, GRAB};
public:
	CShotGun();
	virtual ~CShotGun();


	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Change_enviornment();

	void Shot();

	void IsPurChase();

	CObj* Create_Bullet();

	void Set_State(State _state) { m_ShotgunState = _state; }

	CUI* GetUI() { return m_pStoreUI; }





private:
	HDC hMemDC;

	State m_ShotgunState;

	CUI* m_pStoreUI;


	

	
};

