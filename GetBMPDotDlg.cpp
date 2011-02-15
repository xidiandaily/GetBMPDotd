// GetBMPDotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetBMPDot.h"
#include "GetBMPDotDlg.h"

#include <math.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetBMPDotDlg dialog

CGetBMPDotDlg::CGetBMPDotDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CGetBMPDotDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CGetBMPDotDlg)
    m_strEDITBit = _T("");
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetBMPDotDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CGetBMPDotDlg)
    DDX_Text(pDX, IDC_EDITBITDot, m_strEDITBit);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetBMPDotDlg, CDialog)
    //{{AFX_MSG_MAP(CGetBMPDotDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTNReadBMP, OnBTNReadBMP)
    ON_BN_CLICKED(IDC_BTNReadCon, OnBTNReadConfig)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetBMPDotDlg message handlers

BOOL CGetBMPDotDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    m_PicWidth = 20;
    m_PicHeigh = 20;
    m_WriteByteCount = 0;
    m_WriteIndex = 0;
    m_bmpSum = 0;
    m_LastByteCount = 0;
//	m_stc.Create("��̬�ı�",WS_CHILD | WS_VISIBLE | SS_SIMPLE,CRect(50,50,200,200),this,123);
//	m_stc.ShowWindow(SW_SHOWNORMAL);


    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetBMPDotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetBMPDotDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetBMPDotDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

int btoi(char* binary_c)
{
    int blength = strlen(binary_c);//����������ַ����ĳ���
    int i = 0;
    int decimal = 0;

    for(i = 0; i < blength; i++)
    {
        int number = binary_c[i] - '0';
        if(number == 0 || number == 1)//�ж�������������Ƿ�Ϊ����������
        {
            //����ʹ����λ������������a������һλ��Ȼ���������һλ���һ������b����ô�����ֵ�ʮ����ֵΪa*2 + b
            decimal = decimal * 2 + number;
        }
        else
        {
            //MessageBox(hwnd, "���������������", "����", MB_OK);
            break;
        }
    }
    return decimal;
}
void CGetBMPDotDlg::OnBTNReadBMP(CString strPathFileName, int bmpIndex)
{
    if (!m_dib.Load(strPathFileName))
    {
        strPathFileName += "m_dib.Load() ����!";
        MessageBox(strPathFileName);
        return;
    }



    CBitmap bitmap; //����һλͼ��

    bitmap.m_hObject = LoadImage(AfxGetInstanceHandle(), strPathFileName ,	//ʹ��λͼ�ľ��ָ�����ͼ��
                                 IMAGE_BITMAP,0,0,
                                 LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);

    if (NULL == bitmap.m_hObject)
    {
        strPathFileName+="  ��ȡͼƬLoadImage����";
        MessageBox(strPathFileName);
        return;
    }

    COLORREF   bmp_color;
    BYTE   red;
    BYTE   green;
    BYTE   blue;

    BITMAP bm;
    int width = 0;
    int height = 0;
    int m = 0;//��
    int n = 0;//��

    bitmap.GetBitmap(&bm);

    CDC dcMem;
    dcMem.CreateCompatibleDC(0);
    dcMem.SelectObject(&bitmap);

    width = bm.bmWidth;                 //BMP ��
    height = bm.bmHeight;

    //��ʾ BMP ͼ��
    CClientDC dc(this);
    m_dib.SetPalette(&dc);
    m_dib.Draw(&dc,m_PicWidth,m_PicHeigh,bm.bmWidth,bm.bmHeight);
    m_strEDITBit += strPathFileName;
    m_strEDITBit += "\r\n�����:\r\n";

    m_PicWidth += (width + 10);
    if (m_PicWidth >= 490)
    {
        m_PicWidth = 20 ;
        m_PicHeigh += 20;
    }

    /*
        if (!((width == 11 && height == 12) || (width == 42 && height == 14)))
        {
            MessageBox("��ȡͼƬ��С����Ϊ 12*36 �� 14*42!");
            return;
        }
    */

    for(m=0; m<height; m++)//    ��ɨ��
    {
        for(n=0; n<width; n++)//
        {
            bmp_color   = dcMem.GetPixel(n, m);  //GetPixel( int x, int y ) ��ɨ��
            red     =   GetRValue(bmp_color);
            green   =   GetGValue(bmp_color);
            blue    =   GetBValue(bmp_color);

            //��ֵ��
            int gray = int(red*0.3+green*0.59+blue*0.11);
            int r = 0;
            if(gray > 128)
            {
                m_strEDITBit +="0";
                r = 0;
            }
            else
            {
                m_strEDITBit +="1";
                r = 1;
            }
            m_BinData[m][n] = r;
        }
        m_strEDITBit +="\r\n";
    }

    m_strEDITBit +="ת����õ��Ĳ���:\r\n";
//    m_strEDITBit +="\r\n";
    //8λתһ�ֽ�
    unsigned char tc[8];//��ʱ��һ���ֽ�����
    int s = 0;
    int i = 0;
    int j = 0;
    int k = 7;
    int p = 0;
    int q = 0;
    int ByteCount = 0;//�����ֽڳ���
    CString str;

    int BeiBa = 0;         //�ж��ٸ��� 8 ��
    int YuBa =  0;
    m = 0;
    n = 0;

    //m_WriteDotAddr�����ŵ������ݵ�ַ����  ��ʽΪ ��ַ���ֽ� ��ַ���ֽ�
    //m_ByteData �����ŵ�������  ÿ��ͼƬ�ĸ�ʽΪ �� �� ���󳤶�


    m_WriteIndex++;   //���

    m_ByteData[p++] = height;   //yuan Ҫ��ÿ��������ǰ �� ����
    m_ByteData[p++] = width;


    str.Format("��:%d ",m_ByteData[0]);	//��
    m_strEDITBit += str;
    ByteCount ++;

    str.Format("��:%d ",m_ByteData[1]);	//��
    m_strEDITBit += str;
    ByteCount ++;

    p++;                               //���󳤶� Ԥ��  2
    ByteCount ++;

    m_strEDITBit +="\r\n";

    if(1/*height == 12*/)
    {
        //FONT12
        int hang,lie;
        int liemax = width%2==0?width:width+1;
        int hangmax = height%8==0?(height/8):(height/8 +1);

        for(hang=0; hang<hangmax; hang++)
        {
            for(lie=0; lie<liemax; lie++)
            {
                int bit_index=8*hang +7;
                int count=0;
                char temp[10]={0};

                CString strBit="";
                CString strInt="";
                strBit.Format("��%d:",lie%2);
                for(bit_index; bit_index>=8*hang; bit_index--)
                {
                    strBit += m_BinData[bit_index][lie]==1 ?"1" : "0";
                    temp[count] = m_BinData[bit_index][lie]==1 ?'1' : '0';
                    count++;
                }
                strInt.Format(":%d",btoi(temp));
                if(lie==11)
                {
                    m_strEDITBit += strBit+strInt+"//\r\n";
                }
                else
                {
                    m_strEDITBit += strBit+strInt+"\r\n";
                }
            }
        }

    }
    /*
        while (i<8)
        {
            tc[i] = m_BinData[m+q][n];
            m++;
            i++;
            if (i == 8)
            {
                n ++;
                s = 0;
                k = 7;
                for (j=7; j>=0; j--)
                {
                    s = s + tc[j] * (int)pow(2, k);//�˸�������λתΪʮ���� �ֽ�
                    k -- ;
                }

                m_ByteData[p++] = s;
                str.Format("0x%02X ",s);
                m_strEDITBit += str;
                ByteCount ++;                       //�ֽ���
                if(n >= width)						//���϶��µ���ǰ��λɨ��
                {
                    n = 0;
                    q+=8;                           //�ӵڰ��е�0�п�ʼ
                    BeiBa = height / 8;         //�ж������ 8 ��
                    YuBa =  height % 8;

                    if (YuBa && (q / 8 == BeiBa))                // �����8���е�����
                    {
                        if (((q+8) * width) > (height * width))
                        {
                            for (i=0; i<(8-YuBa); i++)				  //��� 8-YuBa �� x ��  ����
                            {
                                for (j=0; j<width; j++)
                                {
                                    m_BinData[height+i][j] = 0;
                                }
                            }
                        }
                    }
                    if (!YuBa)
                    {
                        if ((q / 8) == BeiBa)           //ȫ��ɨ�����
                        {
                            break;
                        }
                    }
                    else								//�ж���8��������ʱ ȫ��ɨ�����
                    {
                        if ((q / 8) == (BeiBa+1))
                        {
                            break;
                        }
                    }
                }
                i = 0;
                m = 0;
                if (!((ByteCount-3) % 12))
                {
                    m_strEDITBit +="\r\n";
                }
            }
        }
    */
    m_strEDITBit +="\r\n";
//    str.Format("���ֽ�����%d  (������ �� �������ݳ���)",ByteCount);   //�� �� �������ݳ��� ��������
//    m_strEDITBit += str;
//    m_strEDITBit +="\r\n";


    m_ByteData[2] = ByteCount - 3;    //���󳤶Ȳ����� �� ��  ���󳤶�

    //m_WriteDotAddr
    m_WriteDotAddr[0] = m_bmpSum * 2;  //��һ��ͼƬ�ĵ����ַ
    if (bmpIndex > 1)                  //�ӵڶ���ͼƬ��ַ���㿪ʼ
    {
        m_WriteDotAddr[bmpIndex-1] = m_WriteDotAddr[bmpIndex-2] + m_LastByteCount;   //��һ��ͼƬ�����ŵĵ�ַ
    }

    m_LastByteCount = ByteCount;      //�����ϴεĵ��󳤶�

    for (i=0; i<ByteCount; i++)
    {
        m_WriteFileByte[i + m_WriteByteCount] = m_ByteData[i];
    }
    m_WriteByteCount += ByteCount;
    if (bmpIndex == m_bmpSum)        //m_bmpSum Ϊ�ܵ�ͼƬ����  bmpIndex���� Ϊ��ǰͼƬ���С�ڵ����ܸ���
    {
        WriteDotByteFile();          //д���ļ�
        UpdateData(FALSE);
    }
}


// ��ȡ�����ļ�
void CGetBMPDotDlg::OnBTNReadConfig()
{
    int i = 0;
    int Count = 0;
    CString  str;
    CString  strFileName;
    CString  strPathFileName;

    m_PicHeigh = 20;
    m_PicWidth = 20;
    m_WriteByteCount = 0;
    m_WriteIndex = 0;


    CFileDialog dlg(TRUE,NULL,"*.ini",
                    OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                    _T("ini Files(*.ini)|*.ini|All Files (*.*)|*.*||"),
                    AfxGetMainWnd());
    dlg.m_ofn.lpstrTitle="��ȡͼƬ�����ļ�";    //���ô򿪶Ի���ı���

    if (dlg.DoModal() == IDOK)
    {
        CString strPathName = dlg.GetPathName();
        strFileName = dlg.GetFileName();
        CIni IniFile(strPathName);          //�ļ���

        CString  strCount = IniFile.GetString("COUNT", "COUNT");  //��ȡ��¼����
        Count = atoi(strCount);

        m_bmpSum = Count;

        //��ȡ�ļ�·����
        strPathName = strPathName.Mid(0, strlen(strPathName) - strlen(strFileName));//ȥ�������ļ�������

        m_strPath =  strPathName;
        for (i=0; i<Count; i++)
        {
            str.Format("%d",i);
            strFileName = IniFile.GetString("PATHNAME", str);		//��ȡ�ļ���
            strPathFileName = strPathName + strFileName;
            OnBTNReadBMP(strPathFileName, i+1);
        }
    }
}



void CGetBMPDotDlg::WriteDotByteFile()
{
    CFile* pDstFile = NULL;

    m_strPath += "\MenuDot.lib";
    pDstFile = new CFile(m_strPath, CFile::modeCreate | CFile::modeWrite);	//Ŀ���ļ�
    unsigned int len = 0;//m_WriteByteCount;
    unsigned int i = 0;
    unsigned char c;

    //��д��ַ��������д������Ӧ������
    //������ַ�����ֽڣ��ɸߵ���

    len = m_WriteIndex;
    while(len)
    {
        c = (m_WriteDotAddr[i] >> 8) & 0xFF;
        pDstFile->Write(&c, 1);		 //��д���ֽڵ�ַ

        c = m_WriteDotAddr[i] & 0xFF;
        pDstFile->Write(&c, 1);		 //��д���ֽڵ�ַ
        len--;
        i++;
    }

    len = m_WriteByteCount;
    i = 0;
    while (len > 0)
    {
        pDstFile->Write(m_WriteFileByte+i, 1);		//д��������
        len--;
        i++;
    }
    pDstFile->Close();
}

