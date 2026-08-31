#pragma once
#include "Obj.h"
class CGold : public CObj
{

public:
	CGold();
	virtual ~CGold();
public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	HDC m_hDCGold;
};

