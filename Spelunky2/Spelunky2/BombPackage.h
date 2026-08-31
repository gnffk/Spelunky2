#pragma once
#include "Obj.h"
#include "UI.h"
class CBombPackage : public CObj
{

public:
	CBombPackage();
	~CBombPackage();


public:

	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;


	void IsPurChase();
	CUI* GetUI() { return m_pStoreUI; }

private:
	HDC m_hDCBombPackage;
	CUI* m_pStoreUI;
};