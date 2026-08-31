#pragma once

#include "define.h"

class CKeyManager
{
private:
	CKeyManager();
	CKeyManager& operator=(CKeyManager&) = delete;
	CKeyManager(const CKeyManager& rhs) = delete;
	~CKeyManager();

public:
	void		Initialize();
	void		Update(float deltatime);

	bool		Key_Pressing(int _iKey);

	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);
	void		Release();


public:
	static CKeyManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager;

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
	static CKeyManager* m_pInstance;
	bool		m_bKeyState[VK_MAX];
};

