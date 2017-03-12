// bmp.h : main header file for the BMP application
//

#if !defined(AFX_BMP_H__31974DAF_B391_4C1B_BB78_D4A919CF0A6F__INCLUDED_)
#define AFX_BMP_H__31974DAF_B391_4C1B_BB78_D4A919CF0A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpApp:
// See bmp.cpp for the implementation of this class
//

class CBmpApp : public CWinApp
{
public:
	CBmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBmpApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMP_H__31974DAF_B391_4C1B_BB78_D4A919CF0A6F__INCLUDED_)
