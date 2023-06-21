#include "StdAfx.h"
#include "SkinButton.h"
#include <atlimage.h>

//timer的ID号
#ifndef TIMER_ID_MOUSE
#define TIMER_ID_MOUSE 200
#endif
//延迟时间
#ifndef TIMER_DELAY_TIME_MOUSE
#define TIMER_DELAY_TIME_MOUSE 100
#endif

CSkinButton::CSkinButton(void):
m_bMouseOver(FALSE),
m_bLButtionPress(FALSE),
m_nNormalID(-1),   //正常状态
m_nMouseOverID(-1),//光标悬浮状态
m_nPressID(-1),    //按钮按下状态
m_nDisabledID(-1),  //按钮无效时候
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
	//修改按钮为自绘风格
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
	//正常状态
	UINT nCurrentBmpID = m_nNormalID;
	CString strBmpPath = m_strNormalImg;
	int nDirect = 0;
	if (m_bMouseOver)
	{
		if (m_bLButtionPress)
		{
			//左键按下
			nCurrentBmpID = m_nPressID;
			strBmpPath = m_strPressImg;
			nDirect = -1;
		} 
		else
		{
			//鼠标悬浮
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
	//加载位图
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
	//创建与目标DC兼容的内存DC
	HDC hMemDC = CreateCompatibleDC(lpDrawItemStruct->hDC);
	//将位图旋紧内存DC
	SelectObject(hMemDC,hBitmap);
	//位图信息的结构体
	BITMAP stBitmap;
	hBitmap.GetBitmap(&stBitmap);

	//RECT rcButton;
	//GetWindowRect(&rcButton);//根据图象的大小调整按钮大小
	//CRgn rgn;  
	//rgn.CreateRoundRectRgn(0, 0, rcButton.right-rcButton.left, rcButton.bottom-rcButton.top, 5, 5);
	//SetWindowRgn(rgn, TRUE);
	//将内存位图画在按钮的HDC中
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

	//释放资源
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
		//此处加判断防止过多次的刷新，因为鼠标在按钮上移动会
		//造成这个事件多次触发，但是我们只需要一次
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
		//获取光标位置
		GetCursorPos(&ptCursorPoint);
		ScreenToClient(&ptCursorPoint);
		RECT rcButton;
		GetClientRect(&rcButton);
		 //如果光标不在按钮上则给m_bMouseOver赋值为false
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
	//GetWindowRect(&rcButton);//根据图象的大小调整按钮大小
	//CRgn rgn;  
	//rgn.CreateRoundRectRgn(0, 0, rcButton.right-rcButton.left, rcButton.bottom-rcButton.top, 5, 5);
	//SetWindowRgn(rgn, TRUE);

	RECT rcButton;
	GetWindowRect(&rcButton);//根据图象的大小调整按钮大小
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
