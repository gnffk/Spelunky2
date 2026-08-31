#pragma once
#include "Scene.h"
class CObj;
class CUI;

class CReadyScene : public CScene
{
public:
	CReadyScene();
	virtual ~CReadyScene();


public:
	void Initialize() override;
	void Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Mange_Bgm();

	void Check_Mouse();

protected:
	int m_bOnceBgm;

	int m_iChoice;

	CObj* m_pMouse;
	CUI* m_pUI;


};

