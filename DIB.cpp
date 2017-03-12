// DIB.cpp: implementation of the CDIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bmp.h"
#include "DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define BYTE_PER_LINE(w,c) ((((w)*(c)+31)/32)*4)
#define PALETTESIZE(b) (((b)==8)?256:(((b)==4)?16:0))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDIB::CDIB()
{
    m_lpBits    = NULL;
	m_lpPalette = NULL;
	m_nWidth    =m_nHeight=0;
	m_nBitCount=0;
}

CDIB::~CDIB()
{
     Clear();
}

BOOL CDIB::LoadDib(BYTE *lpDib)
{
   	BYTE *lpBits;
	BITMAPINFOHEADER *pInfo;
	int nWidth,nHeight,nBitCount,nByteWidth;
	RGBQUAD *pPalette;
	unsigned int PaletteSize;

	pInfo=(BITMAPINFOHEADER *)lpDib;
	lpBits=lpDib+sizeof(BITMAPINFOHEADER);

	nWidth=pInfo->biWidth;
	nHeight=pInfo->biHeight;
	nBitCount=pInfo->biBitCount;
	nByteWidth=BYTE_PER_LINE(nWidth,nBitCount);

	switch(nBitCount)
	{
	case 24:
			if(m_lpBits)
				delete[] m_lpBits;
			if(m_lpPalette)
				delete[] m_lpPalette;
			m_lpPalette=NULL;

			m_lpBits=new BYTE[nByteWidth*nHeight];

			memcpy(m_lpBits,lpBits,nByteWidth*nHeight);
			break;

	case 8:
	case 4:
			if(m_lpBits)
				delete[] m_lpBits;
			if(m_lpPalette)
				delete[] m_lpPalette;

			PaletteSize=(1<<pInfo->biBitCount);

			if(pInfo->biClrUsed!=0 && pInfo->biClrUsed<PaletteSize)
					PaletteSize=pInfo->biClrUsed;

			pPalette=(RGBQUAD *)lpBits;
			lpBits+=sizeof(RGBQUAD)*PaletteSize;

			m_lpPalette=new BYTE[sizeof(RGBQUAD)*PaletteSize];

			memcpy(m_lpPalette,pPalette,sizeof(RGBQUAD)*PaletteSize);

			m_lpBits=new BYTE[nByteWidth *nHeight];
			memcpy(m_lpBits,lpBits,nByteWidth *nHeight);
			break;
	default:
		return FALSE;

	
	}
		m_nBitCount=nBitCount;
		m_nWidth=nWidth;
		m_nHeight=nHeight;

		return TRUE;
}

BOOL CDIB::SaveToDib(BYTE *lpDib)
{
   	if(m_lpBits==NULL)
		return FALSE;
	BYTE *p=lpDib;
	int nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);
	BITMAPINFOHEADER bmi;
	bmi.biSize=sizeof(BITMAPINFOHEADER);
	bmi.biWidth=m_nWidth;
	bmi.biWidth=m_nHeight;
	bmi.biPlanes=1;
	bmi.biBitCount=m_nBitCount;
	bmi.biCompression=BI_RGB;
	bmi.biSizeImage=0;
	bmi.biXPelsPerMeter=0;
	bmi.biYPelsPerMeter=0;
	bmi.biClrUsed=0;
	bmi.biClrImportant=0;
	memcpy(p,&bmi,sizeof(BITMAPINFOHEADER));
	p+=sizeof(BITMAPINFOHEADER);
	if(m_nBitCount!=24)
	{
		memcpy(p,m_lpPalette,PALETTESIZE(m_nBitCount)* sizeof(RGBQUAD));
     	p+=PALETTESIZE(m_nBitCount)*sizeof(RGBQUAD);
	}
	memcpy(p,m_lpBits,nByteWidth*m_nHeight);
	return TRUE;
}

void CDIB::Clear()
{
   if(m_lpBits)
		delete[] m_lpPalette;
	m_lpBits=NULL;
	if(m_lpPalette)
       delete[] m_lpPalette;  
	m_lpPalette=NULL;
	m_nWidth=m_nHeight=0;
	m_nBitCount=0;
}

BOOL CDIB::IsEmpty()
{
  return  !m_lpBits;
}

int CDIB::GetBitCount()
{
    return m_nBitCount;
}

int CDIB::GetHeight()
{
  return m_nHeight;
}

int CDIB::GetWidth()
{
    return m_nWidth;
}

BOOL CDIB::LoadFromFile(CFile *pf)
{
    BYTE *lpBitmap,*lpDib;
	int nLen;
	nLen=pf->GetLength();

	lpBitmap=new BYTE[nLen];
	pf->Read(lpBitmap,nLen);

	if(lpBitmap[0]!='B'&&lpBitmap[1]!='M')
	{

		AfxMessageBox("非位图文件");
		delete[] lpBitmap;
		return FALSE;
	}

	lpDib=lpBitmap+sizeof(BITMAPFILEHEADER);

	BOOL ret=LoadDib(lpDib);
	 delete[] lpBitmap;

	 return ret;
}

BOOL CDIB::LoadFromFile(LPCTSTR filename)
{
   CFile f;
	if(!f.Open(filename,CFile::modeRead))
		return FALSE;
	BOOL r=LoadFromFile(&f);
	f.Close();
	return r;
}

BOOL CDIB::SaveToFile(CFile *pf)
{
   if(m_lpBits==NULL)
		return FALSE;
    int nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);

	BITMAPFILEHEADER bm;
	bm.bfType='M'*256+'B';
	bm.bfSize=nByteWidth*m_nHeight;
	bm.bfReserved1=0;
	bm.bfReserved2=0;
	bm.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	if(m_nBitCount!=24)
		bm.bfOffBits += PALETTESIZE(m_nBitCount)*sizeof(RGBQUAD);

	pf->Write(&bm,sizeof(BITMAPFILEHEADER));

	BITMAPINFOHEADER bmi;
	bmi.biSize=sizeof(BITMAPINFOHEADER);
    bmi.biWidth=m_nWidth;
	bmi.biHeight=m_nHeight;
	bmi.biPlanes=1;
	bmi.biBitCount=m_nBitCount;
	bmi.biCompression=BI_RGB;
	bmi.biSizeImage=0;
	bmi.biXPelsPerMeter=0;
	bmi.biYPelsPerMeter=0;
	bmi.biClrUsed=0;
	bmi.biClrImportant=0;
	pf->Write(&bmi,sizeof BITMAPINFOHEADER);
	if(m_nBitCount!=24)
	   pf->Write(m_lpBits,nByteWidth*m_nHeight);
     return TRUE; 
}

BOOL CDIB::SaveToFile(LPCTSTR fn)
{
    CFile f;
	if(!f.Open(fn,CFile::modeCreate|CFile::modeWrite))
       return FALSE;
	BOOL r=SaveToFile(&f);
		f.Close();
	return r;
}

BOOL CDIB::Copy()
{
   if(m_lpBits==0)
		return FALSE;
	 if(!OpenClipboard(NULL))
		return FALSE;
     EmptyClipboard();
	 HGLOBAL hMem;
	 BYTE *lpDib;
	 int nLen=sizeof(BITMAPINFOHEADER)+BYTE_PER_LINE(m_nWidth,m_nBitCount)*m_nHeight;
	 if(m_nBitCount!=24)
		 nLen+=PALETTESIZE(m_nBitCount)*sizeof(RGBQUAD);
	 hMem=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,nLen);
	 lpDib=(BYTE *)GlobalLock(hMem);
	 SaveToDib(lpDib);
	 GlobalUnlock(hMem);
	 SetClipboardData(CF_DIB,hMem);
	 CloseClipboard();
	 return TRUE;
}

BOOL CDIB::Grey()
{
   	if(!m_lpBits)
		return FALSE;
	int y,x,nByteWidth,palsize,grey;
	BYTE *p;
	if(m_nBitCount==24)
	{
		nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);
		for(y=0;y<m_nHeight;y++)
			for(x=0;x<m_nWidth;x++)
			{
				p=m_lpBits+nByteWidth*y+x*3;
				grey=(BYTE)(0.299*p[2]+0.587*p[1]+0.114*p[0]);
				p[0]=grey;
                p[1]=grey;
				p[2]=grey;
			}
	}
	else
	{
		 palsize=PALETTESIZE(m_nBitCount);
		 for(x=0;x<palsize;x++)
		 {
			 p=m_lpPalette+x*4;
			 grey=(BYTE)(0.299*p[2]+0.587*p[1]+0.114*p[0]);
			 p[0]=grey;
             p[1]=grey;
		     p[2]=grey;
		 }
	}
	return TRUE; 
}

BOOL CDIB::Paste()
{
    HGLOBAL hMem;
	BYTE *lpDib;
	if(!OpenClipboard(NULL))
		return FALSE;
	if(!(hMem=GetClipboardData(CF_DIB)))
        return FALSE;
	lpDib=(BYTE*)GlobalLock(hMem);
	LoadDib(lpDib);
    CloseClipboard();
	return TRUE; 
}

BOOL CDIB::HFlip()
{
  if(!m_lpBits)
		return FALSE;
    int y,x,nByteWidth,temp;
	BYTE *p1,*p2;
	nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);
	switch(m_nBitCount)
	{
	    case 24:
			for(y=0;y<m_nHeight;y++)
				for(x=0;x<m_nWidth/2;x++)
				{
                  p1=m_lpBits+nByteWidth*y+x*3;
			      p2=m_lpBits+nByteWidth*y+(m_nWidth-x-1)*3;
				  temp=p1[0];
				  p1[0]=p2[0];
				  p2[0]=temp;
				  temp=p1[1];
				  p1[1]=p2[1];
				  p2[1]=temp;
				  temp=p1[2];
				  p1[2]=p2[2];
				  p2[2]=temp;
				}
				break;
		case 8:
			for(y=0;y<m_nHeight;y++)
				for(x=0;x<m_nWidth/2;x++)
				{
                  p1=m_lpBits+nByteWidth*y+x;
			      p2=m_lpBits+nByteWidth*y+(m_nWidth-x-1);
				  temp=*p1;
				  *p1=*p2;
				  *p2=temp;
				}
				break;
		case 4:
			return FALSE;
	}
	return TRUE;    
}

BOOL CDIB::VFlip()
{
    if(!m_lpBits)
		return FALSE;
    int y,nByteWidth;
	BYTE *p1,*p2,*pm;
	nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);
	pm=new BYTE[nByteWidth];
	for(y=0;y<m_nHeight/2;y++)
	{
	   p1=m_lpBits+nByteWidth*y;
	   p2=m_lpBits+nByteWidth*(m_nHeight-y-1);
	   memcpy(pm,p1,nByteWidth);
       memcpy(p1,p2,nByteWidth);
	   memcpy(p2,pm,nByteWidth);
	}
	delete[] pm;
	return TRUE;  
}

BOOL CDIB::Rotate()
{
   if(!m_lpBits)
		return FALSE;
	BYTE *pbits,*p1,*p2,*pa,*pb,*pa1,*pb1;
	int w2,h2,bw2,bw1,x,y;
	w2=m_nHeight;
	h2=m_nWidth;
	bw1=BYTE_PER_LINE(m_nWidth,m_nBitCount);
	bw2=BYTE_PER_LINE(w2,m_nBitCount);
    pbits=new BYTE[bw2*h2];
	switch(m_nBitCount)
	{
         case 24:
			for(y=0;y<m_nHeight;y++)
				for(x=0;x<m_nWidth;x++)
				{
                  p1=m_lpBits+bw1*y+x*3;
			      p2=m_lpBits+bw2*(h2-x-1)+y*3;
				  p2[0]=p1[0];
				  p2[1]=p1[1];
				  p2[2]=p1[2];
				}
				break;
		case 8:
			for(y=0;y<m_nHeight;y++)
				for(x=0;x<m_nWidth;x++)
				{
                  p1=m_lpBits+bw1*y+x;
			      p2=m_lpBits+bw2*(h2-x-1)+y;
				  p2[0]=p1[0];
				}
				break;
		case 4:
			 for(y=0;y<m_nHeight;y+=2)
				for(x=0;x<m_nWidth;x+=2)
				{
                  pa=m_lpBits+bw1*y+x/2;
			      pb=pa+bw1;
				  pb1=pbits+bw2*(h2-x-1)+y/2;
			      pa1=pb1-bw2;
				  if(pa1>=pbits)
					  *pa1=((*pa&0x0f)<<4)|(*pb&0x0f);
				  *pb1=(*pa&0xf0)|((*pb&0xf0)>>4);
				}
				break;
	}
	delete[] m_lpBits;
	m_lpBits=pbits;
	m_nWidth=w2;
	m_nHeight=h2;
	return TRUE;
}

BOOL CDIB::Negative()
{
  if(!m_lpBits)
		return FALSE;
	BYTE *p;
	int x,y,nByteWidth,palsize;
	if(m_nBitCount==24)
	{
         nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);
		 for(y=0;y<m_nHeight;y++)
			 for(x=0;x<m_nWidth;x++)
			 {
				 p=m_lpBits+nByteWidth*y+x*3;
                 p[0]=~p[0];
				 p[1]=~p[1];
				 p[2]=~p[2];
			 }
	}
	else
	{
		palsize=PALETTESIZE(m_nBitCount);
		for(x=0;x<palsize;x++)
		{
			p=m_lpPalette+x*4;
            p[0]=~p[0];
		    p[1]=~p[1];
		    p[2]=~p[2];
		}
	}

	return TRUE;
}

int CDIB::Stretch(HDC hDC, int XDest, int YDest, int  nDestWidth,  int nDestHeight , int XSrc , int YSrc, int nSrcWidth,int nSrcHeight, UINT  iUsage,  DWORD dwRop)
{
   BITMAPINFO *pbmi;
	int palsize;
	palsize=PALETTESIZE(m_nBitCount);
	pbmi=(BITMAPINFO *  )new BYTE[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*palsize];
	
	memcpy(pbmi->bmiColors,m_lpPalette,sizeof(RGBQUAD)*palsize);
	pbmi->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth=m_nWidth;
	pbmi->bmiHeader.biHeight=m_nHeight;

	pbmi->bmiHeader.biPlanes=1;
	pbmi->bmiHeader.biBitCount=m_nBitCount;
	pbmi->bmiHeader.biCompression=BI_RGB;

	pbmi->bmiHeader.biSizeImage=0;
	pbmi->bmiHeader.biXPelsPerMeter=0;
	pbmi->bmiHeader.biYPelsPerMeter=0;

	pbmi->bmiHeader.biClrUsed=0;
	pbmi->bmiHeader.biClrImportant=0;



	SetStretchBltMode(hDC,COLORONCOLOR);
	
	int ret=StretchDIBits( hDC, XDest, YDest , nDestWidth,
				   nDestHeight, XSrc, YSrc, nSrcWidth,
				   nSrcHeight,m_lpBits,pbmi, iUsage, dwRop);
	delete[] pbmi;
	return ret;

}

BOOL CDIB::ProXiangsu(int bx, int by, int ox, int oy, int m_red, int m_blue, int m_green)
{
     
	if(!m_lpBits)
		return FALSE;

	int nByteWidth;
	int x,y;
	BYTE * p;
	nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);

		for(y=by;y<oy;y++)
		{

			for(x=bx;x<ox;x++)
			{
			p=m_lpBits+nByteWidth*y+x*3;
			p[0]=m_blue;
			p[1]=m_green;
			p[2]=m_red;
			}
		}
		int q=0;
	return	TRUE ;
}
