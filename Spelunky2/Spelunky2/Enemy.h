#pragma once
#include "Obj.h"

class CEnemy : public CObj
{
public:
	CEnemy();
	~CEnemy();
	
public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;
};

