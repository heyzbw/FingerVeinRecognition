// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PictureBox.h"
#include "SKinButton/SkinButton.h"

#include "libfv\include\fvapi.h"
#include "libfv\include\fvapierrdef.h"
#include "libfv\include\fvapitype.h"

#define WM_FINGER_RECEIVED		(WM_USER+103)
#define WM_VEIN_RECEIVED		(WM_USER+104)




class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DESTROY, OnDestory)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNCHittest)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlStatic)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDC_BTN_CLOSE, OnCancel)
		COMMAND_ID_HANDLER(IDC_BTN_CONN, OnBnConn)
		COMMAND_ID_HANDLER(IDC_BTN_DISCONN, OnBnDisConn)
		COMMAND_ID_HANDLER(IDC_BTN_ENROLL, OnBnEnroll)
		COMMAND_ID_HANDLER(IDC_BTN_VERIFY, OnBnVerify)
		COMMAND_ID_HANDLER(IDC_BTN_IDENTIFY, OnBnIdentify)
		COMMAND_ID_HANDLER(IDC_BTN_CLEAR, OnBnClear)
		COMMAND_ID_HANDLER(IDC_BTN_DEVPARAM, OnBnGetDevParam)
		MESSAGE_HANDLER(WM_FINGER_RECEIVED, OnMsgFingerReceived)
		MESSAGE_HANDLER(WM_VEIN_RECEIVED, OnMsgVeinReceived)	
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnBnConn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnDisConn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnEnroll(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnVerify(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnIdentify(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClear(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnGetDevParam(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestory(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNCHittest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCtlStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnMsgFingerReceived(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMsgVeinReceived(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	static DWORD WINAPI ThreadCapture(LPVOID lParam);
private:
	Image* m_pImgBK;
	WTL::CPictureBox m_PictureBoxVein;
	WTL::CPictureBox m_PictureBoxFingerprint;
	CSkinButton m_bnClose;
	CSkinButton m_bnConn;
	CSkinButton m_bnDisConn;
	CSkinButton m_bnEnroll;
	CSkinButton m_bnVerify;
	CSkinButton m_bnIdentify;
	CSkinButton m_bnClear;

public:

	HANDLE m_hDevice;
	HANDLE m_hDBCache;
	HANDLE m_hThreadWork;
	int m_imgFPWidth;
	int m_imgFPHeight;
	int m_imgFVWidth;
	int m_imgFVHeight;

	BOOL m_bIdentify;
	BOOL m_bStopThread;

	CString m_strFingerID;

	int GetIdentifyMode();

	void SaveImageToFile(unsigned char* pImageData, int nImageWidth, int nImageHeight, const CString& strFileName);

	unsigned char** m_preRegFPTmps;
	int  m_nPreRegFPTmpSize[3];
	unsigned char** m_preRegFVTmps;
	int  m_nPreRegFVTmpSize[3];
	int m_nEnrollIndex;

	//verify sample
	unsigned char** m_lastRegFPTmps;
	int  m_nlastRegFPTmpSize[3];
	unsigned char** m_lastRegFVTmps;
	int  m_nlastRegFVTmpSize[3];

	//�Ǽ�ͼƬ�Ĵ��
	unsigned char ** m_regFpImage;
	int  m_nregFpImageSize[3];
	unsigned char ** m_regFvImage;
	int  m_nregFvImageSize[3];

	BOOL m_bRegister;
	void DoRegister(unsigned char* fpTmp, int cbFPTmp, unsigned char* fvTmp, int cbFVTmp,unsigned char * fpImg,int fpImgSize, unsigned char * fvImg,int fvImgSize);

	void DoVerify(unsigned char* fpTmp, int cbFPTmp, unsigned char* fvTmp, int cbFVTmp);
};
