// bmpView.cpp : implementation of the CBmpView class
//

#include "stdafx.h"
#include "bmp.h"

#include "bmpDoc.h"
#include "bmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpView

IMPLEMENT_DYNCREATE(CBmpView, CScrollView)

BEGIN_MESSAGE_MAP(CBmpView, CScrollView)
	//{{AFX_MSG_MAP(CBmpView)
		ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpView construction/destruction

CBmpView::CBmpView()
{
	// TODO: add construction code here

}

CBmpView::~CBmpView()
{
}

BOOL CBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpView drawing

void CBmpView::OnDraw(CDC* pDC)
{
	CBmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
		int w,h;
	w=int(pDoc->m_DIB.GetWidth()*pDoc->m_dRoom);
	h=int(pDoc->m_DIB.GetHeight()*pDoc->m_dRoom);
	pDoc->m_DIB.Stretch(pDC->m_hDC,0,0,w,h,0,0,pDoc->m_DIB.GetWidth(),pDoc->m_DIB.GetHeight(),DIB_RGB_COLORS,SRCCOPY);

}

/////////////////////////////////////////////////////////////////////////////
// CBmpView printing

BOOL CBmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmpView diagnostics

#ifdef _DEBUG
void CBmpView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBmpView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CBmpDoc* CBmpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpDoc)));
	return (CBmpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpView message handlers

void CBmpView::OnInitialUpdate()
{
   CScrollView::OnInitialUpdate();

 CSize sizeTotal(1000,1600);
 SetScrollSizes(MM_TEXT,sizeTotal);
}
