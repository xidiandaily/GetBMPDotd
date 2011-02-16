// GetBMPDotDlg.h : header file
//

#if !defined(AFX_GETBMPDOTDLG_H__AEDCD4A7_A43B_428C_ABD7_60AB710ADE4F__INCLUDED_)
#define AFX_GETBMPDOTDLG_H__AEDCD4A7_A43B_428C_ABD7_60AB710ADE4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetBMPDotDlg dialog

#include "Dib.h"
#include "ini.h"



class CGetBMPDotDlg : public CDialog
{
// Construction
public:
	CGetBMPDotDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetBMPDotDlg)
	enum { IDD = IDD_GETBMPDOT_DIALOG };
	CString	m_strEDITBit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetBMPDotDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	CStatic m_stc;
	CDib    m_dib;
	unsigned char	m_BinData[128][128];
	unsigned char   m_ByteData[256];
	unsigned char   m_WriteFileByte[2048];
	unsigned int    m_WriteDotAddr[56];           //存放各图片点阵的地址  点阵数据索引

	int     m_PicWidth;
	int     m_PicHeigh;
	unsigned int m_WriteByteCount;//点阵字节长度
	int     m_WriteIndex;
	CString  m_strPath;
	int     m_bmpSum;
    unsigned char m_LastByteCount;
	//的汉字  最多三个字 图标固定为 12 * 36 和 14 * 42 两种大小图标
	int     unicode;        //图像所代表的字的unicode码. by chiyulong 2011-2-16 17:6:22
    int     item_count;     //每个区间所含的item个数


    void WriteDotByteFile();
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetBMPDotDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBTNReadBMP(CString strPathName,int bmpSum);
	afx_msg void OnBTNReadConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef struct
{
    LPCTSTR str;
    int     value;
}FIND_VALUE_T;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBMPDOTDLG_H__AEDCD4A7_A43B_428C_ABD7_60AB710ADE4F__INCLUDED_)
