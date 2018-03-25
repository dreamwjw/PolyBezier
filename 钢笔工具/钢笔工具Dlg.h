
// �ֱʹ���Dlg.h : ͷ�ļ�
//

#pragma once


// C�ֱʹ���Dlg �Ի���
class C�ֱʹ���Dlg : public CDialogEx
{
// ����
public:
	C�ֱʹ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

private:
	unsigned char m_ucDTtype;
	enum{LINE, POLYGON, CIRCULAR};
	bool m_bThreadDrawTutorialStop;
	HANDLE m_hThreadDrawTutorial;
	bool m_bPlayDrawTutorial;

private:
	void DrawGraphics(CDC* pDC, unsigned char ucDTtype);
	void DrawTutorial(CDC* pDC, unsigned char ucDTtype);
	void StopThreadDrawTutorial();

private:
	static UINT ThreadDrawTutorial(LPVOID lpVoid);

public:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
