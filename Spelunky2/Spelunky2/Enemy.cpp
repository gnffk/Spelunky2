#include "pch.h"
#include "Enemy.h"
CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Initialize()
{
	m_eRender = GAMEOBJECT;
}

int CEnemy::Update(float deltatime)
{


	return OBJ_NOEVENT;
}

void CEnemy::Late_Update(float deltatime)
{
}

void CEnemy::Render(HDC hDC)
{
}

void CEnemy::Release()
{
}
