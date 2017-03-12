#if !defined(AFX_BINARYDLG_H__38812D16_6277_4BF9_8A53_3EB65BAC2ADF__INCLUDED_)
#define AFX_BINARYDLG_H__38812D16_6277_4BF9_8A53_3EB65BAC2ADF__INCLUDED_

#include "DIB.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinaryDlg.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CBinaryDlg dialog

class CBinaryDlg : public CDialog
{
// Construction
public:

	CBinaryDlg(CWnd* pParent = NULL);   // standard constructor
   	CDIB m_DIB;
// Dialog Data
	//{{AFX_DATA(CBinaryDlg)
	enum { IDD = IDD_Sanse };
	

	int m_oy;
	int m_ox;
	int m_red;
	int m_green;
	int m_by;
	int m_bx;
	int m_blue;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinaryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBinaryDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnOk();
	//afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINARYDLG_H__38812D16_6277_4BF9_8A53_3EB65BAC2ADF__INCLUDED_)
