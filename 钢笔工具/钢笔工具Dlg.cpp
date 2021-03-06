
// 钢笔工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "钢笔工具.h"
#include "钢笔工具Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C钢笔工具Dlg 对话框




C钢笔工具Dlg::C钢笔工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C钢笔工具Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ucDTtype = LINE;
	m_bThreadDrawTutorialStop = true;
	m_hThreadDrawTutorial = NULL;
	m_bPlayDrawTutorial = false;
	m_clrBackground = RGB(57,63,67);
	m_clrGraphic=RGB(40,50,50);
	m_clrLine=RGB(96,102,104);
	m_clrDraw=RGB(255,255,255);
}

void C钢笔工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C钢笔工具Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// C钢笔工具Dlg 消息处理程序

BOOL C钢笔工具Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_bThreadDrawTutorialStop = false;
	m_hThreadDrawTutorial = CreateEvent(NULL, TRUE, FALSE, NULL);
	AfxBeginThread(ThreadDrawTutorial, this);

	return FALSE;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C钢笔工具Dlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawBackground(&dc);
		DrawGraphics(&dc, m_ucDTtype);
		m_bPlayDrawTutorial = true;

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C钢笔工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C钢笔工具Dlg::DrawBackground(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, m_clrBackground);
}

void C钢笔工具Dlg::DrawGraphics(CDC* pDC, unsigned char ucDTtype)
{
	switch(ucDTtype)
	{
	case LINE:
		{
			int nPenWidth = 10, nRectangleWidth = 5;

			CPen pen(PS_SOLID, nPenWidth, m_clrGraphic);
			CPen* pOldPen = pDC->SelectObject(&pen);

			pDC->MoveTo(300, 200);
			pDC->LineTo(600, 200);
			pDC->Ellipse(300-nRectangleWidth, 200-nRectangleWidth, 300+nRectangleWidth, 200+nRectangleWidth);
			pDC->LineTo(600, 500);
			pDC->Ellipse(600-nRectangleWidth, 500-nRectangleWidth, 600+nRectangleWidth, 500+nRectangleWidth);

			pDC->SelectObject(pOldPen);

			//HGDIOBJ pOldGdiobj = pDC->SelectStockObject(NULL_BRUSH);
			//CRect rect(300-nRectangleWidth, 200-nRectangleWidth, 300+nRectangleWidth, 200+nRectangleWidth);
			//CPoint p1()
			//pDC->Arc()
			////AngleArc(pDC->m_hDC,600,500,nRectangleWidth,240,300);

			//pDC->SelectObject(pOldGdiobj);
		}
		break;
	case POLYGON:
		break;
	case CIRCULAR:
		break;
	default:
		break;
	}
}

void C钢笔工具Dlg::DrawTutorial(CDC* pDC, unsigned char ucDTtype)
{
	switch(ucDTtype)
	{
	case LINE:
		{
			int nPenWidth = 2, nRectangleWidth = 2;

			CPen pen(PS_SOLID, nPenWidth, m_clrLine);
			CPen* pOldPen = pDC->SelectObject(&pen);

			pDC->MoveTo(300, 200);
			pDC->LineTo(600, 200);
			pDC->LineTo(600, 500);

			CRect rect1(300-nRectangleWidth, 200-nRectangleWidth, 300+nRectangleWidth, 200+nRectangleWidth),
				rect2(600-nRectangleWidth, 200-nRectangleWidth, 600+nRectangleWidth, 200+nRectangleWidth),
				rect3(600-nRectangleWidth, 500-nRectangleWidth, 600+nRectangleWidth, 500+nRectangleWidth);
			pDC->FillSolidRect(&rect1, m_clrLine);
			pDC->FillSolidRect(&rect2, m_clrLine);
			pDC->FillSolidRect(&rect3, m_clrLine);

			//一条贝塞尔线最少要有 4 个点
			/*int nCount = 3;
			POINT* pts = new POINT[nCount];  
			pts[0].x = 300;  
			pts[0].y = 200;    
			pts[1].x = 600;  
			pts[1].y = 200;  
			pts[2].x = 600;  
			pts[2].y = 500;  
			PolyBezier(pDC->m_hDC, pts, nCount);  
			delete [] pts; */

			pDC->SelectObject(pOldPen);
		}
		break;
	case POLYGON:
		break;
	case CIRCULAR:
		break;
	default:
		break;
	}
}

UINT C钢笔工具Dlg::ThreadDrawTutorial(LPVOID lpVoid)
{
	C钢笔工具Dlg* pDlg = (C钢笔工具Dlg*)lpVoid;
	CClientDC dc(pDlg);

	while(!pDlg->m_bThreadDrawTutorialStop)
	{
		if(pDlg->m_bPlayDrawTutorial)
		{
			pDlg->DrawTutorial(&dc, pDlg->m_ucDTtype);
			pDlg->m_bPlayDrawTutorial = false;
		}

		Sleep(100);
	}

	SetEvent(pDlg->m_hThreadDrawTutorial);

	return 0;
}

void C钢笔工具Dlg::StopThreadDrawTutorial()
{
	m_bThreadDrawTutorialStop = true;
	while(TRUE)
	{
		DWORD result; 
		MSG msg;
		if(m_hThreadDrawTutorial == NULL) break;
		result = MsgWaitForMultipleObjects(1, &m_hThreadDrawTutorial, FALSE, INFINITE, QS_ALLINPUT); 
		if (result == (WAIT_OBJECT_0))
		{
			break;
		} 
		else 
		{ 
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			DispatchMessage(&msg);
		} 
	}
	CloseHandle(m_hThreadDrawTutorial);
}

void C钢笔工具Dlg::OnClose()
{
	StopThreadDrawTutorial();

	CDialogEx::OnClose();
}
