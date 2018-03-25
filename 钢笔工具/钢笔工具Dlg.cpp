
// �ֱʹ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�ֱʹ���.h"
#include "�ֱʹ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�ֱʹ���Dlg �Ի���




C�ֱʹ���Dlg::C�ֱʹ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�ֱʹ���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ucDTtype = LINE;
	m_bThreadDrawTutorialStop = true;
	m_hThreadDrawTutorial = NULL;
	m_bPlayDrawTutorial = false;
}

void C�ֱʹ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C�ֱʹ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// C�ֱʹ���Dlg ��Ϣ�������

BOOL C�ֱʹ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_bThreadDrawTutorialStop = false;
	m_hThreadDrawTutorial = CreateEvent(NULL, TRUE, FALSE, NULL);
	AfxBeginThread(ThreadDrawTutorial, this);

	return FALSE;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C�ֱʹ���Dlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawGraphics(&dc, m_ucDTtype);
		m_bPlayDrawTutorial = true;

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C�ֱʹ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C�ֱʹ���Dlg::DrawGraphics(CDC* pDC, unsigned char ucDTtype)
{
	switch(ucDTtype)
	{
	case LINE:
		{
			CPen pen(PS_SOLID, 10, RGB(50,50,50));
			CPen* pOldPen = pDC->SelectObject(&pen);

			pDC->MoveTo(300, 200);
			pDC->LineTo(600, 200);
			pDC->Ellipse(300-5, 200-5, 300+5, 200+5);
			pDC->LineTo(600, 500);
			pDC->Ellipse(600-5, 500-5, 600+5, 500+5);

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

void C�ֱʹ���Dlg::DrawTutorial(CDC* pDC, unsigned char ucDTtype)
{
	switch(ucDTtype)
	{
	case LINE:
		{
			CPen pen(PS_SOLID, 5, RGB(0,0,255));
			CPen* pOldPen = pDC->SelectObject(&pen);

			pDC->Rectangle(300-3, 200-3, 300+3, 200+3);
			pDC->Rectangle(600-3, 200-3, 600+3, 200+3);
			pDC->Rectangle(600-3, 500-3, 600+3, 500+3);

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

			pDC->MoveTo(300, 200);
			pDC->LineTo(600, 200);
			pDC->LineTo(600, 500);

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

UINT C�ֱʹ���Dlg::ThreadDrawTutorial(LPVOID lpVoid)
{
	C�ֱʹ���Dlg* pDlg = (C�ֱʹ���Dlg*)lpVoid;
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

void C�ֱʹ���Dlg::StopThreadDrawTutorial()
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

void C�ֱʹ���Dlg::OnClose()
{
	StopThreadDrawTutorial();

	CDialogEx::OnClose();
}
