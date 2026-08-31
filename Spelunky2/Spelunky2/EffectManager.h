#pragma once
#include "Obj.h"

class CEffectManager
{
private:
	CEffectManager() {};
	CEffectManager& operator= (CEffectManager&) = delete;
	CEffectManager(const CEffectManager& rhs) = delete;
	~CEffectManager();

public:
	static CEffectManager* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CEffectManager;
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

	void		Paricle_Effect(Vec2 pos, int type);

	void		ADD_Effect(Vec2 pos, int type);

	vector <CObj*>& GetParticle() {
		return m_vecParticle;
	}
private:
	static CEffectManager* m_pInstance;


private:
	vector<CObj*> m_vecParticle;
	vector<CObj*> m_vecEffect;


};

