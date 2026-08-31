#pragma once
#include "define.h"
class CUI  abstract
{
public:
	CUI();
	virtual ~CUI();



public:
	void		Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}


	bool		Get_Dead() { return m_bDead; }
	const RECT* Get_Rect() const { return &m_tRect; }
	const INFO* Get_Info() const { return &m_tInfo; }
	bool		Get_Remain() { return m_bRemain; }

	void		Set_PosX(float fX) { m_tInfo.fX += fX; }
	void		Set_PosY(float fY) { m_tInfo.fY += fY; }
	void		Set_Remain(bool _remain) { m_bRemain = _remain; }

public:
	virtual void	Initialize()	PURE;
	virtual int		Update(float deltatime)		PURE;
	virtual void	Late_Update(float deltatime)	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;

	void Set_In(bool _In) { m_bIN = _In; }
	bool Get_In() { return m_bIN; }

protected:
	void Update_Rect();

	void Move_Frame();
	void Move_Frame_Right();
	void Move_Frame_Left();

	void Move_Frame_Free(int maxIndex, int firstMotion);






protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	FRAME		m_tFrame;


	float		m_fSpeed;
	DIRECTION	m_eDir;
	bool		m_bDead;
	float		m_fAngle;
	float		m_fDistance;

	bool		m_bRemain;


	bool m_bIN;


};