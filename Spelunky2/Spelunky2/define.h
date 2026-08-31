#pragma once

// 100 x 100
// 20 X 50 

#define		WINCX 1280
#define		WINCY 720

#define		MAPCX 4000
#define		MAPCY 4000

#define     TILENUMX 50
#define     TILENUMY 50


#define		TILEX 80
#define     TILEY 80


#define		PURE = 0

#define		OBJ_NOEVENT 0
#define		OBJ_DEAD    1

#define		PI	3.141592f

#define		VK_MAX		0xff

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };

enum SCENEID {SCMAPEDIT ,SCMENU,SCREADYSCENE, SCSTAGE2, SCSTAGE3, SCEND };
enum OBJID { OBJ_WEAPON, OBJ_PLAYER,  OBJ_MOUSE,OBJ_MONSTER,OBJ_ITEM, OBJ_BOSS, OBJ_BULLET, OBJ_END };

enum ITEM {ITEM_BOBM, ITEM_SHOTGUN, ITEM_GOLD,ITEM_KEY, ITEM_BOMB_PACKAGE, ITEM_ROPE_PACKAGE, ITEM_END};
enum CollisionType { FLOOR,PITFALL,NEXTSTAGE, LADDER, C_BOMB, C_ITEM,C_BULLET, END };
enum RENDERID { TETHER, GAMEOBJECT, SHOTGUN, UI, TILE, RENDER_END };
enum CHANNELID { SOUND_BGM, SOUND_EFFECT,SOUND_TALK, MAXCHANNEL };
enum ENEMY {ENEMY_BAT, ENEMY_SNAKE, ENEMY_SHOPMAN};
template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct tagObjDelete
{
	template<typename T>
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};


struct tagDeleteMap
{
	template<typename T>
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};



struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}


	const TCHAR* m_pTag;
};



typedef struct tagInfo
{
	float		fX, fY;	// 중점
	float		fCX, fCY; // 가로, 세로 길이

}INFO;
typedef struct tagFrame
{
	bool    bLoop;
	int		iBegin;
	int		iStart;
	int		iEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

struct Vec2 {
	float x;
	float y;
};

struct PlayerOwn {
	int					m_iHp;
	int					m_iBomb;
	int					m_iRope;
	int					m_iMoney;
};

struct EnemyOwn {
	int				m_iHp;

};

extern HWND g_hWnd;

extern BOOL g_viewCollisionBox;

extern BOOL g_Off;