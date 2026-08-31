#pragma once

#include "define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void		Initialize()	PURE;
	virtual void		Update(float deltatime)		PURE;
	virtual void		Late_Update(float deltatime)	PURE;
	virtual void		Render(HDC hDC) PURE;
	virtual void		Release()		PURE;

	float GetTime() { return m_CurrTime; }
protected:
	float m_StartTime;
	float m_CurrTime;
};

