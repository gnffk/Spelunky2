#pragma once
#include "Obj.h"


class CEffect : public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	void Initialize() override;
	void InitValue(Vec2 pos, Vec2 vel, float life, int gen, int type);
	int  Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;
protected:
	HDC  m_hMiddleDC;
	HDC  m_hLittleDC;


};

