#include "pch.h"
#include "EffectManager.h"
#include "Particle.h"
#include "BmpManager.h"
#include "CEffect.h"
CEffectManager* CEffectManager::m_pInstance = nullptr;

CEffectManager::~CEffectManager()
{
}

void CEffectManager::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/fx_rubble.bmp", L"Rubble");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Fire.bmp", L"Fire");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bomb.bmp", L"Bomb");

}

void CEffectManager::Update(float deltatime)
{
    vector<CObj*> vecSpawn;

    for (auto iter = m_vecParticle.begin(); iter != m_vecParticle.end(); )
    {
        CObj* p = *iter;
        p->Update(deltatime);

 

        if (static_cast<CParticle*>(p)->NeedSplit())
        {
     
            if (static_cast<CParticle*>(p)->GetGen() >= 1)
            {
                Safe_Delete<CObj*>(*iter);
                iter = m_vecParticle.erase(iter);
                continue;
            }

            Vec2 pos = { static_cast<CParticle*>(p)->Get_Info()->fX,static_cast<CParticle*>(p)->Get_Info()->fY };
            Vec2 vel = static_cast<CParticle*>(p)->GetVel();


     
            CObj* p1 = new CParticle;
            static_cast<CParticle*>(p1)->InitValue(pos, { -vel.x, vel.y }, 200.f, static_cast<CParticle*>(p)->GetGen() + 1, static_cast<CParticle*>(p)->GetType());

            CObj* p2 = new CParticle;
            static_cast<CParticle*>(p2)->InitValue(pos, { vel.x, -vel.y }, 200.f, static_cast<CParticle*>(p)->GetGen() + 1, static_cast<CParticle*>(p)->GetType());
          
            vecSpawn.push_back(p1);
            vecSpawn.push_back(p2);


            Safe_Delete<CObj*>(*iter);
            iter = m_vecParticle.erase(iter);
            continue;
        }

  
        if (static_cast<CParticle*>(p)->IsDead())
        {
            Safe_Delete<CObj*>(p);
            iter = m_vecParticle.erase(iter);
        }
        else
            ++iter;
    }


    for (auto& p : vecSpawn)
        m_vecParticle.push_back(p);

    for (auto iter = m_vecEffect.begin();
        iter != m_vecEffect.end(); )
    {
        int iResult = (*iter)->Update(deltatime);

        if (iResult == OBJ_DEAD)
        {
            Safe_Delete<CObj*>(*iter);
            iter = m_vecEffect.erase(iter);
        }
        else
        {
            ++iter;
        }

    }
}

void CEffectManager::Late_Update(float deltatime)
{
}

void CEffectManager::Render(HDC hDC)
{
    for (auto& p : m_vecParticle)
        p->Render(hDC);    
    
    for (auto& p : m_vecEffect)
        p->Render(hDC);
}

void CEffectManager::Release()
{
    for (auto& p : m_vecParticle)
    {
        if (p)
            delete p;
    }

    m_vecParticle.clear();   
    
    
    for (auto& p : m_vecEffect)
    {
        if (p)
            delete p;
    }

    m_vecEffect.clear();
}

void CEffectManager::Paricle_Effect(Vec2 pos, int type) {
    CParticle* p = new CParticle;
    Vec2 vel = { rand() % 200 - 100.f, -(rand() % 200 + 100.f) };
 
    p->InitValue(pos, vel, 200.f, 0, type);
    m_vecParticle.push_back(p);
}


void CEffectManager::ADD_Effect(Vec2 pos, int type) {
    CEffect* p = new CEffect;
    Vec2 vel = { rand() % 200 - 100.f, -(rand() % 200 + 100.f) };
 
    p->InitValue(pos, vel, 200.f, 0, type);
    m_vecEffect.push_back(p);
}