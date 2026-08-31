#pragma once
#include "define.h"

class CSoundManager
{
private:
	CSoundManager();
	~CSoundManager();

	CSoundManager& operator=(const CSoundManager&) = delete;
	CSoundManager(const CSoundManager&) = delete;

public:
	static CSoundManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundManager;

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


public:
    void Initialize();
    void Release();

public:
    void PlaySound(const wchar_t* pSoundKey, CHANNELID eID, float fVolume);
    void PlayBGM(const wchar_t* pSoundKey, float fVolume);
    void StopSound(CHANNELID eID);
    void StopAll();
    void SetChannelVolume(CHANNELID eID, float fVolume);
	bool IsSoundFinished(CHANNELID eID);
	bool IsChannelPlaying(CHANNELID eID);
	void PlaySound_IfNotPlaying(const wchar_t* pSoundKey, CHANNELID eID, float fVolume);
private:
    void LoadSoundFile();

private:
    static CSoundManager* m_pInstance;

    std::map<std::wstring, FMOD_SOUND*> m_mapSound;
    FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
    FMOD_SYSTEM* m_pSystem;
};

