#pragma once
#include "pch.h"
#include "MenuScene.h"
#include "MapEditScene.h"
#include "ReadyScene.h"
#include "Stage2.h"
#include "Stage3.h"





class CSceneManager
{
private:
	CSceneManager();
	CSceneManager& operator= (CSceneManager&) = delete;
	CSceneManager(const CSceneManager& rhs) = delete;
	~CSceneManager();

public:
	static CSceneManager* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CSceneManager;
		}
		return m_pInstance;
	}
	static void Destroy_Instance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}

public:
	void		Initialize();
	void		Update(float deltatime);
	void		Late_Update(float deltatime);
	void		Render(HDC hDC);
	void		Release();

	void		Change_Scene(SCENEID eID);

	void		Fade_Out(HDC hDC);

	void		Fade_In(HDC hDC);



	SCENEID     GetCurScene() { return m_eCurScene; }
private:
	static CSceneManager* m_pInstance;

	CScene* m_pScene;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;

public:
	BLENDFUNCTION bf{};
	bool		m_bChangeOn;
	bool		m_bChangeOff;
	bool		m_bFadeOut;
	float		m_falpha;


};

