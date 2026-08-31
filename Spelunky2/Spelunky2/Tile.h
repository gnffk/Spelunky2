#pragma once
#include "Obj.h"

class CTile : public CObj
{

public:
	CTile();
	virtual ~CTile();

public:
	int		Get_DrawID() { return m_iDrawID; }
	int		Get_Option() { return m_iOption; }
	int		Get_iLayer() { return m_iLayer; }
	int		Get_Count() { return m_iCount; }
	bool	Get_Ladder() { return m_Ladder; }
	

	void	Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void	Set_Option(int iOption) { m_iOption = iOption; }
	void    Set_Layer(int iLayer) { m_iLayer = iLayer; }
	void    Set_Count(int iCount) { m_iCount = iCount; }
	

public:
	void Initialize()		override;
	int  Update(float deltatime)			override;
	void Late_Update(float deltatime)		override;
	void Render(HDC hDC)	override;
	void Release()			override;

	void DifferentTypeDraw();

	void CheckLayer();

	CObj* Spone();

	bool Get_up(){ return m_UP; }
	bool Get_down(){ return m_DOWN; }
	bool Get_right(){ return m_RIGHT; }
	bool Get_left(){ return m_LEFT; }
	bool Get_Bomb() { return m_Bomb; }
	void SetTileFloor(bool up, bool down, bool right, bool left) {
		m_UP = up; m_DOWN = down; m_RIGHT = right, m_LEFT = left;
	};


private:
	bool		m_floorx;
	bool		m_Ladder;

	bool		m_UP;
	bool		m_DOWN;
	bool		m_RIGHT;
	bool		m_LEFT;

	bool		m_Bomb;

	int			m_iDrawID;
	int			m_iOption;
	int			m_iLayer;
	int			m_iCount;
	Vec2		m_iMemDCTile;
	HDC			m_hMemDC;
	Vec2		m_RealSize;
	HPEN hPen;
	HBRUSH hBrush;
};