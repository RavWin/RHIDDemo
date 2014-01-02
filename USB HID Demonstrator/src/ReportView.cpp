/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : ReportView.cpp
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Report page implementation
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
#include "ReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BYTE InputReport[256];
extern BYTE OutputReport[256];
extern BOOL WRITE_ROPRT;

/////////////////////////////////////////////////////////////////////////////
// CReportView dialog


CReportView::CReportView(CWnd* pParent /*=NULL*/)
	: CDialog(CReportView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportView)
	m_OutPutHxEditLength = _T("FFFF");
	m_InPutHxEditLength = _T("FFFF");
	//}}AFX_DATA_INIT
}


void CReportView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportView)
	DDX_Control(pDX, IDC_OUTPUT_HEX_EDITOR, m_OutputHexEditorCtrl);
	DDX_Control(pDX, IDC_INPUT_HEX_EDITOR, m_InputHexEditorCtrl);
	DDX_Control(pDX, IDC_SIZE_INPUT_HEX_EDIT, m_InPutHxEditLengthCtrl);
	DDX_Control(pDX, IDC_SIZE_OUTPUT_HEX_EDIT, m_OutPutHxEditLengthCtrl);
	DDX_Text(pDX, IDC_SIZE_OUTPUT_HEX_EDIT, m_OutPutHxEditLength);
	DDX_Text(pDX, IDC_SIZE_INPUT_HEX_EDIT, m_InPutHxEditLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportView, CDialog)
	//{{AFX_MSG_MAP(CReportView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_WRITE_BTN, OnWriteBtn)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_SIZE_OUTPUT_HEX_EDIT, OnChangeSizeOutputHexEdit)
	ON_EN_CHANGE(IDC_SIZE_INPUT_HEX_EDIT, OnChangeSizeInputHexEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportView message handlers

void CReportView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages

	UpdateData(TRUE);
	WORD  OutSize = _tcstoul(m_OutPutHxEditLength, 0, 16); 
	WORD  InSize =  _tcstoul(m_InPutHxEditLength, 0, 16); 

	m_OutputHexEditorCtrl.SetDataSize(OutSize);
	m_InputHexEditorCtrl.SetDataSize(InSize);
	UpdateData(FALSE);
}

void CReportView::OnWriteBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	WORD  OutSize = _tcstoul(m_OutPutHxEditLength, 0, 16); 

	LPBYTE pData = (LPBYTE)malloc(OutSize);
	m_OutputHexEditorCtrl.GetData(pData, OutSize); 

	memcpy(&OutputReport, pData, OutSize);

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;
}

void CReportView::OnSetfocusHexEditor() 
{
	// TODO: Add your control notification handler code here
}

void CReportView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	WORD  InSize = _tcstoul(m_InPutHxEditLength, 0, 16); 
	m_InputHexEditorCtrl.SetData((LPBYTE)InputReport,InSize);
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

BOOL CReportView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportView::OnChangeSizeOutputHexEdit() 
{
	UpdateData(TRUE);
	WORD  OutSize = _tcstoul(m_OutPutHxEditLength, 0, 16); 
	m_OutputHexEditorCtrl.SetDataSize(OutSize);
	UpdateData(FALSE);
}

void CReportView::OnChangeSizeInputHexEdit() 
{
	UpdateData(TRUE);
	WORD  InSize = _tcstoul(m_InPutHxEditLength, 0, 16); 
	m_InputHexEditorCtrl.SetDataSize(InSize);
	UpdateData(FALSE);
}
