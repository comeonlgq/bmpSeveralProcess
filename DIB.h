// DIB.h: interface for the CDIB class.
//
//////////////////////////////////////////////////////////////////////



#ifndef _DIB_H
#define _DIB_H
#include <windows.h>

class CDIB  
{
public:
	BOOL ProXiangsu( int bx,int by,int ox,int oy,int m_red,int m_blue,int m_green);
	int Stretch(HDC,int,int,int,int,int,int,int,int,UINT,DWORD);
	BOOL Negative();
	BOOL Rotate();
	BOOL VFlip();
	BOOL HFlip();
	BOOL Paste();
	BOOL Grey();
	BOOL Copy();
	BOOL SaveToFile(LPCTSTR fn);
	BOOL SaveToFile(CFile *pf);
	BOOL LoadFromFile(LPCTSTR filename);
	BOOL LoadFromFile(CFile *pf);
	int GetWidth();
	int GetHeight();
	int GetBitCount();
	BOOL IsEmpty();
	void Clear();
	CDIB();
	virtual ~CDIB();

private:
	BOOL SaveToDib(BYTE* lpDib);
	BOOL LoadDib(BYTE*lpDib);
	BYTE* m_lpPalette;
	int m_nBitCount;
	int m_nHeight;
	int m_nWidth;
	BYTE * m_lpBits;
};

#endif // !defined(AFX_DIB_H__D4519631_D3A6_4D6F_B66E_A7253938E812__INCLUDED_)
