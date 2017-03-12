// bmpDoc.h : interface of the CBmpDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "DIB.h"
#include "BinaryDlg.h"	// Added by ClassView
#if !defined(AFX_BMPDOC_H__C150F89C_7262_4FFF_86A4_EA291C4A3FF7__INCLUDED_)
#define AFX_BMPDOC_H__C150F89C_7262_4FFF_86A4_EA291C4A3FF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmpDoc : public CDocument
{
protected: // create from serialization only
	CBmpDoc();
	DECLARE_DYNCREATE(CBmpDoc)

// Attributes
public:
   	double m_dRoom;
	CDIB m_DIB;
	CBinaryDlg Dlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	virtual ~CBmpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpDoc)
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnProcessHflip();
	afx_msg void OnProcessNegative();
	afx_msg void OnProcessOriginal();
	afx_msg void OnProcessRotate();
	afx_msg void OnUpdateProcessVflip(CCmdUI* pCmdUI);
	afx_msg void OnProcessZoomIn();
	afx_msg void OnProcessZoomOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPDOC_H__C150F89C_7262_4FFF_86A4_EA291C4A3FF7__INCLUDED_)
