/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : DescriptorView.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Descriptor view header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_DESRCIPTORVIEW_H__32F3D861_E32D_46DC_A1C1_279E1FE553F7__INCLUDED_)
#define AFX_DESRCIPTORVIEW_H__32F3D861_E32D_46DC_A1C1_279E1FE553F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DesrciptorView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDesrciptorView dialog*

#include "hexedit.h"

class CDesrciptorView : public CDialog
{
// Construction
public:
	CDesrciptorView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDesrciptorView)
	enum { IDD = IDD_DESCRIPTOR_VIEW };
	CHexEdit	m_VersionNumberCtrl;
	CHexEdit	m_VIDValueCtrl;
	CHexEdit	m_PIDValueCtrl;
	CString	m_VIDValue;
	CString	m_PIDValue;
	CString	m_VersionNumber;
	CString	m_CapabilitiesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesrciptorView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDesrciptorView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESRCIPTORVIEW_H__32F3D861_E32D_46DC_A1C1_279E1FE553F7__INCLUDED_)
