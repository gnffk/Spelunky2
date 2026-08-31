#pragma once

class CObj;


class CCameraManager
{
private:
	CCameraManager();
	CCameraManager& operator=(CCameraManager&) = delete;
	CCameraManager(const CCameraManager& rhs) = delete;
	~CCameraManager();

public:
	
	void		Initialize();
	void		Render(HDC hDC);
	void		Update(float deltatime);
	void		Release();

	void		Climp();

	void UpdateShake(float deltaTime);

	void Shake(float duration, float power);

public:
	Vec2		GetCameraPos() { return m_vPos; }
	void		SetCameraPos(Vec2 _pos) { m_vPos = _pos; }

	void		SetCameraOffset(Vec2 _Offset) { m_vPos.y += _Offset.y; }

	Vec2		GetDistance() { return m_vDistance; }

	CObj*		GetTarget() { return m_pTarget; }
	void		SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

	void		Move_Up();
	void		Move_Down();
public:
	static CCameraManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCameraManager;

		return m_pInstance;
	}

	static void		Destroy_Instacne()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CCameraManager* m_pInstance;
	
	CObj* m_pTarget;
	Vec2  m_vPos;
	Vec2  m_vPurPos;
	Vec2  m_vDistance;
	Vec2  m_LookAt;

	bool  m_bShake = false;
	float m_fShakeTimer ;
	float m_fShakePower; 
	Vec2 m_vShakeOffset ;
};

