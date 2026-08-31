#include <Windows.h>
#include "SceneManager.h"
#include "BmpManager.h"
#include "SoundManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

CSceneManager::CSceneManager() : m_pScene(nullptr), m_ePreScene(SCEND), m_eCurScene(SCEND)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Initialize()
{



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/black.bmp", L"Black");

	m_pScene = new CMenuScene;
	m_pScene->Initialize();
	m_ePreScene = m_eCurScene;
	

	m_falpha = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0x00;
	bf.SourceConstantAlpha = m_falpha;

	m_bFadeOut = false;
	m_bChangeOn = false;
	m_bChangeOff = false;
}

void CSceneManager::Update(float deltatime)
{

	m_pScene->Update(deltatime);

}

void CSceneManager::Late_Update(float deltatime)
{
	m_pScene->Late_Update(deltatime);
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
	if (m_bChangeOn) {
		Fade_Out(hDC);
	}
	if (m_bChangeOff) {
		Fade_In(hDC);
	}
}

void CSceneManager::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneManager::Change_Scene(SCENEID eID) {
	


	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene && m_bFadeOut!= true && m_bChangeOn != true && m_bChangeOff!= true)
	{
		m_bChangeOn = true;
	}
	
	
}

void CSceneManager::Fade_Out(HDC hDC) {
	
	HDC m_Black = CBmpMgr::Get_Instance()->Find_Image(L"Black");

	AlphaBlend(hDC,
		0, 0,
		WINCX, WINCY,
		m_Black,
		0, 0,
		(int)1890,
		(int)1056,
		bf);


	if (m_falpha < 255) {
		m_falpha += 5;
		bf.SourceConstantAlpha = m_falpha;
		if (m_falpha == 255) {
			bf.SourceConstantAlpha = 255;
			m_bFadeOut = true;
		}
	}

	if (m_bFadeOut) {
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SCMENU:
			m_pScene = new CMenuScene;

			
			break;
		case SCREADYSCENE:
			m_pScene = new CReadyScene;

			break;
		case SCMAPEDIT:
			m_pScene = new CMapEditScene;
			break;

		case SCSTAGE2:
			m_pScene = new CStage2;
			break;
		case SCSTAGE3:
			m_pScene = new CStage3;
			break;
		}

		m_pScene->Initialize();
		CSoundManager::Get_Instance()->StopSound(SOUND_BGM);
		m_ePreScene = m_eCurScene;
		m_bFadeOut = false;
		m_bChangeOn = false;
		m_bChangeOff = true;
	}
	

}


void CSceneManager::Fade_In(HDC hDC) {
	HDC m_Black = CBmpMgr::Get_Instance()->Find_Image(L"Black");
	
	AlphaBlend(hDC,
		0, 0,
		WINCX, WINCY,
		m_Black,
		0, 0,
		(int)1890,
		(int)1056,
		bf);

	if (m_falpha <= 255) {
		m_falpha -= 5;
		bf.SourceConstantAlpha = m_falpha;
		if (m_falpha < 0) {
			bf.SourceConstantAlpha = 0;
			m_bChangeOff = false;
		}
	}
}