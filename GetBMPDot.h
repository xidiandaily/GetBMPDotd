// GetBMPDot.h : main header file for the GETBMPDOT application
//

#if !defined(AFX_GETBMPDOT_H__B45B4EE4_33B7_4746_8885_139DF4AF20FD__INCLUDED_)
#define AFX_GETBMPDOT_H__B45B4EE4_33B7_4746_8885_139DF4AF20FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetBMPDotApp:
// See GetBMPDot.cpp for the implementation of this class
//

class CGetBMPDotApp : public CWinApp
{
public:
	CGetBMPDotApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetBMPDotApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetBMPDotApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBMPDOT_H__B45B4EE4_33B7_4746_8885_139DF4AF20FD__INCLUDED_)
