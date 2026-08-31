#pragma once
#include "Scene.h"

class CObj;
class CUI;

class CStage3 : public CScene
{
public:
	CStage3();
	~CStage3();

public:
	
	void Initialize() override;
	void Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;
	void Mange_Bgm();

private:
	int m_bOnceBgm;

private:
	CObj* m_pPlayer;
	CObj* m_pBoss;
	CUI* baseUI;
	CUI* DeadUI;

};

