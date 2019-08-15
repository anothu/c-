#pragma once

#include"GameControl.h"

#include"global.h"
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;			//�ڴ�DC
	CDC m_dcBG;				//����DC
	CDC m_dcElm;			//Ԫ���ڴ�DC
	CDC m_dcMask;			//�����ڴ�DC
	CPoint m_ptGameTop;		//��ʼ������
    CSize m_sizeElem;		//ͼƬԪ�ش�С
    CRect m_rtGameRect;     //��Ϸ����Ĵ�С
    CGameControl m_gameControl; //��Ϸ������
	bool m_bFirstPoint;
	Vertex m_avPath[4];
	int m_nVexNum;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();//���ڳ�ʼ������
	afx_msg void OnPaint();//WM_PAINT��Ϣ����
	afx_msg void OnClickedBtnStart();
	void InitBackground();
	void InitElement();
	void UpdateWindow();//���½���
	void UpdateMap();
	

protected:
	void DrawTipLine(Vertex avPath[4], int nVexnum);
	void DrawTipFrame(int nRow, int nCol);

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
