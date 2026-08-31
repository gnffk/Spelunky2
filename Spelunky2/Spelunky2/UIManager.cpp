#include "pch.h"
#include "UIManager.h"
#include "BmpManager.h"

CUIManager* CUIManager::m_pInstance = nullptr;

CUIManager::CUIManager()
{
	UIS.reserve(10);
}

CUIManager::~CUIManager()
{
	Release();
}

void CUIManager::Initialize() {
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/AnswerUI.bmp", L"AnswerUI");
	for (auto& iter : UIS) {
		iter->Initialize();
	}
}
void CUIManager::Update(float deltatime) {
	for (auto& iter : UIS) {
		iter->Update(deltatime);
	}
}
void CUIManager::Late_Update(float deltatime) {
	for (auto& iter : UIS) {
		iter->Late_Update(deltatime);
	}
}
void CUIManager::Render(HDC hDC) {
	for (auto& iter : UIS) {
		iter->Render(hDC);
	}
}
void CUIManager::Release() {
	//for_each(UIS.begin(), UIS.end(), Safe_Delete<CUI*>);
	//UIS.clear();


	for (auto& j : UIS)
	{
		if (j->Get_Remain()) {
			UISRemain.push_back(j);
		}
		else {
			Safe_Delete(j);
		}
			
	}
	UIS.clear();
	

	
	for (auto& j : UISRemain)
		{
			if (j->Get_Remain()) {
				UIS.push_back(j);
			}
			
	}
	UISRemain.clear();
	
}

void CUIManager::Add_UI(CUI* _UI) {
	UIS.push_back(_UI);
}