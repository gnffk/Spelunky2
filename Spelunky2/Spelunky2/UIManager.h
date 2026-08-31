#pragma once

#include "UI.h"

class CUIManager
{
private:
	CUIManager();
	CUIManager& operator= (CUIManager&) = delete;
	CUIManager(const CUIManager& rhs) = delete;
	~CUIManager();

public:
	static CUIManager* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CUIManager;
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

	void		Add_UI	(CUI* _UI);

	vector<CUI*>& Get_UI() {
		return UIS;
	}
	



private:
	static CUIManager* m_pInstance;

	vector<CUI*> UIS;
	vector<CUI*> UISRemain;
		
};

