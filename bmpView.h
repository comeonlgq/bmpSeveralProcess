// bmpView.h : interface of the CBmpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPVIEW_H__7FCEEE76_F990_4F67_B9A6_609E4042F590__INCLUDED_)
#define AFX_BMPVIEW_H__7FCEEE76_F990_4F67_B9A6_609E4042F590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"DIB.h"

class CBmpView : public CScrollView
{
protected: // create from serialization only
	CBmpView();
	DECLARE_DYNCREATE(CBmpView)

// Attributes
public:
	CBmpDoc* GetDocument();
     CDIB m_DIB;
	 	void OnInitialUpdate();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CBmpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CBmpView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in bmpView.cpp
inline CBmpDoc* CBmpView::GetDocument()
   { return (CBmpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPVIEW_H__7FCEEE76_F990_4F67_B9A6_609E4042F590__INCLUDED_)
