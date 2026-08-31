#pragma once
#include "Obj.h"
class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();



	void Initialize() override;

	int Update(float deltatime) override;

	void Late_Update(float deltatime) override;

	void Render(HDC hDC) override;

	void Release() override;

	Vec2 GetWinPos() { return WindowPos; }

private:
	Vec2	WindowPos;

};

