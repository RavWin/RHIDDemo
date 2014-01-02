/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : FeatureView.h
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Feature view header file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#if !defined(AFX_FEATUREVIEW_H__FB1F874E_D07B_488D_A6FF_F9AAC8EBD428__INCLUDED_)
#define AFX_FEATUREVIEW_H__FB1F874E_D07B_488D_A6FF_F9AAC8EBD428__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FeatureView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFeatureView dialog

class CFeatureView : public CDialog
{
// Construction
public:
	CFeatureView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFeatureView)
	enum { IDD = IDD_FEATURE_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeatureView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFeatureView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATUREVIEW_H__FB1F874E_D07B_488D_A6FF_F9AAC8EBD428__INCLUDED_)
