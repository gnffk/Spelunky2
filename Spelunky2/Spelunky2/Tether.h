#pragma once
#include "Obj.h"
struct Check {
	bool bRender;
	bool bEnd;
};

class CTether : public CObj
{
public:
	enum State{ UP, STOP, DOWN, COMPLETE};
public:
	CTether();
	~CTether();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void Change_State();

	void Environment_State();

	void Move_Frame_Tether();
	
	void Set_FirstPos(Vec2 _firstPos) { m_vFirstPos = _firstPos; }
private:
	FRAME		m_MoveFrame;


	State m_eTetherState;
	State m_ePreTetherState;


	Vec2  m_vFirstPos;
	Vec2  m_VMovePos;

	vector <Check> m_vecRenderTrue;
	int		m_iCount;
	int		m_iSize;
	
	float	m_fTime;
};

