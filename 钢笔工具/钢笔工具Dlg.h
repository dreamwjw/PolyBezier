
// 钢笔工具Dlg.h : 头文件
//

#pragma once


// C钢笔工具Dlg 对话框
class C钢笔工具Dlg : public CDialogEx
{
// 构造
public:
	C钢笔工具Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
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
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
