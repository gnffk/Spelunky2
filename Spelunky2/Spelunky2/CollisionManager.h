#pragma once
#include "Obj.h"

class CPlayer;

class CCollisionManager
{
public:
	static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_RectEx_Player(CObj* Dst, vector<CObj*> _Src);
	static void Collision_RectEx_Player_Item(CObj* Dst, list<CObj*> _Src);
	static void Collision_RectEx_Player_Item_Hand(CObj* Dst, list<CObj*> _Src, CObj*& m_Hand);
	static void Collision_RectEx_Boss(CObj* Dst, vector<CObj*>& _Src);
	static void Collision_RectEx_Item(list<CObj*> _Dst, vector<CObj*> _Src);
	static void Collision_RectEx_Player_Boss(CObj* Dst, CObj* Src);
	static void Collision_RectEx_Enemy(list<CObj*> _Dst, vector<CObj*> _Src);
	static void Collision_RectEx_Player_Enemy(CObj* Dst, list<CObj*> _Src);

	
	static void Collision_RectEx_Weapon_Enemy(CObj* Dst, list<CObj*> _Src);

	static void Collision_RectEx_Bomb(CObj* Dst, vector<CObj*> _Src);

	static void Collision_RectEx_Particle(vector<CObj*> _Dst, vector<CObj*> _Src);

	static void Collision_RectEx_Bullet_ENEMY(list<CObj*> _Dst, list<CObj*> _Src);

	static void TileCheck(CObj* _Dst, vector<CObj*> _Src);
	
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static bool Check_Ladder_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static bool Check_Circle(CObj* pDst, CObj* pSrc);
	static void Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Bomb(CObj* pDst, CObj* pSrc);
	
};

