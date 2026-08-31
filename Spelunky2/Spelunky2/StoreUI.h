#pragma once
#include "UI.h"

class CObj;

class CStoreUI : public CUI
{
public:
	CStoreUI();
	virtual ~CStoreUI();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Target_Write(HDC hDC);

	
	
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	CObj* Get_Target() { return m_pTarget; }

	void Set_Change(int _bChange) { m_bChange = _bChange; }
	int Get_Change() { return m_bChange; }

private:
	CObj* m_pTarget;
	HFONT m_hFont;
	HDC HDCUI;
	int m_bChange;
};

