/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : GraphicConfigView.cpp
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Graphic Configuration page implementation
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
#include "GraphicConfigView.h"
#include "Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicConfigView dialog


CGraphicConfigView::CGraphicConfigView(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphicConfigView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphicConfigView)
	m_B1 = _T("00");
	m_B2 = _T("00");
	m_B3 = _T("00");
	m_B4 = _T("00");
	m_B5 = _T("00");
	m_B6 = _T("00");
	m_B7 = _T("00");
	m_L1 = _T("00");
	m_L2 = _T("00");
	m_L3 = _T("00");
	m_L4 = _T("00");
	m_VO = _T("00");
	m_VI1 = _T("00");
	m_VI2 = _T("00");
	m_shb1 = FALSE;
	m_shb2 = FALSE;
	m_shb3 = FALSE;
	m_shb4 = FALSE;
	m_shb5 = FALSE;
	m_shb7 = FALSE;
	m_shb6 = FALSE;
	m_Buttons = FALSE;
	m_shl1 = FALSE;
	m_shl2 = FALSE;
	m_shl3 = FALSE;
	m_shvi1 = FALSE;
	m_shvi2 = FALSE;
	m_shvo = FALSE;
	m_shl4 = FALSE;
	
	//}}AFX_DATA_INIT
}


void CGraphicConfigView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphicConfigView)
	DDX_Control(pDX, B1, m_B1Ctrl);
	DDX_Control(pDX, B2, m_B2Ctrl);
	DDX_Control(pDX, B3, m_B3Ctrl);
	DDX_Control(pDX, B4, m_B4Ctrl);
	DDX_Control(pDX, B5, m_B5Ctrl);
	DDX_Control(pDX, B6, m_B6Ctrl);
	DDX_Control(pDX, B7, m_B7Ctrl);
	DDX_Control(pDX, L1, m_L1Ctrl);
	DDX_Control(pDX, L2, m_L2Ctrl);
	DDX_Control(pDX, L3, m_L3Ctrl);
	DDX_Control(pDX, L4, m_L4Ctrl);
	DDX_Control(pDX, VO, m_VOCtrl);
	DDX_Control(pDX, VI1, m_VI1Ctrl);
	DDX_Control(pDX, VI2, m_VI2Ctrl);
	DDX_Control(pDX, IDC_SHB7, m_shb7ctrl);
	DDX_Control(pDX, IDC_SHB6, m_shb6ctrl);
	DDX_Control(pDX, IDC_SHB5, m_shb5ctrl);
	DDX_Control(pDX, IDC_SHB4, m_shb4ctrl);
	DDX_Control(pDX, IDC_SHB3, m_shb3ctrl);
	DDX_Control(pDX, IDC_SHB1, m_shb1ctrl);
	DDX_Control(pDX, IDC_SHB2, m_shb2ctrl);
	DDX_Text(pDX, B1, m_B1);
	DDV_MaxChars(pDX, m_B1, 2);
	DDX_Text(pDX, B2, m_B2);
	DDV_MaxChars(pDX, m_B2, 2);
	DDX_Text(pDX, B3, m_B3);
	DDV_MaxChars(pDX, m_B3, 2);
	DDX_Text(pDX, B4, m_B4);
	DDV_MaxChars(pDX, m_B4, 2);
	DDX_Text(pDX, B5, m_B5);
	DDV_MaxChars(pDX, m_B5, 2);
	DDX_Text(pDX, B6, m_B6);
	DDV_MaxChars(pDX, m_B6, 2);
	DDX_Text(pDX, B7, m_B7);
	DDV_MaxChars(pDX, m_B7, 2);
	DDX_Text(pDX, L1, m_L1);
	DDV_MaxChars(pDX, m_L1, 2);
	DDX_Text(pDX, L2, m_L2);
	DDV_MaxChars(pDX, m_L2, 2);
	DDX_Text(pDX, L3, m_L3);
	DDV_MaxChars(pDX, m_L3, 2);
	DDX_Text(pDX, L4, m_L4);
	DDV_MaxChars(pDX, m_L4, 2);
	DDX_Text(pDX, VO, m_VO);
	DDV_MaxChars(pDX, m_VO, 2);
	DDX_Text(pDX, VI1, m_VI1);
	DDV_MaxChars(pDX, m_VI1, 2);
	DDX_Text(pDX, VI2, m_VI2);
	DDV_MaxChars(pDX, m_VI2, 2);
	DDX_Check(pDX, IDC_SHB1, m_shb1);
	DDX_Check(pDX, IDC_SHB2, m_shb2);
	DDX_Check(pDX, IDC_SHB3, m_shb3);
	DDX_Check(pDX, IDC_SHB4, m_shb4);
	DDX_Check(pDX, IDC_SHB5, m_shb5);
	DDX_Check(pDX, IDC_SHB7, m_shb7);
	DDX_Check(pDX, IDC_SHB6, m_shb6);
	DDX_Check(pDX, IDC_SHL1, m_shl1);
	DDX_Check(pDX, IDC_SHL2, m_shl2);
	DDX_Check(pDX, IDC_SHL3, m_shl3);
	DDX_Check(pDX, IDC_SHVI1, m_shvi1);
	DDX_Check(pDX, IDC_SHVI2, m_shvi2);
	DDX_Check(pDX, IDC_SHVO, m_shvo);
	DDX_Check(pDX, IDC_SHL4, m_shl4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphicConfigView, CDialog)
	//{{AFX_MSG_MAP(CGraphicConfigView)
	ON_EN_CHANGE(B1, OnChangeB1)
	ON_EN_CHANGE(B2, OnChangeB2)
	ON_EN_CHANGE(B3, OnChangeB3)
	ON_EN_CHANGE(B4, OnChangeB4)
	ON_EN_CHANGE(B5, OnChangeB5)
	ON_EN_CHANGE(B6, OnChangeB6)
	ON_EN_CHANGE(B7, OnChangeB7)
	ON_EN_CHANGE(L1, OnChangeL1)
	ON_EN_CHANGE(L2, OnChangeL2)
	ON_EN_CHANGE(L3, OnChangeL3)
	ON_EN_CHANGE(VI1, OnChangeVI1)
	ON_EN_CHANGE(VO, OnChangeVO)
	ON_EN_CHANGE(VI2, OnChangeVI2)
	ON_BN_CLICKED(IDC_SHB1, OnShb1)
	ON_BN_CLICKED(IDC_SHB2, OnShb2)
	ON_BN_CLICKED(IDC_SHB3, OnShb3)
	ON_BN_CLICKED(IDC_SHB4, OnShb4)
	ON_BN_CLICKED(IDC_SHB5, OnShb5)
	ON_BN_CLICKED(IDC_SHB6, OnShb6)
	ON_BN_CLICKED(IDC_SHB7, OnShb7)
	ON_BN_CLICKED(IDC_SHL1, OnShl1)
	ON_BN_CLICKED(IDC_SHL2, OnShl2)
	ON_BN_CLICKED(IDC_SHL3, OnShl3)
	ON_BN_CLICKED(IDC_SHVI1, OnShvi1)
	ON_BN_CLICKED(IDC_SHVI2, OnShvi2)
	ON_BN_CLICKED(IDC_SHVO, OnShvo)
	ON_BN_CLICKED(IDC_SHL4, OnShl4)
	ON_EN_CHANGE(L4, OnChangeL4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicConfigView message handlers

void CGraphicConfigView::OnChangeB1() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB1", (LPCTSTR)m_B1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB2() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB2", (LPCTSTR)m_B2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB3() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB3", (LPCTSTR)m_B3);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB4() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB4", (LPCTSTR)m_B4);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB5() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB5", (LPCTSTR)m_B5);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB6() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB6", (LPCTSTR)m_B6);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeB7() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB7", (LPCTSTR)m_B7);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeL1() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL1", (LPCTSTR)m_L1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeL2() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL2", (LPCTSTR)m_L2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeL3() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL3", (LPCTSTR)m_L3);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeVI1() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI1", (LPCTSTR)m_VI1);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeVI2() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI2", (LPCTSTR)m_VI2);
	UpdateData(FALSE);

	// TODO: Add your control notification handler code here
	
}

void CGraphicConfigView::OnChangeVO() 
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
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVO", (LPCTSTR)m_VO);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}



void CGraphicConfigView::OnShb1() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB1", m_shb1);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb2() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB2", m_shb2);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb3() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB3", m_shb3);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb4() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB4", m_shb4);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb5() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB5", m_shb5);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb6() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB6", m_shb6);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShb7() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDB7", m_shb7);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShl1() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDL1", m_shl1);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShl2() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDL2", m_shl2);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShl3() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDL3", m_shl3);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShvi1() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI1", m_shvi1);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShvi2() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI2", m_shvi2);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShvo() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDVO", m_shvo);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnShl4() 
{
	// TODO: Add your control notification handler code here
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteBool((LPCTSTR)"Design",(LPCTSTR)"RIDL4", m_shl4);
	UpdateData(FALSE);
}

void CGraphicConfigView::OnChangeL4() 
{
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	UpdateData(TRUE);
	Ini.WriteString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL4", (LPCTSTR)m_L4);
	UpdateData(FALSE);
}
