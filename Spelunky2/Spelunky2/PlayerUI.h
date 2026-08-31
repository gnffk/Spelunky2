#pragma once
#include "UI.h"
#include "Obj.h"
#include "Stage3.h"
#include <string>
class CPlayerUI : public CUI 
{
public:
	CPlayerUI();
	virtual ~CPlayerUI();

public:
	void Initialize() override;
	int Update(float deltatime) override;
	void Late_Update(float deltatime) override;
	void Render(HDC hDC) override;
	void Release() override;


	void Set_Targert(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Scene(CScene* _pScene) { m_pScene = _pScene; }
	
private:
	CObj* m_pTarget;
	CScene* m_pScene;

	HFONT m_hFont;
	std::wstring m_stageName;
};

