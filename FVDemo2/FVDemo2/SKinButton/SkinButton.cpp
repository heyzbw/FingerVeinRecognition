#include "StdAfx.h"
#include "SkinButton.h"
#include <atlimage.h>

//timer��ID��
#ifndef TIMER_ID_MOUSE
#define TIMER_ID_MOUSE 200
#endif
//�ӳ�ʱ��
#ifndef TIMER_DELAY_TIME_MOUSE
#define TIMER_DELAY_TIME_MOUSE 100
#endif

CSkinButton::CSkinButton(void):
m_bMouseOver(FALSE),
m_bLButtionPress(FALSE),
m_nNormalID(-1),   //����״̬
m_nMouseOverID(-1),//�������״̬
m_nPressID(-1),    //��ť����״̬
m_nDisabledID(-1),  //��ť��Чʱ��
m_nWidth(-1),
m_nHeight(-1),
m_bTransparent(FALSE)
{
	m_strText = _T("");
	m_strNormalImg = _T("");
	m_strHoverImg = _T("");
	m_strPressImg = _T("");
	m_strDisableImage = _T("");
	m_crText = RGB(0, 0, 255);
}

CSkinButton::~CSkinButton(void)
{
}
void CSkinButton::SubclassWindow(HWND hWnd)
{
	CWindowImplBaseT::SubclassWindow(hWnd);
	//�޸İ�ťΪ�Ի���
	ModifyStyle(0,BS_OWNERDRAW);
}

void CSkinButton::SetTitle(CString strTitle)
{
	m_strText = strTitle;
}

LRESULT 
CSkinButton::OnDrawItem(
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam,
			BOOL& bHandled)
{
	// TODO: Add your code to draw the specified item
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT) lParam;
	//����״̬
	UINT nCurrentBmpID = m_nNormalID;
	CString strBmpPath = m_strNormalImg;
	int nDirect = 0;
	if (m_bMouseOver)
	{
		if (m_bLButtionPress)
		{
			//�������
			nCurrentBmpID = m_nPressID;
			strBmpPath = m_strPressImg;
			nDirect = -1;
		} 
		else
		{
			//�������
			nCurrentBmpID = m_nMouseOverID;
			strBmpPath = m_strHoverImg;
			nDirect = 1;
		}

	}
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		nCurrentBmpID = m_nDisabledID;  // last image for disabled
		strBmpPath = m_strDisableImage;
	}

	// 	else if (lpDrawItemStruct->itemState & ODS_SELECTED)
	// 		nCurrentBmpID = m_nMouseOverID;
	// 	else if (lpDrawItemStruct->itemState & ODS_FOCUS)
	// 		nCurrentBmpID = m_nNormalID;  // third image for focused
	CBitmap hBitmap;
	//����λͼ
	if (-1 == nCurrentBmpID)
	{
		CImage img;
		img.Load(strBmpPath);
		hBitmap.Attach(img.Detach());
	}
	else
	{
		hBitmap.LoadBitmap(nCurrentBmpID);
	}
	
	if (NULL == hBitmap)
	{
		return FALSE;
	}
	//������Ŀ��DC���ݵ��ڴ�DC
	HDC hMemDC = CreateCompatibleDC(lpDrawItemStruct->hDC);
	//��λͼ�����ڴ�DC
	SelectObject(hMemDC,hBitmap);
	//λͼ��Ϣ�Ľṹ��
	BITMAP stBitmap;
	hBitmap.GetBitmap(&stBitmap);

	//RECT rcButton;
	//GetWindowRect(&rcButton);//����ͼ��Ĵ�С������ť��С
	//CRgn rgn;  
	//rgn.CreateRoundRectRgn(0, 0, rcButton.right-rcButton.left, rcButton.bottom-rcButton.top, 5, 5);
	//SetWindowRgn(rgn, TRUE);
	//���ڴ�λͼ���ڰ�ť��HDC��
	if (m_bTransparent)
	{
		BLENDFUNCTION bf = {AC_SRC_OVER,0,255,1};
		::AlphaBlend(lpDrawItemStruct->hDC, 0, 0,stBitmap.bmWidth,stBitmap.bmHeight,hMemDC,0,0,m_nWidth,m_nHeight,bf);
	}
	else
	{
		BitBlt(lpDrawItemStruct->hDC,0,0,stBitmap.bmWidth,stBitmap.bmHeight,hMemDC,nDirect,nDirect,SRCCOPY);
	}
	hBitmap.Detach();
	if (!m_strText.IsEmpty())
	{
		RECT rcBtn;
		rcBtn.left = 0;
		rcBtn.top = 5;
		rcBtn.right = stBitmap.bmWidth;
		rcBtn.bottom = stBitmap.bmHeight;
		SetTextColor(lpDrawItemStruct->hDC, m_crText);
		::SetBkMode( lpDrawItemStruct->hDC, TRANSPARENT );
		::DrawText(lpDrawItemStruct->hDC, m_strText, m_strText.GetLength(), &rcBtn, DT_CENTER);
	}

	//�ͷ���Դ
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);

	bHandled = FALSE;
	return TRUE;
}
LRESULT
CSkinButton::OnMouseMove(
			UINT uMsg,
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled)
{
	if (!m_bMouseOver)
	{	
		//�˴����жϷ�ֹ����ε�ˢ�£���Ϊ����ڰ�ť���ƶ���
		//�������¼���δ�������������ֻ��Ҫһ��
		m_bMouseOver = TRUE;
		SetTimer(TIMER_ID_MOUSE,TIMER_DELAY_TIME_MOUSE,NULL);
		InvalidateRect(NULL,FALSE);
	}
	bHandled = FALSE;
	return TRUE;
}
LRESULT
CSkinButton::OnLButtonDown(
			  UINT uMsg,
			  WPARAM wParam, 
			  LPARAM lParam, 
			  BOOL& bHandled)
{
	m_bLButtionPress = TRUE;
	bHandled = FALSE;
	return TRUE;
}
LRESULT
CSkinButton::OnLButtonUp(
						   UINT uMsg,
						   WPARAM wParam, 
						   LPARAM lParam, 
						   BOOL& bHandled)
{
	m_bLButtionPress = FALSE;
	bHandled = FALSE;
	return TRUE;
}
LRESULT
CSkinButton::OnTimer(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled)
{
	switch (wParam)
	{
	case TIMER_ID_MOUSE:
		POINT ptCursorPoint;
		//��ȡ���λ��
		GetCursorPos(&ptCursorPoint);
		ScreenToClient(&ptCursorPoint);
		RECT rcButton;
		GetClientRect(&rcButton);
		 //�����겻�ڰ�ť�����m_bMouseOver��ֵΪfalse
		if(!PtInRect(&rcButton ,ptCursorPoint))
		{
			KillTimer(TIMER_ID_MOUSE);
			m_bMouseOver = FALSE;
			InvalidateRect(NULL,FALSE);
		}
		break;
	default:
		break;
	}
	bHandled = FALSE;
	return TRUE;
}
BOOL CSkinButton::SetBitmap(
			   UINT nNormalID,
			   UINT nMouseOverID ,
			   UINT nPressID,
			   UINT nDisabledID)
{
	m_nNormalID = nNormalID;
	m_nMouseOverID = nMouseOverID;
	m_nPressID = nPressID;
	m_nDisabledID = nDisabledID;
	SizeAdjustToContent();
	return TRUE;
}

BOOL CSkinButton::SetBitmap(
			   CString strNormal,       
			   CString strHover,
			   CString strPress,   
			   CString strDisable)
{
	m_strNormalImg = strNormal;
	m_strHoverImg = strHover;
	m_strPressImg = strPress;
	m_strDisableImage = strDisable;
	SizeAdjustToContent();
	return TRUE;
}

void CSkinButton::SizeAdjustToContent()
{
	CBitmap bitmap;
	BITMAP stBitmap;
	
	if (-1 == m_nNormalID)
	{
		CImage img;
		img.Load(m_strNormalImg);
		bitmap.Attach(img.Detach());
	}
	else
	{
		bitmap.LoadBitmap(m_nNormalID);
	}
	bitmap.GetBitmap(&stBitmap);
	bitmap.Detach();
	//RECT rcButton;
	//GetWindowRect(&rcButton);//����ͼ��Ĵ�С������ť��С
	//CRgn rgn;  
	//rgn.CreateRoundRectRgn(0, 0, rcButton.right-rcButton.left, rcButton.bottom-rcButton.top, 5, 5);
	//SetWindowRgn(rgn, TRUE);

	RECT rcButton;
	GetWindowRect(&rcButton);//����ͼ��Ĵ�С������ť��С
	GetParent().ScreenToClient(&rcButton);
	rcButton.right  = rcButton.left + stBitmap.bmWidth;
	rcButton.bottom = rcButton.top  + stBitmap.bmHeight;
	if (-1 != m_nWidth)
	{
		rcButton.right = rcButton.left + m_nWidth;
	}
	else
	{
		m_nWidth = rcButton.right - rcButton.left;
	}
	if (-1 != m_nHeight)
	{
		rcButton.bottom = rcButton.top + m_nHeight;
	}
	else
	{
		m_nHeight = rcButton.bottom - rcButton.top ;
	}
	
	
	MoveWindow(&rcButton,FALSE);
}
