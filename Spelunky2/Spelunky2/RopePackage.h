#pragma once
#include "Obj.h"
#include "UI.h"
class CRopePackage : public CObj
{

public:
	CRopePackage();
	~CRopePackage();


public:

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void IsPurChase();

	CUI* GetUI() { return m_pStoreUI; }
private:
	HDC m_hDCRopePackage;

	CUI* m_pStoreUI;
	
};