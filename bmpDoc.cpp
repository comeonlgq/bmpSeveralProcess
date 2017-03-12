// bmpDoc.cpp : implementation of the CBmpDoc class
//

#include "stdafx.h"
#include "bmp.h"

#include "winnt.h"
#include "bmpDoc.h"

#include "dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpDoc

IMPLEMENT_DYNCREATE(CBmpDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpDoc, CDocument)
	//{{AFX_MSG_MAP(CBmpDoc)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_PROCESS_HFLIP, OnProcessHflip)
	ON_COMMAND(ID_PROCESS_NEGATIVE, OnProcessNegative)
	ON_COMMAND(ID_PROCESS_ORIGINAL, OnProcessOriginal)
	ON_COMMAND(ID_PROCESS_ROTATE, OnProcessRotate)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_VFLIP, OnUpdateProcessVflip)
	ON_COMMAND(ID_PROCESS_ZOOM_IN, OnProcessZoomIn)
	ON_COMMAND(ID_PROCESS_ZOOM_OUT, OnProcessZoomOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpDoc construction/destruction

CBmpDoc::CBmpDoc()
{
	// TODO: add one-time construction code here
    m_dRoom=1;
}

CBmpDoc::~CBmpDoc()
{
}

BOOL CBmpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmpDoc serialization

void CBmpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
        m_DIB.SaveToFile(ar.GetFile());
	}
	else
	{
		// TODO: add loading code here
       	if(!m_DIB.LoadFromFile(ar.GetFile()))
			AfxMessageBox("´ò¿ªÎÄµµÊ§°Ü");
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBmpDoc diagnostics

#ifdef _DEBUG
void CBmpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpDoc commands

void CBmpDoc::OnEditCopy() 
{
	// TODO: Add your command handler code here
    m_DIB.Copy ();
	UpdateAllViews(NULL);	
}

void CBmpDoc::OnEditPaste() 
{
	// TODO: Add your command handler code here
	if (m_DIB.Paste())
		SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CBmpDoc::OnProcessHflip() 
{
	// TODO: Add your command handler code here
	m_DIB.HFlip();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CBmpDoc::OnProcessNegative() 
{
	// TODO: Add your command handler code here
	m_DIB.Negative();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CBmpDoc::OnProcessOriginal() 
{
	// TODO: Add your command handler code here
	m_DIB.Negative();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CBmpDoc::OnProcessRotate() 
{
	// TODO: Add your command handler code here
	
}

void CBmpDoc::OnUpdateProcessVflip(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CBmpDoc::OnProcessZoomIn() 
{
	// TODO: Add your command handler code here
    m_dRoom=m_dRoom*0.8;
	SetModifiedFlag();
	UpdateAllViews(NULL);	
}

void CBmpDoc::OnProcessZoomOut() 
{
	// TODO: Add your command handler code here
	m_dRoom=m_dRoom*1.2;
	SetModifiedFlag();
	UpdateAllViews(NULL);
}
