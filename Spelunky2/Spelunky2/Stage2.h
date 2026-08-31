#pragma once
#include "Scene.h"
class CObj;
class CUI;

class CStage2 : public CScene
{
public:
	CStage2();
	virtual ~CStage2();
	
public:
	void Initialize() override;
	void Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Spone();

	void Key_Set();
	void Mange_Bgm();
	float GetTime() { return m_CurrTime; }
private:
	CObj* m_pPlayer;
	CUI* baseUI;
	CUI* DeadUI;
	int m_bOnceBgm;
};

