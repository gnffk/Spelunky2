#pragma once
#include "Obj.h"
#include "UI.h"

class COpenKey : public CObj
{

public:
	COpenKey();
	~COpenKey();


public:

	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;



private:
	HDC m_hDCOpenKey;
};