#pragma once
#include "Obj.h"

class CObjManager
{
private:
	CObjManager();
	CObjManager& operator=(CObjManager&) = delete;
	CObjManager(const CObjManager& rhs) = delete;
	~CObjManager();


public:
	CObj* Get_Target(OBJID eID, CObj* pObj);
	list<CObj*> Get_TypeObj(OBJID eID) {
		return m_ObjList[eID];
	}
public:

	void	AddObject(OBJID eID, CObj* pObj = nullptr);
	void	Update(float deltatime);
	void	Late_Update(float deltatime);
	void	Render(HDC hDC);
	void	Release();

	void	Remain_Not();
	void	Delete_ID(OBJID eID);

public:
	static CObjManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjManager;

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
	static CObjManager* m_pInstance;
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*> m_ObjRemainList[OBJ_END];
	list<CObj*>  m_RenderList[RENDER_END];
	
};

