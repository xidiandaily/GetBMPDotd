// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__8C7D2D8C_E4B9_483C_95E7_BEC8E3D6AF67__INCLUDED_)
#define AFX_DIB_H__8C7D2D8C_E4B9_483C_95E7_BEC8E3D6AF67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDib : public CObject  
{
public:
	CDib();
	~CDib();
	BOOL Load( const char * );
	BOOL Save( const char * );
	BOOL AttachMapFile(const char* pszFilename, BOOL bShare);
	BOOL Draw( CDC *, int nX = 0, int nY = 0, int nWidth = -1, int nHeight = -1 );
	BOOL SetPalette( CDC * );
private:
	CPalette m_Palette;
	unsigned char *m_pDib, *m_pDibBits;
	DWORD m_dwDibSize;
	BITMAPINFOHEADER *m_pBIH;
	RGBQUAD *m_pPalette;
	int m_nPaletteEntries;

};

#endif // !defined(AFX_DIB_H__8C7D2D8C_E4B9_483C_95E7_BEC8E3D6AF67__INCLUDED_)
