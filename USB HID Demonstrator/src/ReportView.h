/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : ReportView.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Report view header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_REPORTVIEW_H__64FEBAC0_58ED_48D0_9D8B_B48B6D0DAD6C__INCLUDED_)
#define AFX_REPORTVIEW_H__64FEBAC0_58ED_48D0_9D8B_B48B6D0DAD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportView.h : header file
//

#include "HexEdit.h"
#include "hexeditctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CReportView dialog

class CReportView : public CDialog
{
// Construction
public:
	CReportView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportView)
	enum { IDD = IDD_REPORT_VIEW };
	CHexEditor	m_OutputHexEditorCtrl;
	CHexEditor	m_InputHexEditorCtrl;
	CHexEdit	m_InPutHxEditLengthCtrl;
	CHexEdit	m_OutPutHxEditLengthCtrl;
	CString	m_OutPutHxEditLength;
	CString	m_InPutHxEditLength;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CReportView)
	afx_msg void OnPaint();
	afx_msg void OnWriteBtn();
	afx_msg void OnSetfocusHexEditor();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSizeOutputHexEdit();
	afx_msg void OnChangeSizeInputHexEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTVIEW_H__64FEBAC0_58ED_48D0_9D8B_B48B6D0DAD6C__INCLUDED_)
