/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : DescriptorView.cpp
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Descriptor page implementation
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
#include "stdafx.h"
#include "UsbHidDemonstrator.h"
#include "DesrciptorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDesrciptorView dialog


CDesrciptorView::CDesrciptorView(CWnd* pParent /*=NULL*/)
	: CDialog(CDesrciptorView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDesrciptorView)
	m_VIDValue = _T("0xFFFF");
	m_PIDValue = _T("0xFFFF");
	m_VersionNumber = _T("0xFFFF");
	m_CapabilitiesList = _T("");
	//}}AFX_DATA_INIT
}


void CDesrciptorView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesrciptorView)
	DDX_Control(pDX, IDC_VERSION, m_VersionNumberCtrl);
	DDX_Control(pDX, IDC_VID, m_VIDValueCtrl);
	DDX_Control(pDX, IDC_PID, m_PIDValueCtrl);
	DDX_Text(pDX, IDC_VID, m_VIDValue);
	DDX_Text(pDX, IDC_PID, m_PIDValue);
	DDX_Text(pDX, IDC_VERSION, m_VersionNumber);
	DDX_Text(pDX, IDC_CAPABILITIES_LIST, m_CapabilitiesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDesrciptorView, CDialog)
	//{{AFX_MSG_MAP(CDesrciptorView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesrciptorView message handlers
