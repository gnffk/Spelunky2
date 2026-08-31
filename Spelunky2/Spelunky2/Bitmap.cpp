#include "pch.h"
#include "Bitmap.h"

CBitmap::CBitmap()
{
}

CBitmap::~CBitmap()
{
	Release();
}

void CBitmap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개 변수로 전달한 DC와 호환되는 DC를 생성하여 반환

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL, 
									pFilePath, 
									IMAGE_BITMAP,	
									0, 0,	
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
