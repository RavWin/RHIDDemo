/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : GraphicView.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Graphic view header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_GRAPHICVIEW_H__63F7C696_E14A_453D_A678_F11A8B11108E__INCLUDED_)
#define AFX_GRAPHICVIEW_H__63F7C696_E14A_453D_A678_F11A8B11108E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphicView dialog

#include "hexedit.h"

class CGraphicView : public CDialog
{
// Construction
public:
	CGraphicView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphicView)
	enum { IDD = IDD_GRAPHIC_VIEW };
	CStatic	m_VICtrl;
	CStatic	m_L4Ctrl;
	CHexEdit	m_RID_L4_Ctrl;
	CButton	m_Led4OnOff_Ctrl;
	CStatic	m_Led4_Ctrl;
	CStatic	m_RV2_Ctrl;
	CStatic	m_RV1_Ctrl;
	CButton	m_Led3OnOff_Ctrl;
	CButton	m_Led2OnOff_Ctrl;
	CButton	m_Led1OnOff_Ctrl;
	CStatic	m_RL2_Ctrl;
	CStatic	m_VL_Ctrl;
	CStatic	m_RL1_Ctrl;
	CStatic	m_BL7_Ctrl;
	CStatic	m_BL6_Ctrl;
	CStatic	m_BL5_Ctrl;
	CStatic	m_BL4_Ctrl;
	CStatic	m_BL3_Ctrl;
	CStatic	m_BL2_Ctrl;
	CStatic	m_BL1_Ctrl;
	CHexEdit	m_RID_V_Ctrl;
	CHexEdit	m_RID_R2_Ctrl;
	CHexEdit	m_RID_R1_Ctrl;
	CHexEdit	m_RID_L3_Ctrl;
	CHexEdit	m_RID_L2_Ctrl;
	CHexEdit	m_RID_L1_Ctrl;
	CHexEdit	m_RID_B7_Ctrl;
	CHexEdit	m_RID_B6_Ctrl;
	CHexEdit	m_RID_B5_Ctrl;
	CHexEdit	m_RID_B4_Ctrl;
	CHexEdit	m_RID_B3_Ctrl;
	CHexEdit	m_RID_B2_Ctrl;
	CHexEdit	m_RID_B1_Ctrl;
	CSliderCtrl	m_VariableCtrl;
	CStatic	m_L1Ctrl;
	CStatic	m_L2Ctrl;
	CStatic	m_L3Ctrl;
	CStatic	m_B1Ctrl;
	CStatic	m_B2Ctrl;
	CStatic	m_B3Ctrl;
	CStatic	m_B4Ctrl;
	CStatic	m_B5Ctrl;
	CStatic	m_B6Ctrl;
	CStatic	m_B7Ctrl;
	CProgressCtrl	m_R2Ctrl;
	CProgressCtrl	m_R1Ctrl;
	CString	m_RID_B1;
	CString	m_RID_B2;
	CString	m_RID_B3;
	CString	m_RID_B4;
	CString	m_RID_B5;
	CString	m_RID_B6;
	CString	m_RID_B7;
	CString	m_RID_L1;
	CString	m_RID_L2;
	CString	m_RID_L3;
	CString	m_RID_L4;
	CString	m_RID_R1;
	CString	m_RID_R2;
	CString	m_RV1;
	CString	m_RV2;
	BOOL	m_Led1OnOffChecked;
	BOOL	m_Led2OnOffChecked;
	BOOL	m_Led3OnOffChecked;
	CString	m_RID_V;
	CString	m_vi_val;
	BOOL	m_Led4OnOffChecked;
	int		m_UseReport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphicView)
	virtual BOOL OnInitDialog();
	afx_msg void OnLed1OnOff();
	afx_msg void OnLed2OnOff();
	afx_msg void OnLed3OnOff();
	afx_msg void OnVariable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureVariable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRidButton1();
	afx_msg void OnChangeRidButton2();
	afx_msg void OnChangeRidButton3();
	afx_msg void OnChangeRidButton4();
	afx_msg void OnChangeRidButton5();
	afx_msg void OnChangeRidButton6();
	afx_msg void OnChangeRidButton7();
	afx_msg void OnChangeRidRoller1();
	afx_msg void OnChangeRidRoller2();
	afx_msg void OnChangeRidLed1();
	afx_msg void OnChangeRidLed2();
	afx_msg void OnChangeRidLed3();
	afx_msg void OnChangeRidVariable();
	afx_msg void OnCustomdrawVariable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRidLed4();
	afx_msg void OnLed4OnOff();
	afx_msg void OnUseSetReport();
	afx_msg void OnUseSetFeature();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__63F7C696_E14A_453D_A678_F11A8B11108E__INCLUDED_)
