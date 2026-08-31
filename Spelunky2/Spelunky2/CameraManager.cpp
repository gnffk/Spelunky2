#include "pch.h"
#include "Obj.h"
#include "CameraManager.h"

CCameraManager* CCameraManager::m_pInstance = nullptr;

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
	Release();
}

void CCameraManager::Initialize() {
	
	m_vPos.x = WINCX >>1;
	m_vPos.y = WINCY >>1;
	m_pTarget = nullptr;


	m_vDistance.x = 0.f;
	m_vDistance.y = 0.f;

    m_bShake = false;
    m_fShakeTimer = 0.f;
    m_fShakePower = 8.f;  
    m_vShakeOffset = { 0.f, 0.f };
}

void CCameraManager::Update(float deletatime) {
	if (m_pTarget) {
		m_LookAt.x = m_pTarget->Get_Info()->fX;
		m_LookAt.y = m_pTarget->Get_Info()->fY;

		Climp();

        
	}
	

    UpdateShake(deletatime);
}

void CCameraManager::Render(HDC hDC) {
	
}

void CCameraManager::Release() {
	m_pTarget = nullptr;
}

void CCameraManager::Climp() {

	
    if (m_LookAt.x < (WINCX >> 1)) {
        m_vPos.x = WINCX >> 1;
    }
    else if (m_LookAt.x > MAPCX - (WINCX >> 1)) {

        m_vPos.x = MAPCX - (WINCX >> 1);
    }
    else {
        m_vDistance.x = m_pTarget->Get_Info()->fX - (WINCX >> 1) + m_vShakeOffset.x;
        m_vPos.x = (WINCX >> 1) + m_vDistance.x;
    }

    if (m_LookAt.y < (WINCY >> 1)) {

        m_vPos.y = WINCY >> 1;
    }
    else if (m_LookAt.y > MAPCY - (WINCY >> 1) ) {
        m_vPos.y = MAPCY - (WINCY >> 1) ;
    }
    else {
      

        m_vDistance.y = m_pTarget->Get_Info()->fY - (WINCY >> 1) + m_vShakeOffset.y;

        m_vPos.y = (WINCY >> 1) + m_vDistance.y ;
    }

	
}

void CCameraManager::UpdateShake(float deltaTime)
{
    if (!m_bShake)
    {
        m_vShakeOffset = { 0.f, 0.f };
        return;
    }

    m_fShakeTimer -= deltaTime;

    if (m_fShakeTimer <= 0.f)
    {
        m_bShake = false;
        m_vShakeOffset = { 0.f, 0.f };
        return;
    }

    float rx = (rand() % 2000 / 1000.f - 1.f);   
    float ry = (rand() % 2000 / 1000.f - 1.f);

    m_vShakeOffset.x = rx * m_fShakePower;
    m_vShakeOffset.y = ry * m_fShakePower;
}

void CCameraManager::Shake(float duration, float power)
{
    m_bShake = true;
    m_fShakeTimer = duration;
    m_fShakePower = power;
}

void CCameraManager::Move_Up()
{
}

void CCameraManager::Move_Down()
{
}
