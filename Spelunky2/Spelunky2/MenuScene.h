#pragma once
#include "Scene.h"

class CObj;

class CMenuScene : public CScene
{
public:
	CMenuScene();
	virtual	~CMenuScene();

public:
	void Initialize() override;
	void Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Key_Set();

	void Mange_Bgm();

private:
	int m_bOnceBgm;
};

