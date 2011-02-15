// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "GraphS1.h"
#include "Dib.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
    // Set the Dib pointer to NULL so we know if it's been loaded.
    m_pDib = NULL;
}

CDib::~CDib()
{
    // If a Dib has been loaded, delete the memory.
    if( m_pDib != NULL )
    {
        delete [] m_pDib;
    }
}

BOOL CDib::Load( const char* pszFilename )
{
    CFile cf;
    // Attempt to open the Dib file for reading.
    if( !cf.Open( pszFilename, CFile::modeRead ) )
    {
        return( FALSE );
    }
    // Get the size of the file and store in a local variable. Subtract the
    // size of the BITMAPFILEHEADER structure since we won't keep that in memory.
    DWORD dwDibSize;
    dwDibSize =cf.GetLength() - sizeof( BITMAPFILEHEADER );
    // Attempt to allocate the Dib memory.
    unsigned char* pDib;
    pDib = new unsigned char [dwDibSize];
    if( pDib == NULL )
    {
        return( FALSE );
    }
    BITMAPFILEHEADER BFH;
    // Read in the Dib header and data.
    try
    {
        // Did we read in the entire BITMAPFILEHEADER?
        if( cf.Read( &BFH, sizeof( BITMAPFILEHEADER ) )
                != sizeof( BITMAPFILEHEADER ) ||
                // Is the type 'MB'?
                BFH.bfType != 'MB' ||
                // Did we read in the remaining data?
                cf.Read( pDib, dwDibSize ) != dwDibSize )
        {
            // Delete the memory if we had any errors and return FALSE.
            delete [] pDib;
            return( FALSE );
        }
    }
    // If we catch an exception, delete the exception, the temporary Dib memory,
    // and return FALSE.
    catch( CFileException* e )
    {
        e->Delete();
        delete [] pDib;
        return( FALSE );
    }
    // If we got to this point, the Dib has been loaded. If a Dib was already loaded into
    // this class, we must now delete it.
    if( m_pDib != NULL )
    {
        delete m_pDib;
    }
    // Store the local Dib data pointer and Dib size variables in the class member variables.
    m_pDib = pDib;
    m_dwDibSize = dwDibSize;
    // Pointer our BITMAPINFOHEADER and RGBQUAD
    // variables to the correct place in the Dib data.
    m_pBIH = (BITMAPINFOHEADER*) m_pDib;
    m_pPalette =(RGBQUAD*) &m_pDib[sizeof(BITMAPINFOHEADER)];
    // Calculate the number of palette entries.
    m_nPaletteEntries = 1 << m_pBIH->biBitCount;
    if( m_pBIH->biBitCount > 8 )
    {
        m_nPaletteEntries = 0;
    }
    else if( m_pBIH->biClrUsed != 0 )
    {
        m_nPaletteEntries = m_pBIH->biClrUsed;
    }
    // Point m_pDibBits to the actual Dib bits data.
    m_pDibBits =&m_pDib[sizeof(BITMAPINFOHEADER)+
                        m_nPaletteEntries*sizeof(RGBQUAD)];
    // If we have a valid palette, delete it.
    if( m_Palette.GetSafeHandle() != NULL )
    {
        m_Palette.DeleteObject();
    }
    // If there are palette entries, we'll need to create a LOGPALETTE then create the
    // CPalette palette.
    if( m_nPaletteEntries != 0 )
    {
        // Allocate the LOGPALETTE structure.
        LOGPALETTE* pLogPal = (LOGPALETTE*) new char
                              [sizeof(LOGPALETTE)+m_nPaletteEntries*sizeof(PALETTEENTRY)];
        if( pLogPal != NULL ) // Set the LOGPALETTE to version 0x300
        {
            // and store the number of palette entries.
            pLogPal->palVersion = 0x300;
            pLogPal->palNumEntries = m_nPaletteEntries;
            // Store the RGB values into each PALETTEENTRY element.
            for( int i=0; i<m_nPaletteEntries; i++)
            {
                pLogPal->palPalEntry[i].peRed = m_pPalette[i].rgbRed;
            }
            pLogPal->palPalEntry[i].peGreen = m_pPalette[i].rgbGreen;
            pLogPal->palPalEntry[i].peBlue = m_pPalette[i].rgbBlue;
        }
        // Create the CPalette object and delete the LOGPALETTE memory.
        m_Palette.CreatePalette( pLogPal );
        delete [] pLogPal;

    }
    return (TRUE);
}



BOOL CDib::Save( const char* pszFilename )
{
    if( m_pDib == NULL )
    {
        return( FALSE );
    }
    CFile cf;
    // Attempt to create the file.
    if( !cf.Open( pszFilename,CFile::modeCreate | CFile::modeWrite ) )
    {
        return( FALSE );
    }
    // Write the data.
    try
    {
        // First, create a BITMAPFILEHEADER with the correct data.
        BITMAPFILEHEADER BFH;
        memset( &BFH, 0, sizeof( BITMAPFILEHEADER ) );
        BFH.bfType='MB';
        BFH.bfSize=sizeof( BITMAPFILEHEADER ) + m_dwDibSize;
        BFH.bfOffBits = sizeof( BITMAPFILEHEADER ) +sizeof( BITMAPINFOHEADER )+m_nPaletteEntries * sizeof( RGBQUAD );
        // Write the BITMAPFILEHEADER and the Dib data.
        cf.Write( &BFH, sizeof( BITMAPFILEHEADER ) );
        cf.Write( m_pDib, m_dwDibSize );
    }
    // If we get an exception, delete the exception and return FALSE.
    catch( CFileException* e )
    {
        e->Delete();
        return( FALSE );
    }
    return( TRUE );
}



BOOL CDib::Draw( CDC* pDC, int nX, int nY, int nWidth, int nHeight )
{
    // If we have not data we can't draw.
    if( m_pDib == NULL )
    {
        return( FALSE );
    }
    // Check for the default values of -1 in the width and height arguments. If
    // we find -1 in either, we'll set them to the value that's in the BITMAPINFOHEADER.
    if( nWidth == -1 )
    {
        nWidth = m_pBIH->biWidth;
    }
    if( nHeight == -1 )
    {
        nHeight = m_pBIH->biHeight;
    }
    // Use StretchDIBits to draw the Dib.
    StretchDIBits( pDC->m_hDC, nX, nY,nWidth, nHeight,0, 0,
                   m_pBIH->biWidth, m_pBIH->biHeight, m_pDibBits,
                   (BITMAPINFO*) m_pBIH, BI_RGB, SRCCOPY );
    return( TRUE );
}


BOOL CDib::SetPalette( CDC* pDC )
{
    // If we have not data we won't want to set the palette.
    if( m_pDib == NULL )
    {
        return( FALSE );
    }
    // Check to see if we have a palette handle. For Dibs greater than 8 bits, this will be NULL.
    if( m_Palette.GetSafeHandle() == NULL )
    {
        return( TRUE );
    }
    // Select the palette, realize the palette, then finally restore the old palette.
    CPalette* pOldPalette;
    pOldPalette = pDC->SelectPalette( &m_Palette, FALSE );
    pDC->RealizePalette();
    pDC->SelectPalette( pOldPalette, FALSE );
    return( TRUE );
}