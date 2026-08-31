#include "pch.h"
#include "KeyManager.h"
#include "SoundManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyManager::~CKeyManager()
{
	Release();
}

void CKeyManager::Initialize() {
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

void CKeyManager::Update(float deltatime)
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}


bool CKeyManager::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000) {
		m_bKeyState[_iKey] = true;
		return true;
	}

	else {
		return false;
	}

}

// 이전에는 누른 적이 없고, 현재 눌렀을 경우
bool CKeyManager::Key_Down(int _iKey)
{

	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];

		return true;
	}

	return false;
}

// 이전에는 누른 적이 있고, 현재 누르지 않은 경우
bool CKeyManager::Key_Up(int _iKey)
{
	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];

		return true;
	}

	return false;
}

void CKeyManager::Release()
{
}
