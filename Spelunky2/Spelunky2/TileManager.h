#pragma once
#include "define.h"

class CTILE;

class CTileManager
{
private: 
	CTileManager();
	CTileManager& operator=(CTileManager&) = delete;
	CTileManager(const CTileManager& rhs) = delete;
	~CTileManager();

public:
	static CTileManager* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CTileManager;
			
		}
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
	void	Initialize();
	void	Render(HDC hDC);
	void	Update(float deletatime);
	void	Release();

	void	Save_Tile();

	void	Load_Tile();

	void Load_Tile(const TCHAR* pImgKey);

	void	Pick_Tile(Vec2 ptMouse);

	void	Choice_Tile(int iDrawID, int iOption, int iLayer);

	void	Check_Tile();

	vector <CObj*>& GetTile() {
		return m_vecTile;
	}
private:
	static CTileManager* m_pInstance;

	vector<CObj*>	m_vecTile;


	int m_iDrawID;
	int m_iOption;
	int m_iLayer;
};

