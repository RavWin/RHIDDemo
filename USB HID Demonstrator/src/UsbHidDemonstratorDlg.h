/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : UsbHidDemonstratorDlg.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Main dialog header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_USBHIDDEMONSTRATORDLG_H__568434D4_16F5_45BC_A0EA_44631DE02D1F__INCLUDED_)
#define AFX_USBHIDDEMONSTRATORDLG_H__568434D4_16F5_45BC_A0EA_44631DE02D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ReportView.h" 
#include "GraphicView.h" 
#include "FeatureView.h" 
#include "DesrciptorView.h" 
#include "GraphicConfigView.h"
#include "IconButton.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbHidDemonstratorDlg dialog

class CUsbHidDemonstratorDlg : public CDialog
{
// Construction
public:
	static DWORD WINAPI ReadReport(void*);
	static DWORD WINAPI WriteReport(void*);

	void DisplayData(CString Data);
	void RefreshDevices();
	CUsbHidDemonstratorDlg(CWnd* pParent = NULL);	// standard constructor
	void GetDeviceCapabilities();

	CReportView m_ReportView_frm; 
    CGraphicView m_GraphicView_frm;
    CFeatureView m_FeatureView_frm;
    CDesrciptorView m_DesrciptorView_frm;
	CGraphicConfigView m_GraphicConfig_frm;

// Dialog Data
	//{{AFX_DATA(CUsbHidDemonstratorDlg)
	enum { IDD = IDD_USBHIDDEMONSTRATOR_DIALOG };
	CIconButton	m_GraphicConfigCtrl;
	CIconButton	m_TransfereCtrl;
	CIconButton	m_CapabilitiesCtrl;
	CIconButton	m_GraphicViewCtrl;
	CListBox	m_TargetsCtrl;
	CComboBox	m_HidTargetsCtrl;
	CString	m_HidTarget;
	int		m_UseSetxxx;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsbHidDemonstratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
    BOOL OnDeviceChange(UINT nEventType,DWORD dwData);

	// Generated message map functions
	//{{AFX_MSG(CUsbHidDemonstratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowDescroptorView();
	afx_msg void OnShowFeatureView();
	afx_msg void OnShowReportView();
	afx_msg void OnShowGraphicView();
	afx_msg void OnSelchangeHidTargets();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGraphicConfig();
	afx_msg void OnSetFeature();
	afx_msg void OnGetFeature();
	afx_msg void OnUseSetReport();
	afx_msg void OnUseSetFeature();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBHIDDEMONSTRATORDLG_H__568434D4_16F5_45BC_A0EA_44631DE02D1F__INCLUDED_)
