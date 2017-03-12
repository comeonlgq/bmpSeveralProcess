// BinaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bmp.h"
#include "BinaryDlg.h"
#include "DIB.h"
#include "MainFrm.h"
#include "bmpDoc.h"
#include "bmpView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinaryDlg dialog


CBinaryDlg::CBinaryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBinaryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBinaryDlg)
    m_blue = 0;
	m_bx = 0;
	m_by = 0;
	m_green = 0;
	m_ox = 0;
	m_oy = 0;
	m_red = 255;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBinaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBinaryDlg)
	DDX_Text(pDX, IDC_B, m_blue);
	DDV_MinMaxInt(pDX, m_blue, 0, 255);
	DDX_Text(pDX, IDC_B_X, m_bx);
	DDX_Text(pDX, IDC_B_Y, m_by);
	DDX_Text(pDX, IDC_G, m_green);
	DDV_MinMaxInt(pDX, m_green, 0, 255);
	DDX_Text(pDX, IDC_O_X, m_ox);
	DDX_Text(pDX, IDC_O_Y, m_oy);
	DDX_Text(pDX, IDC_R, m_red);
	DDV_MinMaxInt(pDX, m_red, 0, 255);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CBinaryDlg, CDialog)
	//{{AFX_MSG_MAP(CBinaryDlg)
      ON_BN_CLICKED(IDOK, OnOk)
//      ON_BN_CLICKED(IDCANCLE, OnCancle)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinaryDlg message handlers

void CBinaryDlg::OnOk()
{
   	UpdateData(TRUE);
	
  CMainFrame*pFrame=(CMainFrame*)AfxGetMainWnd();
  CBmpDoc* pDoc = (CBmpDoc* )pFrame->GetActiveDocument();
  ASSERT_VALID(pDoc);	
  pDoc->m_DIB.ProXiangsu( m_bx,m_by,m_ox,m_oy,m_red,m_blue,m_green);

  pDoc->SetModifiedFlag();
  pDoc->UpdateAllViews(NULL);
  DestroyWindow ( );
}


