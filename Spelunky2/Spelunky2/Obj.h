#pragma once

#include "define.h"


class CObj abstract
{
public:
	CObj();
	virtual ~CObj();



public:
	void		Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}


	bool		Get_Dead() { return m_bDead; }
	const RECT* Get_Rect() const { return &m_tRect; }
	const INFO* Get_Info() const { return &m_tInfo; }
	const RECT* Get_CollisionRect() const { return &m_CollisionRect; }
	Vec2		Get_RealSize() { return m_fRealSize; }
	DIRECTION	GetDirect() { return m_eDir; }
	RENDERID    Get_RenderID() const { return m_eRender; }
	CollisionType Get_Collision() {return m_eCollisionType;}
	bool		Get_PlayerIn() { return m_PlayerIn; }
	float		Get_invincibility() { return m_invincibility; }
	ITEM		Get_ItemType() { return m_eItemType; }
	bool		Get_Store() { return m_bStore; }
	bool		Get_Remain() { return m_bRemain; }
	ENEMY		Get_EnemyType() { return m_EnemyType; }
	float		Get_StopCollision() { return m_fStopCollision; }

	void		Set_PosX(float fX) { m_tInfo.fX += fX; }
	void		Set_PosY(float fY) { m_tInfo.fY += fY; }
	void		Set_Direction(DIRECTION dir) { m_eDir = dir; }
	void		Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void		Set_Collision() { m_bCollision = true; }
	void		Set_PlayerIn(bool _PlayerIn) { m_PlayerIn = _PlayerIn; }
	void		Set_invincibility(float _invincibility) { m_invincibility = _invincibility; }
	void		Set_Angle(float _Angle) { m_fAngle = _Angle; }
	void		Set_Dead(bool Dead) { m_bDead = Dead; }
	void		Set_Store(bool _bStore) { m_bStore = _bStore; }
	void		Set_Remain(bool _bRemain) { m_bRemain = _bRemain; }
	void		Set_CollisionType(CollisionType _type) { m_eCollisionType = _type; }
	void		Set_StopCollision(float _collision) { m_fStopCollision = _collision; }
	void		Set_Collision(bool _bCollision) { m_bCollision = _bCollision; }

public:
	virtual void	Initialize()	PURE;
	virtual int		Update(float deltatime)		PURE;
	virtual void	Late_Update(float deltatime)	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;

protected:
	void Update_Rect();

	void Move_Frame();
	void Move_Frame_Right();
	void Move_Frame_Left();

	void Move_Frame_Free(int maxIndex, int firstMotion);






protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	RECT		m_CollisionRect;
	ENEMY		m_EnemyType;
	FRAME		m_tFrame;
	bool		m_PlayerIn;
	bool		m_bCollision;
	float		m_fSpeed;
	DIRECTION	m_eDir;
	bool		m_bDead;
	bool		m_bFloor;
	float		m_fAngle;
	float		m_fDistance;

	float		m_invincibility;

	float		m_tGravity;
	Vec2		m_fRealSize;
	Vec2		m_fBombSize;

	ITEM		m_eItemType;

	CObj* m_pTarget;
	const TCHAR* m_pFrameKey;

	RENDERID      m_eRender;

	CollisionType m_eCollisionType;

	bool m_bStore;

	bool m_bRemain;

	float m_fStopCollision;
};

