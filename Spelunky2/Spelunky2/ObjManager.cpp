#include "pch.h"
#include "ObjManager.h"


CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager()
{
}

CObjManager::~CObjManager()
{
	Release();
}



CObj* CObjManager::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	float	fDistance = 0.f;

	for (auto& Dst : m_ObjList[eID])
	{
		if (Dst->Get_Dead())
			continue;

		float	fWidth = Dst->Get_Info()->fX - pObj->Get_Info()->fX;
		float	fHeight = Dst->Get_Info()->fY - pObj->Get_Info()->fY;

		// 현재 프레임의 거리 비교 값
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Dst;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjManager::AddObject(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjManager::Update(float deltatime)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update(deltatime);

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}

		}
	}
}

void CObjManager::Late_Update(float deltatime)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Late_Update(deltatime);

			if (m_ObjList[i].empty())
				break;

			RENDERID   eID = pObj->Get_RenderID();
			m_RenderList[eID].push_back(pObj);

		}
	}

}





void CObjManager::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info()->fY < pSrc->Get_Info()->fY;
			});

		for (auto& pObj : m_RenderList[i])
		{
			pObj->Render(hDC);
		}

		m_RenderList[i].clear();
	}
}


void CObjManager::Release()
{
	/*for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}*/

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto& j : m_ObjList[i])
		{
			if (j->Get_Remain()) {
				m_ObjRemainList[i].push_back(j);
			}
			else {
				Safe_Delete(j);
			}
			
		}
		m_ObjList[i].clear();
	}

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto& j : m_ObjRemainList[i]) {
			m_ObjList[i].push_back(j);
		}
		m_ObjRemainList[i].clear();
	}
}

void CObjManager::Remain_Not()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		/*for_each(m_ObjList[i].begin(), m_ObjList[i].end(), [&m_ObjList](CObj* i) {
				
			
		});*/
		
	}

}

void CObjManager::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}
