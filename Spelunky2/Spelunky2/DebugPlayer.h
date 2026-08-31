#pragma once
#include "Obj.h"

class CDebugPlayer : public CObj
{


public:
	CDebugPlayer();
	virtual ~CDebugPlayer();



public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Key_Input();


};

