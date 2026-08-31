#include "pch.h"
#include "Particle.h"
#include "BmpManager.h"
CParticle::CParticle()
{
}
CParticle::~CParticle()
{
}
void CParticle::Initialize()
{
}

void CParticle::InitValue(Vec2 pos, Vec2 vel, float life, int gen, int type) {
    m_hDC = CBmpMgr::Get_Instance()->Find_Image(L"Rubble");
    m_tInfo.fX = pos.x;
    m_tInfo.fY = pos.y;
    m_fStartPosy = pos.y;
    m_tInfo.fCX = 20;
    m_tInfo.fCY = 20;
    RandJump = rand() % 40 + 20.f;
    m_fRealSize.x = 30;
    m_fRealSize.y = 30;
    m_iGen = gen;
    m_vVel = vel;
    m_fLife = life;
    m_tGravity = 9.8;
    m_bSplit = false;
    m_fJumpTime = 0.f;
    m_fAngle = 90.f;
    m_iType = type;
    switch (type) {
    case 0:
        m_iTypeXY.x = 0;
        m_iTypeXY.y = 0;
        break;


    case 1:
        m_iTypeXY.x = 7;
        m_iTypeXY.y = 1;
        break;

    case 2:
        m_iTypeXY.x = 2;
        m_iTypeXY.y = 5;
        break;
    }
}

int CParticle::Update(float deltatime)
{
    __super::Update_Rect();


    m_fLife -= deltatime;
    m_fJumpTime += (deltatime * 0.2f);


    float v0_y = RandJump * sin(m_fAngle * PI / 180.f);

    float _newPos_y = v0_y * m_fJumpTime - 0.5f * m_tGravity * m_fJumpTime * m_fJumpTime;


    float v_y = v0_y - m_tGravity * m_fJumpTime;



    m_tInfo.fX += m_vVel.x * deltatime * 0.07f;
    m_tInfo.fY = m_fStartPosy - _newPos_y;


    if (m_iGen == 0 && m_fLife < 0.5f && !m_bSplit) {
        m_bSplit = true;
    }
        

    return 0;
}

void CParticle::Late_Update(float deltatime)
{
}

void CParticle::Render(HDC hDC)
{
   // Rectangle(hDC, m_CollisionRect.left, m_CollisionRect.top, m_CollisionRect.right, m_CollisionRect.bottom);
    GdiTransparentBlt(hDC,
        m_CollisionRect.left,
        m_CollisionRect.top,
        (int)m_fRealSize.x,
        (int)m_fRealSize.y,
        m_hDC,
        m_iTypeXY.x * 128,
        m_iTypeXY.y * 128,
        128,
        128,
        RGB(255, 255, 255));
}

void CParticle::Release()
{
}
