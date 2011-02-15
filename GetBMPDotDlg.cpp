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
//	m_stc.Create("静态文本",WS_CHILD | WS_VISIBLE | SS_SIMPLE,CRect(50,50,200,200),this,123);
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
    int blength = strlen(binary_c);//计算二进制字符串的长度
    int i = 0;
    int decimal = 0;

    for(i = 0; i < blength; i++)
    {
        int number = binary_c[i] - '0';
        if(number == 0 || number == 1)//判断所输入的数字是否为二进制数字
        {
            //这里使用移位方法。在数字a向左移一位，然后再在最后一位添加一个数字b，那么新数字的十进制值为a*2 + b
            decimal = decimal * 2 + number;
        }
        else
        {
            //MessageBox(hwnd, "请输入二进制整数", "错误", MB_OK);
            break;
        }
    }
    return decimal;
}
void CGetBMPDotDlg::OnBTNReadBMP(CString strPathFileName, int bmpIndex)
{
    if (!m_dib.Load(strPathFileName))
    {
        strPathFileName += "m_dib.Load() 出错!";
        MessageBox(strPathFileName);
        return;
    }



    CBitmap bitmap; //创建一位图类

    bitmap.m_hObject = LoadImage(AfxGetInstanceHandle(), strPathFileName ,	//使该位图的句柄指向导入的图像
                                 IMAGE_BITMAP,0,0,
                                 LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);

    if (NULL == bitmap.m_hObject)
    {
        strPathFileName+="  提取图片LoadImage出错！";
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
    int m = 0;//行
    int n = 0;//列

    bitmap.GetBitmap(&bm);

    CDC dcMem;
    dcMem.CreateCompatibleDC(0);
    dcMem.SelectObject(&bitmap);

    width = bm.bmWidth;                 //BMP 宽
    height = bm.bmHeight;

    //显示 BMP 图像
    CClientDC dc(this);
    m_dib.SetPalette(&dc);
    m_dib.Draw(&dc,m_PicWidth,m_PicHeigh,bm.bmWidth,bm.bmHeight);
    m_strEDITBit += strPathFileName;
    m_strEDITBit += "\r\n点阵表:\r\n";

    m_PicWidth += (width + 10);
    if (m_PicWidth >= 490)
    {
        m_PicWidth = 20 ;
        m_PicHeigh += 20;
    }

    /*
        if (!((width == 11 && height == 12) || (width == 42 && height == 14)))
        {
            MessageBox("读取图片大小必须为 12*36 或 14*42!");
            return;
        }
    */

    for(m=0; m<height; m++)//    列扫描
    {
        for(n=0; n<width; n++)//
        {
            bmp_color   = dcMem.GetPixel(n, m);  //GetPixel( int x, int y ) 行扫描
            red     =   GetRValue(bmp_color);
            green   =   GetGValue(bmp_color);
            blue    =   GetBValue(bmp_color);

            //二值化
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

    m_strEDITBit +="转换后得到的参数:\r\n";
//    m_strEDITBit +="\r\n";
    //8位转一字节
    unsigned char tc[8];//临时存一个字节数据
    int s = 0;
    int i = 0;
    int j = 0;
    int k = 7;
    int p = 0;
    int q = 0;
    int ByteCount = 0;//点阵字节长度
    CString str;

    int BeiBa = 0;         //有多少个整 8 行
    int YuBa =  0;
    m = 0;
    n = 0;

    //m_WriteDotAddr数组存放点阵数据地址索引  格式为 地址高字节 地址低字节
    //m_ByteData 数组存放点阵数据  每个图片的格式为 高 宽 点阵长度


    m_WriteIndex++;   //序号

    m_ByteData[p++] = height;   //yuan 要求每点针数组前 加 其宽高
    m_ByteData[p++] = width;


    str.Format("高:%d ",m_ByteData[0]);	//高
    m_strEDITBit += str;
    ByteCount ++;

    str.Format("宽:%d ",m_ByteData[1]);	//宽
    m_strEDITBit += str;
    ByteCount ++;

    p++;                               //点阵长度 预留  2
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
                strBit.Format("列%d:",lie%2);
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
                    s = s + tc[j] * (int)pow(2, k);//八个二进制位转为十进制 字节
                    k -- ;
                }

                m_ByteData[p++] = s;
                str.Format("0x%02X ",s);
                m_strEDITBit += str;
                ByteCount ++;                       //字节数
                if(n >= width)						//自上而下的列前八位扫完
                {
                    n = 0;
                    q+=8;                           //从第八行第0列开始
                    BeiBa = height / 8;         //有多个个整 8 行
                    YuBa =  height % 8;

                    if (YuBa && (q / 8 == BeiBa))                // 最后不足8倍行的行数
                    {
                        if (((q+8) * width) > (height * width))
                        {
                            for (i=0; i<(8-YuBa); i++)				  //最后 8-YuBa 行 x 列  补零
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
                        if ((q / 8) == BeiBa)           //全部扫描完成
                        {
                            break;
                        }
                    }
                    else								//有多于8的整数倍时 全部扫描完成
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
//    str.Format("总字节数：%d  (包括宽 高 点阵数据长度)",ByteCount);   //宽 高 点阵数据长度 点阵数据
//    m_strEDITBit += str;
//    m_strEDITBit +="\r\n";


    m_ByteData[2] = ByteCount - 3;    //点阵长度不包括 高 宽  点阵长度

    //m_WriteDotAddr
    m_WriteDotAddr[0] = m_bmpSum * 2;  //第一个图片的点阵地址
    if (bmpIndex > 1)                  //从第二个图片地址计算开始
    {
        m_WriteDotAddr[bmpIndex-1] = m_WriteDotAddr[bmpIndex-2] + m_LastByteCount;   //下一个图片点阵存放的地址
    }

    m_LastByteCount = ByteCount;      //保存上次的点阵长度

    for (i=0; i<ByteCount; i++)
    {
        m_WriteFileByte[i + m_WriteByteCount] = m_ByteData[i];
    }
    m_WriteByteCount += ByteCount;
    if (bmpIndex == m_bmpSum)        //m_bmpSum 为总的图片个数  bmpIndex参数 为当前图片序号小于等于总个数
    {
        WriteDotByteFile();          //写入文件
        UpdateData(FALSE);
    }
}


// 读取配置文件
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
    dlg.m_ofn.lpstrTitle="读取图片配置文件";    //设置打开对话框的标题

    if (dlg.DoModal() == IDOK)
    {
        CString strPathName = dlg.GetPathName();
        strFileName = dlg.GetFileName();
        CIni IniFile(strPathName);          //文件名

        CString  strCount = IniFile.GetString("COUNT", "COUNT");  //读取记录个数
        Count = atoi(strCount);

        m_bmpSum = Count;

        //读取文件路径名
        strPathName = strPathName.Mid(0, strlen(strPathName) - strlen(strFileName));//去了配置文件的名字

        m_strPath =  strPathName;
        for (i=0; i<Count; i++)
        {
            str.Format("%d",i);
            strFileName = IniFile.GetString("PATHNAME", str);		//读取文件名
            strPathFileName = strPathName + strFileName;
            OnBTNReadBMP(strPathFileName, i+1);
        }
    }
}



void CGetBMPDotDlg::WriteDotByteFile()
{
    CFile* pDstFile = NULL;

    m_strPath += "\MenuDot.lib";
    pDstFile = new CFile(m_strPath, CFile::modeCreate | CFile::modeWrite);	//目标文件
    unsigned int len = 0;//m_WriteByteCount;
    unsigned int i = 0;
    unsigned char c;

    //先写地址索引表，后写索引对应的数据
    //索引地址两个字节，由高到低

    len = m_WriteIndex;
    while(len)
    {
        c = (m_WriteDotAddr[i] >> 8) & 0xFF;
        pDstFile->Write(&c, 1);		 //先写高字节地址

        c = m_WriteDotAddr[i] & 0xFF;
        pDstFile->Write(&c, 1);		 //再写低字节地址
        len--;
        i++;
    }

    len = m_WriteByteCount;
    i = 0;
    while (len > 0)
    {
        pDstFile->Write(m_WriteFileByte+i, 1);		//写点阵数据
        len--;
        i++;
    }
    pDstFile->Close();
}

