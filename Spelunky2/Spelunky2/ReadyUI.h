#pragma once
#include "UI.h"
#include "Obj.h"
#include <string>
class CReadyUI : public CUI
{
public:
	CReadyUI();
	virtual ~CReadyUI();

public:

	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Choice_Menu(int choice);
protected:
	HFONT m_hFont;
	float m_fColor1;
	float m_fColor2;
	Vec2  m_vStart;
};

