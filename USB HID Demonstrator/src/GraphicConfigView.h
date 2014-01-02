/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : GraphicConfigView.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Graphic config view header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_GRAPHICCONFIGVIEW_H__3202A7BE_7373_4668_9020_0A1892F8E5A8__INCLUDED_)
#define AFX_GRAPHICCONFIGVIEW_H__3202A7BE_7373_4668_9020_0A1892F8E5A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicConfigView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphicConfigView dialog

#include "HexEdit.h"

class CGraphicConfigView : public CDialog
{
// Construction
public:
	CGraphicConfigView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphicConfigView)
	enum { IDD = IDD_GRAPHIC_CONFIG };
	CHexEdit	m_B1Ctrl;
	CHexEdit	m_B2Ctrl;
	CHexEdit	m_B3Ctrl;
	CHexEdit	m_B4Ctrl;
	CHexEdit	m_B5Ctrl;
	CHexEdit	m_B6Ctrl;
	CHexEdit	m_B7Ctrl;
	CHexEdit	m_L1Ctrl;
	CHexEdit	m_L2Ctrl;
	CHexEdit	m_L3Ctrl;
	CHexEdit	m_L4Ctrl;
	CHexEdit	m_VOCtrl;
	CHexEdit    m_VI1Ctrl;
	CHexEdit	m_VI2Ctrl;


	CButton	m_shb7ctrl;
	CButton	m_shb6ctrl;
	CButton	m_shb5ctrl;
	CButton	m_shb4ctrl;
	CButton	m_shb3ctrl;
	CButton	m_shb1ctrl;
	CButton	m_shb2ctrl;
	CString	m_B1;
	CString	m_B2;
	CString	m_B3;
	CString	m_B4;
	CString	m_B5;
	CString	m_B6;
	CString	m_B7;
	CString	m_L1;
	CString	m_L2;
	CString	m_L3;
	CString	m_L4;
	CString	m_VO;
	CString	m_VI1;
	CString	m_VI2;
	BOOL	m_shb1;
	BOOL	m_shb2;
	BOOL	m_shb3;
	BOOL	m_shb4;
	BOOL	m_shb5;
	BOOL	m_shb7;
	BOOL	m_shb6;
	BOOL	m_Buttons;
	BOOL	m_shl1;
	BOOL	m_shl2;
	BOOL	m_shl3;
	BOOL	m_shvi1;
	BOOL	m_shvi2;
	BOOL	m_shvo;
	BOOL	m_shl4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicConfigView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphicConfigView)
	afx_msg void OnChangeB1();
	afx_msg void OnChangeB2();
	afx_msg void OnChangeB3();
	afx_msg void OnChangeB4();
	afx_msg void OnChangeB5();
	afx_msg void OnChangeB6();
	afx_msg void OnChangeB7();
	afx_msg void OnChangeL1();
	afx_msg void OnChangeL2();
	afx_msg void OnChangeL3();
	afx_msg void OnChangeVI1();
	afx_msg void OnChangeVO();
	afx_msg void OnChangeVI2();
	afx_msg void OnShb1();
	afx_msg void OnShb2();
	afx_msg void OnShb3();
	afx_msg void OnShb4();
	afx_msg void OnShb5();
	afx_msg void OnShb6();
	afx_msg void OnShb7();
	afx_msg void OnShl1();
	afx_msg void OnShl2();
	afx_msg void OnShl3();
	afx_msg void OnShvi1();
	afx_msg void OnShvi2();
	afx_msg void OnShvo();
	afx_msg void OnShl4();
	afx_msg void OnChangeL4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICCONFIGVIEW_H__3202A7BE_7373_4668_9020_0A1892F8E5A8__INCLUDED_)
