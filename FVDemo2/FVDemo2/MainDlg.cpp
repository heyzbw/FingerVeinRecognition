// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "fstream"
#include "MainDlg.h"
#include "common.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include<iostream>
#include"Serial.h"
#include <TCHAR.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#ifndef _WIN64
#pragma comment(lib, "libfv/x86lib/fvapi.lib")
#else
#pragma comment(lib, "libfv/x64lib/fvapi.lib")
#endif

RGBQUAD g_GrayTable[256] = {0x0};


#define ENROLL_CNT	3

#define HEIGHT_CAPTION 56

#define SHOWIMG_WIDTH  256
#define SHOWIMG_HEIGHT  320
#define xBtnPos		42
#define yBtnPos		464
#define xBtnSpace	105
#define yBtnSapce	40
CSerial serial;
void  serialInit() {
	serial.OpenSerialPort(_T("COM6:"), 9600, 8, 1);
}
void Send(char x) {
	serial.SendData(&x, 1);
}


LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	MoveWindow(0, 0, 600, 720);
	CenterWindow();
	serialInit();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	CString strPath = g_app_path;
	strPath += _T("Skins\\bg.png");
	USES_CONVERSION;
	m_pImgBK = new Image(T2W(strPath));

	HFONT hFont=CreateFont(16,0,0,0,FW_THIN,false,false,false,
		CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,_T("����"));
	(GetDlgItem(IDC_EDIT_REPORT)).SetFont(hFont);

	//240*320
	RECT rcImage;
	rcImage.left = 28;
	rcImage.top = 110;
	rcImage.right = 28+SHOWIMG_WIDTH;
	rcImage.bottom = 110+SHOWIMG_HEIGHT;
	m_PictureBoxFingerprint.Create(m_hWnd, rcImage, NULL,
		WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, WS_EX_CLIENTEDGE);
	m_PictureBoxFingerprint.StretchPicture(false);

	rcImage.left = 28+SHOWIMG_WIDTH+33;
	rcImage.top = 110;
	rcImage.right = 28+SHOWIMG_WIDTH+33+SHOWIMG_WIDTH;
	rcImage.bottom = 110+SHOWIMG_HEIGHT;
	m_PictureBoxVein.Create(m_hWnd, rcImage, NULL,
		WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, WS_EX_CLIENTEDGE);
	m_PictureBoxVein.StretchPicture(false);

	m_PictureBoxVein.SetBitmap(LoadBitmap(_Module.GetResourceInstance(),(LPTSTR)IDB_BITMAP_FV));
	
	m_bnClose.SubclassWindow(GetDlgItem(IDC_BTN_CLOSE));
	m_bnConn.SubclassWindow(GetDlgItem(IDC_BTN_CONN));
	m_bnDisConn.SubclassWindow(GetDlgItem(IDC_BTN_DISCONN));
	m_bnEnroll.SubclassWindow(GetDlgItem(IDC_BTN_ENROLL));
	m_bnVerify.SubclassWindow(GetDlgItem(IDC_BTN_VERIFY));
	m_bnIdentify.SubclassWindow(GetDlgItem(IDC_BTN_IDENTIFY));
	m_bnClear.SubclassWindow(GetDlgItem(IDC_BTN_CLEAR));

	m_bnClose.MoveWindow(600-56+1, 0, 56, 56, TRUE);

	//m_bnClose.SetBitmap(IDB_BITMAP_CLOSEHOVER, IDB_BITMAP_CLOSENORMAL, IDB_BITMAP_CLOSENORMAL);
	m_bnClose.SetBitmap(g_app_path + _T("skins\\btn_close_n.png"), 
						g_app_path + _T("skins\\btn_close_a.png"),
						g_app_path + _T("skins\\btn_close_p.png"),
						g_app_path + _T("skins\\btn_close_n.png"));
	
	m_bnConn.SetTitle(_T("�����豸"));
	m_bnConn.setTransparent(TRUE);
	m_bnConn.SetColor(RGB(255, 255, 255));
	m_bnConn.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
						g_app_path + _T("skins\\btn_bg_a.png"),
						g_app_path + _T("skins\\btn_bg_p.png"),
						g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnConn.MoveWindow(xBtnPos,yBtnPos,90,25);

	m_bnDisConn.SetTitle(_T("�Ͽ��豸"));
	m_bnDisConn.setTransparent(TRUE);
	m_bnDisConn.SetColor(RGB(255, 255, 255));
	m_bnDisConn.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
							g_app_path + _T("skins\\btn_bg_a.png"),
							g_app_path + _T("skins\\btn_bg_p.png"),
							g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnDisConn.MoveWindow(xBtnPos+xBtnSpace,yBtnPos,90,25);

	m_bnEnroll.SetTitle(_T("���ע��"));
	m_bnEnroll.setTransparent(TRUE);
	m_bnEnroll.SetColor(RGB(255, 255, 255));
	m_bnEnroll.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
							g_app_path + _T("skins\\btn_bg_a.png"),
							g_app_path + _T("skins\\btn_bg_p.png"),
							g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnEnroll.MoveWindow(xBtnPos+xBtnSpace*2,yBtnPos,90,25);

	m_bnVerify.SetTitle(_T("1��1 �ȶ�"));
	m_bnVerify.setTransparent(TRUE);
	m_bnVerify.SetColor(RGB(255, 255, 255));
	m_bnVerify.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
							g_app_path + _T("skins\\btn_bg_a.png"),
							g_app_path + _T("skins\\btn_bg_p.png"),
							g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnVerify.MoveWindow(xBtnPos,yBtnPos+yBtnSapce,90,25);

	m_bnIdentify.SetTitle(_T("1��N ʶ��"));
	m_bnIdentify.setTransparent(TRUE);
	m_bnIdentify.SetColor(RGB(255, 255, 255));
	m_bnIdentify.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
							g_app_path + _T("skins\\btn_bg_a.png"),
							g_app_path + _T("skins\\btn_bg_p.png"),
							g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnIdentify.MoveWindow(xBtnPos+xBtnSpace*1,yBtnPos+yBtnSapce,90,25);

	m_bnClear.SetTitle(_T("����"));
	m_bnClear.setTransparent(TRUE);
	m_bnClear.SetColor(RGB(255, 255, 255));
	m_bnClear.SetBitmap(g_app_path + _T("skins\\btn_bg_n.png"), 
						g_app_path + _T("skins\\btn_qc_bg_a.png"),
						g_app_path + _T("skins\\btn_qc_bg_p.png"),
						g_app_path + _T("skins\\btn_bg_d.png"));
	m_bnClear.MoveWindow(xBtnPos+xBtnSpace*2,yBtnPos+yBtnSapce,90,25);

	m_bnConn.EnableWindow(TRUE);
	m_bnDisConn.EnableWindow(FALSE);
	m_bnEnroll.EnableWindow(FALSE);
	m_bnVerify.EnableWindow(FALSE);
	m_bnIdentify.EnableWindow(FALSE);
	m_bnClear.EnableWindow(FALSE);

	((CWindow)GetDlgItem(IDC_BTN_DEVPARAM)).MoveWindow(xBtnPos-30,yBtnPos+yBtnSapce,20,20);
	((CWindow)GetDlgItem(IDC_STATIC_UID)).MoveWindow(373,yBtnPos+2,40,20);
	((CWindow)GetDlgItem(IDC_EDIT_USERID)).MoveWindow(428,yBtnPos,120,25);
	((CWindow)GetDlgItem(IDC_STATIC_IMODE)).MoveWindow(350,yBtnPos+yBtnSapce+4,75,20);
	((CWindow)GetDlgItem(IDC_COMBO1)).MoveWindow(428,yBtnPos+yBtnSapce,120,25);
	((CWindow)GetDlgItem(IDC_EDIT_REPORT)).MoveWindow(40,580,500,92);

	((CComboBox)GetDlgItem(IDC_COMBO1)).AddString(_T("����-���ʶ��"));
	((CComboBox)GetDlgItem(IDC_COMBO1)).AddString(_T("��-���ʶ��"));
	((CComboBox)GetDlgItem(IDC_COMBO1)).AddString(_T("��ȫ-���ʶ��"));
	((CComboBox)GetDlgItem(IDC_COMBO1)).AddString(_T("��һʶ��"));
	((CComboBox)GetDlgItem(IDC_COMBO1)).SetCurSel(0);

	SYSTEMTIME st = {0x0};
	GetLocalTime(&st);
	CString strText;
	strText.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	SetDlgItemText(IDC_STATIC_DATE, strText);
	SetDlgItemText(IDC_STATIC_SN, _T("SN:{0DBF422A-6700-48DF-B7CD-13EBC4CCB93F}"));
	SetDlgItemText(IDC_EDIT_USERID, _T("1"));

	//SetDlgItemText(IDC_EDIT_REPORT, _T("this is a test!\r\nthis is a test!\r\nthis is a test!\r\nthis is a test!\r\nthis is a test!"));
	SetDlgItemText(IDC_STATIC_SN, _T("��ȸָ����������"));

	for(int i = 0; i < 256; i++)
	{
		g_GrayTable[i].rgbRed = i;
		g_GrayTable[i].rgbGreen = i;
		g_GrayTable[i].rgbBlue = i;
		g_GrayTable[i].rgbReserved = 0;
	}
	m_bIdentify = TRUE;
	m_bRegister = FALSE;
	m_hDBCache = NULL;
	m_hDevice = NULL;
	m_bStopThread = FALSE;
	m_hThreadWork = NULL;

	m_preRegFPTmps = NULL;
	m_preRegFVTmps = NULL;
	m_lastRegFPTmps = NULL;
	m_lastRegFVTmps = NULL;
	m_regFpImage = NULL;
	m_regFvImage = NULL;

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	CPaintDC dc(m_hWnd);
	Graphics grp(dc.m_hDC);
	if (NULL != m_pImgBK)
	{
		RECT rcWnd;
		GetWindowRect(&rcWnd);
		grp.DrawImage(m_pImgBK, 0, 0, rcWnd.right-rcWnd.left, rcWnd.bottom-rcWnd.top);
	}
	grp.ReleaseHDC(dc.m_hDC);

	return 0;
}

LRESULT CMainDlg::OnDestory(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (NULL !=m_pImgBK)
	{
		delete m_pImgBK;
		m_pImgBK = NULL;
	}
	m_bnClose.UnsubclassWindow();
	m_bnConn.UnsubclassWindow();
	m_bnDisConn.UnsubclassWindow();
	m_bnEnroll.UnsubclassWindow();
	m_bnVerify.UnsubclassWindow();
	m_bnIdentify.UnsubclassWindow();
	m_bnClear.UnsubclassWindow();
	return 0;
}

LRESULT CMainDlg::OnNCHittest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	WORD py = HIWORD(lParam);
	RECT rect;
	GetWindowRect(&rect);
	if(py-rect.top < HEIGHT_CAPTION)
		return HTCAPTION;
	else
		return HTCLIENT;
	return 0;
}


LRESULT CMainDlg::OnCtlStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	HWND hWndCtrl = (HWND) lParam;
	HDC hDC = (HDC) wParam;
	
	if (IDC_STATIC_REPORT == ::GetDlgCtrlID(hWndCtrl))
	{
		::SetBkMode( hDC, TRANSPARENT );
		SetTextColor(hDC, RGB(255,0,0));
		return (LRESULT)CreateSolidBrush(RGB(0, 109, 164));
	}
	else if (IDC_STATIC_IMODE == ::GetDlgCtrlID(hWndCtrl) || IDC_STATIC_UID == ::GetDlgCtrlID(hWndCtrl))
	{
		::SetBkMode( hDC, TRANSPARENT );
		SetTextColor(hDC, RGB(20,20,20));
		//return (LRESULT)CreateSolidBrush(RGB(0, 109, 164));
	}
	else
	{
		::SetBkMode( hDC, TRANSPARENT );
		SetTextColor(hDC, RGB(255,255,255));
	}

	return (LRESULT)GetStockObject(NULL_BRUSH);
}


CString FUN_Char2CString(char *ch1, char * ch2)  //ch1 ���ڸ���˵��
{
	CString cs;
	USES_CONVERSION;
	TCHAR* pUnicode1 = A2T(ch1);
	TCHAR* pUnicode2 = A2T(ch2);
	if (pUnicode1 == NULL)
	{
		cs.Format(_T("%s"), pUnicode2);
	}
	else
	{
		cs.Format(_T("%s  %s"), pUnicode1, pUnicode2);
	}

	return cs;
}

LRESULT CMainDlg::OnBnConn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL == m_hDevice)
	{
		if (FingerVein_Init() != FV_ERR_OK)
		{
			SetDlgItemText(IDC_EDIT_REPORT, _T("��ʼ���豸ʧ��"));
			return S_OK;
		}
		if ((m_hDevice = FingerVein_OpenDevice(0) ) == NULL)
		{
			SetDlgItemText(IDC_EDIT_REPORT, _T("�򿪴�����ʧ��"));
			FingerVein_Terminate();
			return S_OK;
		}
		m_hDBCache = FingerVein_DBInit(m_hDevice);
		if (NULL == m_hDBCache)
		{
			SetDlgItemText(IDC_EDIT_REPORT, _T("�������ݿ�ʧ��"));
			FingerVein_CloseDevice(m_hDevice);
			FingerVein_Terminate();
			return S_OK;
		}

		int nFullWidth = 0;
		int nFullHeight = 0;
		int retSize = sizeof(int);
		FingerVein_GetParameter(m_hDevice, 1, (unsigned char*)&nFullWidth, &retSize);
		retSize = sizeof(int);
		FingerVein_GetParameter(m_hDevice, 2, (unsigned char*)&nFullHeight, &retSize);

		m_preRegFPTmps = new unsigned char*[ENROLL_CNT];
		m_preRegFVTmps = new unsigned char*[ENROLL_CNT];
		m_lastRegFPTmps = new unsigned char*[ENROLL_CNT];
		m_lastRegFVTmps = new unsigned char*[ENROLL_CNT];
		m_regFpImage = new unsigned char*[ENROLL_CNT];
		m_regFvImage = new unsigned char*[ENROLL_CNT];

		m_imgFPWidth = nFullWidth&0xFFFF;
		m_imgFPHeight = nFullHeight&0xFFFF;
		m_imgFVWidth = (nFullWidth >> 16) & 0xFFFF;
		m_imgFVHeight = (nFullHeight >> 16) & 0xFFFF;

		for (int i=0;i<ENROLL_CNT;i++)
		{
			m_preRegFPTmps[i] = new unsigned char[MAX_TEMPLATE_SIZE];
			m_preRegFVTmps[i] = new unsigned char[MAX_TEMPLATE_SIZE];
			m_lastRegFPTmps[i] = new unsigned char[MAX_TEMPLATE_SIZE];
			m_lastRegFVTmps[i] = new unsigned char[MAX_TEMPLATE_SIZE];
			m_regFpImage[i] = new unsigned char[m_imgFPWidth * m_imgFPHeight];
			m_regFvImage[i] = new unsigned char[m_imgFVWidth * m_imgFVHeight];
		}
		memset(m_nPreRegFPTmpSize, 0x0, ENROLL_CNT*sizeof(int));
		memset(m_nPreRegFVTmpSize, 0x0, ENROLL_CNT*sizeof(int));
		memset(m_nlastRegFPTmpSize, 0x0, ENROLL_CNT*sizeof(int));
		memset(m_nlastRegFVTmpSize, 0x0, ENROLL_CNT*sizeof(int));
		memset(m_nregFpImageSize, 0x0, ENROLL_CNT*sizeof(int));
		memset(m_nregFvImageSize, 0x0, ENROLL_CNT*sizeof(int));


		m_nEnrollIndex = 0;

		
		m_bnConn.EnableWindow(FALSE);
		m_bnDisConn.EnableWindow(TRUE);
		m_bnEnroll.EnableWindow(TRUE);
		m_bnVerify.EnableWindow(TRUE);
		m_bnIdentify.EnableWindow(TRUE);
		m_bnClear.EnableWindow(TRUE);
		m_hThreadWork = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadCapture, this, 0, NULL);

		SetDlgItemText(IDC_EDIT_REPORT, _T("��ʼ���ɹ�"));
		m_strFingerID.Empty();

		//��ʾSDK�汾��
		char cVerion[10] = {0x0};
		int leng = 10;
		if(FingerVein_GetSDKVersion(cVerion,&leng) == FV_ERR_OK)
		{
			SetDlgItemText(IDC_EDIT_REPORT, "�豸���ӳɹ�����ʼ���ɹ�");
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_REPORT, _T("����ɳ�ʼ��"));
	}
	return S_OK;
}

LRESULT CMainDlg::OnBnDisConn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL != m_hDevice)
	{
		m_bStopThread = TRUE;
		if (NULL != m_hThreadWork)
		{
			WaitForSingleObject(m_hThreadWork, INFINITE);
			CloseHandle(m_hThreadWork);
			m_hThreadWork = NULL;
		}
		if (NULL != m_hDBCache)
		{
			FingerVein_DBFree(m_hDBCache);
			m_hDBCache = NULL;
		}
		FingerVein_CloseDevice(m_hDevice);
		FingerVein_Terminate();
		m_hDevice = NULL;
		SetDlgItemText(IDC_EDIT_REPORT, _T("�رճɹ�"));
		m_bnConn.EnableWindow(TRUE);
		m_bnDisConn.EnableWindow(FALSE);
		m_bnEnroll.EnableWindow(FALSE);
		m_bnVerify.EnableWindow(FALSE);
		m_bnIdentify.EnableWindow(FALSE);
		m_bnClear.EnableWindow(FALSE);

		if (NULL != m_preRegFPTmps)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_preRegFPTmps[i];
			}
			delete[] m_preRegFPTmps;
			m_preRegFPTmps = NULL;
		}

		if (NULL != m_preRegFVTmps)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_preRegFVTmps[i];
			}
			delete[] m_preRegFVTmps;
			m_preRegFVTmps = NULL;
		}

		if (NULL != m_regFpImage)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_regFpImage[i];
			}
			delete[] m_regFpImage;
			m_regFpImage = NULL;
		}

		if (NULL != m_regFvImage)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_regFvImage[i];
			}
			delete[] m_regFvImage;
			m_regFvImage = NULL;
		}

		if (NULL == m_lastRegFVTmps)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_lastRegFVTmps[i];
			}
			delete[] m_lastRegFVTmps;
			m_lastRegFVTmps = NULL;
		}

		if (NULL == m_lastRegFPTmps)
		{
			for (int i=0;i<ENROLL_CNT;i++)
			{
				delete[] m_lastRegFPTmps[i];
			}
			delete[] m_lastRegFPTmps;
			m_lastRegFPTmps = NULL;
		}
	}
	return S_OK;
}

LRESULT CMainDlg::OnBnEnroll(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL != m_hDevice)
	{
		CString strTemp;
		GetDlgItemText(IDC_EDIT_USERID, strTemp);
		if (strTemp.IsEmpty())
		{
			SetDlgItemText(IDC_EDIT_REPORT, _T("�û�ID���Ϸ�������������"));
			return S_OK;
		}
		m_strFingerID = strTemp;
		if (!m_bRegister)
		{
			m_bRegister = TRUE;
			m_nEnrollIndex = 0;
			SetDlgItemText(IDC_EDIT_REPORT, _T("����ע�ᣬ�������ָ3��"));
		}
	}
	return S_OK;
}

LRESULT CMainDlg::OnBnVerify(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL != m_hDevice)
	{
		if (m_bRegister)
		{
			m_bRegister = FALSE;
			SetDlgItemText(IDC_EDIT_REPORT, _T("��ʼ��֤�ϴ�ע�����ָģ��"));
		}
		m_bIdentify = FALSE;
	}
	return S_OK;
}

LRESULT CMainDlg::OnBnIdentify(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL != m_hDevice)
	{
		if (m_bRegister)
		{
			m_bRegister = FALSE;
			SetDlgItemText(IDC_EDIT_REPORT, _T("��¼����ָ��Ϣ"));
		}
		m_bIdentify = TRUE;
	}
	return S_OK;
}

LRESULT CMainDlg::OnBnClear(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (NULL != m_hDevice)
	{
		FingerVein_DBClear(m_hDBCache, BIO_TYPE_FP);
		FingerVein_DBClear(m_hDBCache, BIO_TYPE_FV);
		SetDlgItemText(IDC_EDIT_REPORT, _T("������ɣ�"));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_REPORT, _T("���������豸��"));
	}
	return S_OK;
}


int CMainDlg::GetIdentifyMode()
{
	int nSel = ((CComboBox)GetDlgItem(IDC_COMBO1)).GetCurSel();
	if (- 1 == nSel)
	{
		nSel = 0;
	}
	return nSel;
}


void CMainDlg::SaveImageToFile(unsigned char* pImageData, int nImageWidth, int nImageHeight, const CString& strFileName)
{
	// ����һ����ͼ�����ݴ�С��ƥ��� cv::Mat ����
	cv::Mat image(nImageHeight, nImageWidth, CV_8UC1, pImageData);

	// �� CString ת��Ϊ std::string
	CStringA strFileNameA(strFileName);
	std::string strFileNameStd(strFileNameA);

	// ʹ�� OpenCV �ĺ�����ͼ�����ݱ���Ϊ�Ҷ�ͼ���ļ�
	cv::imwrite(strFileNameStd, image);
}



DWORD WINAPI CMainDlg::ThreadCapture(LPVOID lParam)
{
	CMainDlg* pDlg = (CMainDlg*)lParam;
	if (NULL != pDlg)
	{
		pDlg->m_bStopThread = FALSE;
		CString m_strImageDirectory = R"(C:\Users\16033\Desktop\ָ����\FingerVein SDK for Windows\C++\sample)";
		unsigned char* pBufFPImage = new unsigned char[pDlg->m_imgFPWidth*pDlg->m_imgFPHeight];
		int nFPImageSize = 0;
		unsigned char* pBufFVImage = new unsigned char[pDlg->m_imgFVWidth*pDlg->m_imgFVHeight];
		int nFVImageSize = 0;
		unsigned char szFPTmp[MAX_TEMPLATE_SIZE] = {0x0};
		int nFPTmpSize = 0;
		unsigned char szFVTmp[MAX_TEMPLATE_SIZE] = {0x0};
		int nFVTmpSize = 0;
		while(!pDlg->m_bStopThread)
		{
			nFPImageSize = pDlg->m_imgFPWidth*pDlg->m_imgFPHeight;
			nFVImageSize = pDlg->m_imgFVWidth*pDlg->m_imgFVHeight;
			nFPTmpSize = MAX_TEMPLATE_SIZE;
			nFVTmpSize = MAX_TEMPLATE_SIZE;
			memset(szFPTmp, 0x0, MAX_TEMPLATE_SIZE);
			memset(szFVTmp, 0x0, MAX_TEMPLATE_SIZE);
			int ret = FingerVein_CaptureFingerVeinImageAndTemplate(pDlg->m_hDevice,
				pBufFPImage, &nFPImageSize, pBufFVImage, &nFVImageSize,
				szFPTmp, &nFPTmpSize, szFVTmp, &nFVTmpSize);
			if (FV_ERR_OK == ret)
			{
				if (nFPImageSize > 0)
				{
					// ����ָ��ͼ��ָ��Ŀ¼
					CString strFingerprintImageFile;
					strFingerprintImageFile.Format(_T("%s\\fingerprint_image.jpg"), m_strImageDirectory);
					pDlg->SaveImageToFile(pBufFPImage, pDlg->m_imgFPWidth, pDlg->m_imgFPHeight, strFingerprintImageFile);
					pDlg->SendMessageA((0x0400 + 103), (WPARAM)pBufFPImage, (LPARAM)nFPImageSize);
				}
				if (nFVImageSize > 0 && szFVTmp >0)
				{
					/*FILE *fp = NULL;
					fopen_s(&fp,"1.txt","wb+");
					if(fp != NULL)
					{
						fwrite(pBufFPImage,1,nFPImageSize,fp);
						fclose(fp);
					}*/
					// ����ָ����ͼ��ָ��Ŀ¼
					CString strVeinImageFile;
					strVeinImageFile.Format(_T("%s\\vein_image.jpg"), m_strImageDirectory);
					pDlg->SaveImageToFile(pBufFVImage, pDlg->m_imgFVWidth, pDlg->m_imgFVHeight, strVeinImageFile);
					pDlg->SendMessage(WM_VEIN_RECEIVED, (WPARAM)pBufFVImage, (LPARAM)nFVImageSize);
				}
				if (pDlg->m_bRegister)
				{
					pDlg->DoRegister(szFPTmp, nFPTmpSize, szFVTmp, nFVTmpSize, pBufFPImage, nFPImageSize, pBufFVImage, nFVImageSize);
				}
				else
				{
					pDlg->DoVerify(szFPTmp, nFPTmpSize, szFVTmp, nFVTmpSize);
				}
			}
			Sleep(100);
		}
	}
	return 0;
}


void CMainDlg::DoRegister(unsigned char* fpTmp, int cbFPTmp, unsigned char* fvTmp, int cbFVTmp,unsigned char * fpImg,int fpImgSize, unsigned char * fvImg,int fvImgSize)
{
	/*CString csInfo;
	csInfo.Format("cbFPTmp = %d\r\n\r\n",cbFPTmp);
	MessageBox(csInfo);
	OutputDebugStringA(csInfo);
	csInfo.Format("cbFVTmp = %d\r\n\r\n",cbFVTmp);
	OutputDebugStringA(csInfo);
	MessageBox(csInfo);*/
	if (cbFPTmp > 0 && cbFVTmp > 0)	//fingerprint and fingervein capture success
	{
		if (m_nEnrollIndex > 0)
		{
			//if (FingerVein_Verify(m_hDevice, BIO_TYPE_FP, fpTmp, cbFPTmp, m_preRegFPTmps[m_nEnrollIndex-1], m_nPreRegFPTmpSize[m_nEnrollIndex-1]) <= 0)
			/*if (FingerVein_Verify(m_hDevice, BIO_TYPE_FP, fpTmp, cbFPTmp, m_preRegFPTmps[m_nEnrollIndex-1], m_nPreRegFPTmpSize[m_nEnrollIndex-1]) <= 0 ||
				FingerVein_Verify(m_hDevice, BIO_TYPE_FV, fvTmp, cbFVTmp, m_preRegFVTmps[m_nEnrollIndex-1], m_nPreRegFVTmpSize[m_nEnrollIndex-1]) <= 0)*/
			if (FingerVein_Verify(m_hDevice, BIO_TYPE_FV, fvTmp, cbFVTmp, m_preRegFVTmps[m_nEnrollIndex-1], m_nPreRegFVTmpSize[m_nEnrollIndex-1]) <= 0)
			{
				SetDlgItemText(IDC_EDIT_REPORT, _T("�����Ϣ¼��ʧ�ܣ�"));
				m_bRegister = FALSE;
				m_nEnrollIndex = 0;
			}
		}
		memcpy(m_regFpImage[m_nEnrollIndex],fpImg,fpImgSize);
		m_nregFpImageSize[m_nEnrollIndex] = fpImgSize;
		memcpy(m_regFvImage[m_nEnrollIndex],fvImg,fvImgSize);
		m_nregFvImageSize[m_nEnrollIndex] = fvImgSize;
		memcpy(m_preRegFPTmps[m_nEnrollIndex], fpTmp, cbFPTmp);
		m_nPreRegFPTmpSize[m_nEnrollIndex] = cbFPTmp;
		memcpy(m_preRegFVTmps[m_nEnrollIndex], fvTmp, cbFVTmp);
		m_nPreRegFVTmpSize[m_nEnrollIndex] = cbFVTmp;
		m_nEnrollIndex++;
		//CString csInfo1;
		//csInfo1.Format("m_nEnrollIndex = %d\r\n",m_nEnrollIndex);
		//OutputDebugStringA(csInfo);
		if (m_nEnrollIndex >= 3)
		{
			int ret = 0;
			//if (FV_ERR_OK == (ret = FingerVein_DBAdd(m_hDBCache, BIO_TYPE_FP, m_strFingerID.GetBuffer(), m_preRegFPTmps, ENROLL_CNT)))
			/*if (FV_ERR_OK == (ret = FingerVein_DBAdd(m_hDBCache, BIO_TYPE_FP, m_strFingerID.GetBuffer(), m_preRegFPTmps, ENROLL_CNT)) &&
					FV_ERR_OK == (ret = FingerVein_DBAdd(m_hDBCache, BIO_TYPE_FV, m_strFingerID.GetBuffer(), m_preRegFVTmps, ENROLL_CNT)))*/
			if (FV_ERR_OK == (ret = FingerVein_DBAdd(m_hDBCache, BIO_TYPE_FV, m_strFingerID.GetBuffer(), m_preRegFVTmps, ENROLL_CNT)))
			{
				FingerVein_DBAdd(m_hDBCache, BIO_TYPE_FP, m_strFingerID.GetBuffer(), m_preRegFPTmps, ENROLL_CNT);
				SetDlgItemText(IDC_EDIT_REPORT, _T("�����Ϣ¼��ɹ���"));
				
				/*for(int i =0;i<ENROLL_CNT;i++)
				{
					m_strFingerID;
					char *pUsrID = m_strFingerID.GetBuffer(m_strFingerID.GetLength());	
					char strFpFileName[64] = {0x0};
					sprintf(strFpFileName,"userId%s_fp%d.bmp",pUsrID,i);
					WriteBitmap(fpImg,m_imgFPWidth,m_imgFPHeight,strFpFileName);
					char strFvFileName[64] = {0x0};
					sprintf(strFvFileName,"userId%s_fv%d.bmp",pUsrID,i);
					WriteBitmap(fvImg,m_imgFVWidth,m_imgFVHeight,strFvFileName);
				}*/

				//save Last register featue, to verify sample
				for (int i=0;i<ENROLL_CNT;i++)
				{
					m_nlastRegFPTmpSize[i] = m_nPreRegFPTmpSize[i];
					m_nlastRegFVTmpSize[i] = m_nPreRegFVTmpSize[i];
					memcpy(m_lastRegFPTmps[i], m_preRegFPTmps[i], m_nPreRegFPTmpSize[i]);
					memcpy(m_lastRegFVTmps[i], m_preRegFVTmps[i], m_nPreRegFVTmpSize[i]);
				}
			}
			else
			{
				CString strLog;
				strLog.Format(_T("ģ�������������ʧ�ܣ������Ϣ¼��ʧ�ܣ�return=%d\r\n"), ret);
				SetDlgItemText(IDC_EDIT_REPORT, strLog);
			}
			m_bRegister = FALSE;
			m_nEnrollIndex = 0;
		}
		else
		{
			CString strLog;
			strLog.Format(_T("¼�����������Ϣ��Ҫ�ٰ���ָ %d ��\r\n"), ENROLL_CNT-m_nEnrollIndex);
			SetDlgItemText(IDC_EDIT_REPORT, strLog);
		}
	}
}

void CMainDlg::DoVerify(unsigned char* fpTmp, int cbFPTmp, unsigned char* fvTmp, int cbFVTmp)
{
	if (m_bIdentify)
	{
		int identifyMode = GetIdentifyMode();

		char szFingerID[128] = {0x0};
		CString strLog;
		int score = 0;
		int ret = 0;
		if (0 == identifyMode)
		{
			//if (cbFPTmp > 0 && cbFVTmp > 0)
			if (cbFPTmp > 0 && cbFVTmp > 0)
			{
				if (FV_ERR_OK == (ret = FingerVein_DBHybridIdentify(m_hDBCache, IDENTIFY_MODE_ANY, fpTmp, cbFPTmp, fvTmp, cbFVTmp, szFingerID, &score)))
				{		
					strLog.Format(_T("����-���ʶ��ɹ������Ϊ %s���÷�Ϊ %d"), szFingerID, score);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
					Send('a');
				}
				else
				{
					strLog.Format(_T("����-���ʶ�������֤��ͨ���������ԣ�return=%d"), ret);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
				}
			}
			else
			{
				SetDlgItemText(IDC_EDIT_REPORT, _T("���ʶ�𲶻�ָ�ƺ�ָ�����ɹ���"));
			}
		}
		else if (1 == identifyMode)
		{
			if (cbFPTmp > 0 && cbFVTmp > 0)
			{
				if (FV_ERR_OK == (ret = FingerVein_DBHybridIdentify(m_hDBCache, IDENTIFY_MODE_FAKE, fpTmp, cbFPTmp, fvTmp, cbFVTmp, szFingerID, &score)))
				{		
					strLog.Format(_T("��-���ʶ��ɹ������Ϊ %s���÷�Ϊ %d"), szFingerID, score);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
					Send('a');
				}
				else
				{
					strLog.Format(_T("��-���ʶ�������֤��ͨ���������ԣ�return=%d"), ret);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
				}
			}
			else
			{
				SetDlgItemText(IDC_EDIT_REPORT, _T("���ʶ�𲶻�ָ�ƺ�ָ�����ɹ���"));
			}
		}
		else if(2 == identifyMode)
		{
			if (cbFPTmp > 0 && cbFVTmp > 0)
			{
				if (FV_ERR_OK == (ret = FingerVein_DBHybridIdentify(m_hDBCache, IDENTIFY_MODE_BOTH, fpTmp, cbFPTmp, fvTmp, cbFVTmp, szFingerID, &score)))
				{		
					strLog.Format(_T("��ȫ-���ʶ��ɹ������Ϊ %s���÷�Ϊ %d"), szFingerID, score);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
					Send('a');
				}
				else
				{
					strLog.Format(_T("��ȫ-���ʶ�������֤��ͨ���������ԣ�return=%d"), ret);
					SetDlgItemText(IDC_EDIT_REPORT, strLog);
				}
			}
			else
			{
				SetDlgItemText(IDC_EDIT_REPORT, _T("���ʶ�𲶻�ָ�ƺ�ָ�����ɹ���"));
			}
		}
		else
		{
			strLog = _T("");
			/*if (cbFPTmp > 0 && FV_ERR_OK == (ret = FingerVein_DBIdentify(m_hDBCache, BIO_TYPE_FP, fpTmp, cbFPTmp, szFingerID, &score)))
			{
				CString strTmp;
				strTmp.Format(_T("Identify fingerprint success, tid=%s, score=%d\r\n"), szFingerID, score);
				strLog += strTmp;
			}*/

			score = 0;
			if (cbFVTmp > 0 && FV_ERR_OK == (ret = FingerVein_DBIdentify(m_hDBCache, BIO_TYPE_FV, fvTmp, cbFVTmp, szFingerID, &score)))
			{
				CString strTmp;
				strTmp.Format(_T("ָ����ʶ��ɹ������Ϊ %s���÷�Ϊ %d\r\n"), szFingerID, score);
				strLog += strTmp;
				Send('a');
			}
			if (strLog.IsEmpty())
			{
				SetDlgItemText(IDC_EDIT_REPORT, _T("ָ����ʶ�������֤��ͨ����������"));
			}
			else
			{
				SetDlgItemText(IDC_EDIT_REPORT, strLog);
			}
		}
	}
	else
	{
		if (m_nlastRegFVTmpSize[0] <= 0)
		{
			SetDlgItemText(IDC_EDIT_REPORT, _T("δע��ָ����"));
			return;
		}
		CString strLog;
		if (cbFPTmp > 0)
		{
			CString strTmp = _T("ָ��ʶ��ʧ�ܣ�\r\n");
			int score = 0;
			for (int i = 0;i<ENROLL_CNT;i++)
			{
				if ((score = FingerVein_Verify(m_hDevice, BIO_TYPE_FP, m_lastRegFPTmps[i], m_nlastRegFPTmpSize[i], fpTmp, cbFPTmp)) > 0)
				{
					strTmp.Format(_T("�ɹ�ʶ��ָ�ƣ��÷�Ϊ %d��\r\n"), score);
					Send('a');
					break;
				}
			}
			strLog += strTmp;
		}
		if (cbFVTmp > 0)
		{
			CString strTmp = _T("ָ����ʶ��ʧ�ܣ�\r\n");
			int score = 0;
			for (int i = 0;i<ENROLL_CNT;i++)
			{
				//memcpy(fvTmp,fpTmp+100,100);
				//memcpy(fvTmp,fpTmp+500,100);

				if ((score = FingerVein_Verify(m_hDevice, BIO_TYPE_FV, m_lastRegFVTmps[i], m_nlastRegFVTmpSize[i], fvTmp, cbFVTmp)) > 0)
				{
					strTmp.Format(_T("�ɹ�ʶ��ָ�������÷�Ϊ %d��\r\n"), score);
					Send('a');
					break;
				}
			}
			strLog += strTmp;
		}
		SetDlgItemText(IDC_EDIT_REPORT, strLog);
	}
}

LRESULT CMainDlg::OnMsgFingerReceived(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	BYTE* pShowImg = new BYTE[640*480];
	ConvertImage((BYTE*)wParam, pShowImg, m_imgFPWidth, m_imgFPHeight, 240, 300, 0);
	HBITMAP hBitmap = BuildImage(pShowImg, 240, 300);
	delete [] pShowImg;
	m_PictureBoxFingerprint.SetBitmap(hBitmap);
	return S_OK;
}

void RotateImage(BYTE *ptr, int *width, int *height, int degree)
{
	int i, j, k, w, h;
	BYTE *tmp = NULL;
	w = *width;
	h = *height;
	tmp = (BYTE *)malloc(sizeof(BYTE)*(w * h));
	//BYTE *tmp = new BYTE[w * h];

	//char *tmp = (char *)malloc(sizeof(char)*(w * h));

	if (degree == -90)	//��ʱ����ת
	{
		for (i = 0; i < h; i++)
		{
			for (j = 0; j < w; j++)
			{
				k = (w - j - 1);
				tmp[h * k + i] = ptr[w * i + j];
			}
		}
	}
	else				//˳ʱ����ת
	{
		for (i = 0; i < h; i++)
		{
			k = (h - i - 1);
			for (j = 0; j < w; j++)
			{
				tmp[h * j + k] = ptr[w * i + j];
			}
		}
	}
	memcpy(ptr, tmp, w * h);
	*width = h;
	*height = w;
	if (NULL != tmp)
	{
		free (tmp);
		tmp = NULL;
	}

	//delete[]tmp;
}

LRESULT CMainDlg::OnMsgVeinReceived(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	BYTE* pSrc = new BYTE[640*480];
	BYTE* pShowImg = new BYTE[640*480];

	rotate90((BYTE*)wParam, pSrc, m_imgFVWidth, m_imgFVHeight);
	RotateImage(pShowImg, &m_imgFVWidth, &m_imgFVHeight, 0);
	RotateImage(pShowImg, &m_imgFVWidth, &m_imgFVHeight, 0);
	ConvertImage((BYTE*)pSrc, pShowImg, m_imgFVHeight, m_imgFVWidth, 240, 300, 1);
	HBITMAP hBitmap = BuildImage((BYTE*)pShowImg, 240, 300);
	delete [] pShowImg;
	delete [] pSrc;
	m_PictureBoxVein.SetBitmap(hBitmap);
	return S_OK;
}
	//LRESULT OnBnGetDevParam(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

LRESULT CMainDlg::OnBnGetDevParam(WORD /*uMsg*/, WORD wID, HWND /*lParam*/, BOOL& /*bHandled*/)
{
	CString strLog;
	m_bRegister = false;

	if(m_hDevice == NULL)
	{
		SetDlgItemText(IDC_EDIT_REPORT, "�豸δ����");
		return S_OK;
	}
	//��ʾSN��
	int flag = 1103; 
	unsigned char DevSN[64] = {0x0};
	int size = 64;
	FingerVein_GetParameter(m_hDevice,1103,DevSN,&size);

	//��ʾ�豸��
	flag = 1102; 
	unsigned char DevMame[64] = {0x0};
	size = 64;
	FingerVein_GetParameter(m_hDevice,1102,DevMame,&size);


	//��ʾ�̼��汾
	flag = 1201; 
	unsigned char FwVersion[3] = {0x0};
	size = 3;
	FingerVein_GetParameter(m_hDevice,1201,FwVersion,&size);

	strLog.Format("�豸����%s���豸SN�ţ�%s��SDK�汾�ţ�%d.%d",DevMame, DevSN, FwVersion[1],FwVersion[0]);
	SetDlgItemText(IDC_EDIT_REPORT, strLog);
	return S_OK;
}
