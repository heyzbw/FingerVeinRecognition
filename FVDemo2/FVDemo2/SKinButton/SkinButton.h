#pragma once


#include <atlctrls.h>
class CSkinButton:
	public CWindowImpl <CSkinButton,CButton>
{
public:
	
	CSkinButton(void);
	virtual ~CSkinButton(void);
	BEGIN_MSG_MAP(CSkinButton)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_TIMER,OnTimer);
		MESSAGE_HANDLER(WM_LBUTTONDOWN,OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP,OnLButtonUp)
		MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
public:
	
	LRESULT
		OnDrawItem(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled);
	LRESULT
		OnMouseMove(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled);
	LRESULT
		OnTimer(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled);
	LRESULT
		OnLButtonDown(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled);
	LRESULT
		OnLButtonUp(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& bHandled);
public:
	
	BOOL SetBitmap(
		UINT nNormalID,       
		UINT nMouseOverID = 0,
		UINT nPressID = 0,   
		UINT nDisabledID = 0);

	BOOL SetBitmap(
		CString strNormal,       
		CString strHover = _T(""),
		CString strPress = _T(""),   
		CString strDisable = _T(""));
	virtual void SubclassWindow(HWND hWnd);

	void SetTitle(CString strTitle);

	void SetColor(COLORREF cr)
	{
		m_crText = cr;
	}

	CBitmap LoadBitmapFromFile(CString strPath);

	void setWidth(int nWidth)
	{
		m_nWidth = nWidth;
	}

	void setHeight(int nHeight)
	{
		m_nHeight = nHeight;
	}

	void setTransparent(BOOL bTransparent = FALSE)
	{
		m_bTransparent = bTransparent;
	}
private:
	
	void SizeAdjustToContent();
private:

	BOOL m_bMouseOver;	
	BOOL m_bLButtionPress;
	UINT m_nNormalID;   
	UINT m_nMouseOverID;
	UINT m_nPressID;    
	UINT m_nDisabledID; 

	COLORREF m_crText;
	BOOL m_bTransparent;

	CString m_strNormalImg;
	CString m_strHoverImg;
	CString m_strPressImg;
	CString m_strDisableImage;
	CString m_strText;

	int m_nWidth;
	int m_nHeight;
};
