#pragma once
#include "Scene.h"

class CObj;

class CMapEditScene : public CScene
{
public:
	enum MapType{ NONE, MAP1, MAP2, MAP3, BAT, SNAKE, ERASE};
public:
	CMapEditScene();
	virtual ~CMapEditScene();

public:
	void Initialize() override;
	void Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;

	void KeyDown();

private:
	CObj* m_pPlayer;
	CObj* m_pMouse;

	Vec2  m_CursorPos;
	HDC   m_hTextureUI;
	
	Vec2  m_TileSize;

	MapType m_fMapType;
};

