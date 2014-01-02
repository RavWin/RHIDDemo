/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : GraphicView.cpp 
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Graphic view page implementation
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
#include "GraphicView.h"
#include "Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView dialog

BYTE InputReport[256];
BYTE OutputReport[256];
BOOL WRITE_ROPRT;

int Oldm_RID_V = 0;

CGraphicView::CGraphicView(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphicView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphicView)
	m_RID_B1 = _T("00");
	m_RID_B2 = _T("00");
	m_RID_B3 = _T("00");
	m_RID_B4 = _T("00");
	m_RID_B5 = _T("00");
	m_RID_B6 = _T("00");
	m_RID_B7 = _T("00");
	m_RID_L1 = _T("00");
	m_RID_L2 = _T("00");
	m_RID_L3 = _T("00");
	m_RID_L4 = _T("00");
	m_RID_R1 = _T("00");
	m_RID_R2 = _T("00");
	m_RV1 = _T("00h");
	m_RV2 = _T("00h");
	m_Led1OnOffChecked = FALSE;
	m_Led2OnOffChecked = FALSE;
	m_Led3OnOffChecked = FALSE;
	m_RID_V = _T("00");
	m_vi_val = _T("00h");
	m_Led4OnOffChecked = FALSE;
	m_UseReport = 0;
	//}}AFX_DATA_INIT
}


void CGraphicView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphicView)
	DDX_Control(pDX, IDC_VI, m_VICtrl);
	DDX_Control(pDX, IDC_LED4, m_L4Ctrl);
	DDX_Control(pDX, IDC_RID_LED4, m_RID_L4_Ctrl);
	DDX_Control(pDX, IDC_LED4_ON_OFF, m_Led4OnOff_Ctrl);
	DDX_Control(pDX, IDC_RV2, m_RV2_Ctrl);
	DDX_Control(pDX, IDC_RV1, m_RV1_Ctrl);
	DDX_Control(pDX, IDC_LED3_ON_OFF, m_Led3OnOff_Ctrl);
	DDX_Control(pDX, IDC_LED2_ON_OFF, m_Led2OnOff_Ctrl);
	DDX_Control(pDX, IDC_LED1_ON_OFF, m_Led1OnOff_Ctrl);
	DDX_Control(pDX, IDC_RL2, m_RL2_Ctrl);
	DDX_Control(pDX, IDC_VL, m_VL_Ctrl);
	DDX_Control(pDX, IDC_RL1, m_RL1_Ctrl);
	DDX_Control(pDX, IDC_BL7, m_BL7_Ctrl);
	DDX_Control(pDX, IDC_BL6, m_BL6_Ctrl);
	DDX_Control(pDX, IDC_BL5, m_BL5_Ctrl);
	DDX_Control(pDX, IDC_BL4, m_BL4_Ctrl);
	DDX_Control(pDX, IDC_BL3, m_BL3_Ctrl);
	DDX_Control(pDX, IDC_BL2, m_BL2_Ctrl);
	DDX_Control(pDX, IDC_BL1, m_BL1_Ctrl);
	DDX_Control(pDX, IDC_RID_VARIABLE, m_RID_V_Ctrl);
	DDX_Control(pDX, IDC_RID_ROLLER2, m_RID_R2_Ctrl);
	DDX_Control(pDX, IDC_RID_ROLLER1, m_RID_R1_Ctrl);
	DDX_Control(pDX, IDC_RID_LED3, m_RID_L3_Ctrl);
	DDX_Control(pDX, IDC_RID_LED2, m_RID_L2_Ctrl);
	DDX_Control(pDX, IDC_RID_LED1, m_RID_L1_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON7, m_RID_B7_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON6, m_RID_B6_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON5, m_RID_B5_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON4, m_RID_B4_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON3, m_RID_B3_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON2, m_RID_B2_Ctrl);
	DDX_Control(pDX, IDC_RID_BUTTON1, m_RID_B1_Ctrl);
	DDX_Control(pDX, IDC_VARIABLE, m_VariableCtrl);
	DDX_Control(pDX, IDC_LED1, m_L1Ctrl);
	DDX_Control(pDX, IDC_LED2, m_L2Ctrl);
	DDX_Control(pDX, IDC_LED3, m_L3Ctrl);
	DDX_Control(pDX, IDC_BUTTON1, m_B1Ctrl);
	DDX_Control(pDX, IDC_BUTTON2, m_B2Ctrl);
	DDX_Control(pDX, IDC_BUTTON3, m_B3Ctrl);
	DDX_Control(pDX, IDC_BUTTON4, m_B4Ctrl);
	DDX_Control(pDX, IDC_BUTTON5, m_B5Ctrl);
	DDX_Control(pDX, IDC_BUTTON6, m_B6Ctrl);
	DDX_Control(pDX, IDC_BUTTON7, m_B7Ctrl);
	DDX_Control(pDX, IDC_ROLLER2, m_R2Ctrl);
	DDX_Control(pDX, IDC_ROLLER1, m_R1Ctrl);
	DDX_Text(pDX, IDC_RID_BUTTON1, m_RID_B1);
	DDX_Text(pDX, IDC_RID_BUTTON2, m_RID_B2);
	DDX_Text(pDX, IDC_RID_BUTTON3, m_RID_B3);
	DDX_Text(pDX, IDC_RID_BUTTON4, m_RID_B4);
	DDX_Text(pDX, IDC_RID_BUTTON5, m_RID_B5);
	DDX_Text(pDX, IDC_RID_BUTTON6, m_RID_B6);
	DDX_Text(pDX, IDC_RID_BUTTON7, m_RID_B7);
	DDX_Text(pDX, IDC_RID_LED1, m_RID_L1);
	DDX_Text(pDX, IDC_RID_LED2, m_RID_L2);
	DDX_Text(pDX, IDC_RID_LED3, m_RID_L3);
	DDX_Text(pDX, IDC_RID_LED4, m_RID_L4);
	DDX_Text(pDX, IDC_RID_ROLLER1, m_RID_R1);
	DDX_Text(pDX, IDC_RID_ROLLER2, m_RID_R2);
	DDX_Text(pDX, IDC_RV1, m_RV1);
	DDX_Text(pDX, IDC_RV2, m_RV2);
	DDX_Check(pDX, IDC_LED1_ON_OFF, m_Led1OnOffChecked);
	DDX_Check(pDX, IDC_LED2_ON_OFF, m_Led2OnOffChecked);
	DDX_Check(pDX, IDC_LED3_ON_OFF, m_Led3OnOffChecked);
	DDX_Text(pDX, IDC_RID_VARIABLE, m_RID_V);
	DDV_MaxChars(pDX, m_RID_V, 2);
	DDX_Text(pDX, IDC_VI, m_vi_val);
	DDX_Check(pDX, IDC_LED4_ON_OFF, m_Led4OnOffChecked);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphicView, CDialog)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_BN_CLICKED(IDC_LED1_ON_OFF, OnLed1OnOff)
	ON_BN_CLICKED(IDC_LED2_ON_OFF, OnLed2OnOff)
	ON_BN_CLICKED(IDC_LED3_ON_OFF, OnLed3OnOff)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_VARIABLE, OnVariable)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_VARIABLE, OnReleasedcaptureVariable)
	ON_EN_CHANGE(IDC_RID_BUTTON1, OnChangeRidButton1)
	ON_EN_CHANGE(IDC_RID_BUTTON2, OnChangeRidButton2)
	ON_EN_CHANGE(IDC_RID_BUTTON3, OnChangeRidButton3)
	ON_EN_CHANGE(IDC_RID_BUTTON4, OnChangeRidButton4)
	ON_EN_CHANGE(IDC_RID_BUTTON5, OnChangeRidButton5)
	ON_EN_CHANGE(IDC_RID_BUTTON6, OnChangeRidButton6)
	ON_EN_CHANGE(IDC_RID_BUTTON7, OnChangeRidButton7)
	ON_EN_CHANGE(IDC_RID_ROLLER1, OnChangeRidRoller1)
	ON_EN_CHANGE(IDC_RID_ROLLER2, OnChangeRidRoller2)
	ON_EN_CHANGE(IDC_RID_LED1, OnChangeRidLed1)
	ON_EN_CHANGE(IDC_RID_LED2, OnChangeRidLed2)
	ON_EN_CHANGE(IDC_RID_LED3, OnChangeRidLed3)
	ON_EN_CHANGE(IDC_RID_VARIABLE, OnChangeRidVariable)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_VARIABLE, OnCustomdrawVariable)
	ON_EN_CHANGE(IDC_RID_LED4, OnChangeRidLed4)
	ON_BN_CLICKED(IDC_LED4_ON_OFF, OnLed4OnOff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers

BOOL CGraphicView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_R1Ctrl.SetRange(0, 0xFF);
	m_R2Ctrl.SetRange(0, 0xFF);

	m_VariableCtrl.SetRange(0, 0xFF);

	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
    // Get report IDs
	m_RID_V.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVO", "00"));

	m_RID_R1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI1", "00"));
    m_RID_R2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI2", "00"));

	m_RID_L1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL1", "00"));
    m_RID_L2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL2", "00"));
	m_RID_L3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL3", "00"));
	m_RID_L4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL4", "00"));

	m_RID_B1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB1", "00"));
    m_RID_B2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB2", "00"));
	m_RID_B3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB3", "00"));
    m_RID_B4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB4", "00"));
	m_RID_B5.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB5", "00"));
    m_RID_B6.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB6", "00"));
	m_RID_B7.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB7", "00"));


    // Get design configuration
	BOOL RIDV = Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVO", TRUE);
	m_VariableCtrl.ShowWindow(RIDV);
	m_RID_V_Ctrl.ShowWindow(RIDV);
	m_VL_Ctrl.ShowWindow(RIDV);
	m_VICtrl.ShowWindow(RIDV);

	BOOL RIDR1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI1" , TRUE);
	m_R1Ctrl.ShowWindow(RIDR1);
	m_RID_R1_Ctrl.ShowWindow(RIDR1);
	m_RL1_Ctrl.ShowWindow(RIDR1);
	m_RV1_Ctrl.ShowWindow(RIDR1);

	BOOL RIDR2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI2", TRUE);
    m_R2Ctrl.ShowWindow(RIDR2);
	m_RID_R2_Ctrl.ShowWindow(RIDR2);
	m_RL2_Ctrl.ShowWindow(RIDR2);
	m_RV2_Ctrl.ShowWindow(RIDR2);

	BOOL RIDL1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL1", TRUE);
	m_L1Ctrl.ShowWindow(RIDL1);
	m_RID_L1_Ctrl.ShowWindow(RIDL1);
	m_Led1OnOff_Ctrl.ShowWindow(RIDL1);

    BOOL RIDL2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL2", TRUE);
	m_L2Ctrl.ShowWindow(RIDL2);
	m_RID_L2_Ctrl.ShowWindow(RIDL2);
	m_Led2OnOff_Ctrl.ShowWindow(RIDL2);

	BOOL RIDL3 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL3", TRUE);
	m_L3Ctrl.ShowWindow(RIDL3);
	m_RID_L3_Ctrl.ShowWindow(RIDL3);
	m_Led3OnOff_Ctrl.ShowWindow(RIDL3);

	BOOL RIDL4 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL4", TRUE);
	m_L4Ctrl.ShowWindow(RIDL4);
	m_RID_L4_Ctrl.ShowWindow(RIDL4);
	m_Led4OnOff_Ctrl.ShowWindow(RIDL4);

	BOOL RIDB1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB1", TRUE);
	m_B1Ctrl.ShowWindow(RIDB1);
	m_RID_B1_Ctrl.ShowWindow(RIDB1);
	m_BL1_Ctrl.ShowWindow(RIDB1);

    BOOL RIDB2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB2", TRUE);
	m_B2Ctrl.ShowWindow(RIDB2);
	m_RID_B2_Ctrl.ShowWindow(RIDB2);
	m_BL2_Ctrl.ShowWindow(RIDB2);

	BOOL RIDB3 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB3", TRUE);
	m_B3Ctrl.ShowWindow(RIDB3);
	m_RID_B3_Ctrl.ShowWindow(RIDB3);
	m_BL3_Ctrl.ShowWindow(RIDB3);


    BOOL RIDB4 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB4", TRUE);
	m_B4Ctrl.ShowWindow(RIDB4);
	m_RID_B4_Ctrl.ShowWindow(RIDB4);
	m_BL4_Ctrl.ShowWindow(RIDB4);

	BOOL RIDB5 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB5", TRUE);
	m_B5Ctrl.ShowWindow(RIDB5);
	m_RID_B5_Ctrl.ShowWindow(RIDB5);
	m_BL5_Ctrl.ShowWindow(RIDB5);

    BOOL RIDB6 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB6", TRUE);
	m_B6Ctrl.ShowWindow(RIDB6);
	m_RID_B6_Ctrl.ShowWindow(RIDB6);
	m_BL6_Ctrl.ShowWindow(RIDB6);

	BOOL RIDB7 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB7", TRUE);
	m_B7Ctrl.ShowWindow(RIDB7);
	m_RID_B7_Ctrl.ShowWindow(RIDB7);
	m_BL7_Ctrl.ShowWindow(RIDB7);

    UpdateData(FALSE);
	WRITE_ROPRT = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGraphicView::OnLed1OnOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OutputReport[0] = _tcstoul(m_RID_L1, 0, 16) ;

	if(m_Led1OnOffChecked)
	{
		OutputReport[1] = 0x01;
		m_L1Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));
	}
	else
	{
		OutputReport[1] = 0x00;
		m_L1Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	}

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;
} 

void CGraphicView::OnLed2OnOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OutputReport[0] = _tcstoul(m_RID_L2, 0, 16) ;

	if(m_Led2OnOffChecked)
		{
		OutputReport[1] = 0x01;
		m_L2Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));
	}
	else
	{
		OutputReport[1] = 0x00;
		m_L2Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	}

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;
}

void CGraphicView::OnLed3OnOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OutputReport[0] = _tcstoul(m_RID_L3, 0, 16) ;

	if(m_Led3OnOffChecked)
		{
		OutputReport[1] = 0x01;
		m_L3Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));
	}
	else
	{
		OutputReport[1] = 0x00;
		m_L3Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	}

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;
}

void CGraphicView::OnVariable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CGraphicView::OnReleasedcaptureVariable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OutputReport[0] = _tcstoul(m_RID_V, 0, 16) ;

	OutputReport[1] = m_VariableCtrl.GetPos();
	m_vi_val.Format("%2Xh", OutputReport[1]);

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;

	*pResult = 0;
}

void CGraphicView::OnChangeRidButton1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB1", (LPCTSTR)m_RID_B1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB2", (LPCTSTR)m_RID_B2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB3", (LPCTSTR)m_RID_B3);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB4", (LPCTSTR)m_RID_B4);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB5", (LPCTSTR)m_RID_B5);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB6", (LPCTSTR)m_RID_B6);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidButton7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
    CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB7", (LPCTSTR)m_RID_B7);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidRoller1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI1", (LPCTSTR)m_RID_R1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidRoller2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI2", (LPCTSTR)m_RID_R2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidLed1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL1", (LPCTSTR)m_RID_L1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidLed2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL2", (LPCTSTR)m_RID_L2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidLed3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL3", (LPCTSTR)m_RID_L3);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnChangeRidLed4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL4", (LPCTSTR)m_RID_L4);
	UpdateData(FALSE);
	
}

void CGraphicView::OnChangeRidVariable() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVO", (LPCTSTR)m_RID_V);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnCustomdrawVariable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(Oldm_RID_V != m_VariableCtrl.GetPos())
	{
	   OutputReport[0] = _tcstoul(m_RID_V, 0, 16) ;
	   OutputReport[1] = m_VariableCtrl.GetPos();
	   Oldm_RID_V      = m_VariableCtrl.GetPos();
	   m_vi_val.Format("%2Xh", OutputReport[1]);
	   WRITE_ROPRT = TRUE;
	}

	UpdateData(FALSE);

	*pResult = 0;
}



void CGraphicView::OnLed4OnOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OutputReport[0] = _tcstoul(m_RID_L4, 0, 16) ;

	if(m_Led4OnOffChecked)
	{
		OutputReport[1] = 0x01;
		m_L4Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));
	}
	else
	{
		OutputReport[1] = 0x00;
		m_L4Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	}

	UpdateData(FALSE);

	WRITE_ROPRT = TRUE;
}

void CGraphicView::OnUseSetReport() 
{
	// TODO: Add your control notification handler code here
	
}

void CGraphicView::OnUseSetFeature() 
{
	// TODO: Add your control notification handler code here
	
}
