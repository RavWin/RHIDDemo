/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : UsbHidDemonstratorDlg.cpp
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : Main dialog implementation file
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#include "stdafx.h"
#include "INC\hidsdi++.h"
#include "INC\hid.h"
#include "INC\setupapi.h"
#include "INC\usb100.h"
#include "Ini.h"

#include <dbt.h>

#include "UsbHidDemonstrator.h"
#include "UsbHidDemonstratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GUID Guid;
HANDLE HidDeviceObject;
HIDP_CAPS Capabilities;
OVERLAPPED	HIDOverlapped;
DWORD NumberOfBytesRead;
DWORD NumberOfBytesWriten;

HANDLE ReadThread;
DWORD ReadThreadId;
HANDLE WriteThread;
DWORD WriteThreadId;

int Use_Setxxx = 0;


extern BYTE InputReport[256];
extern BYTE OutputReport[256];
extern BOOL WRITE_ROPRT;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbHidDemonstratorDlg dialog

void CUsbHidDemonstratorDlg::GetDeviceCapabilities()
{
	//Get the Capabilities structure for the device.

	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/

	HidD_GetPreparsedData (HidDeviceObject, &PreparsedData);
	//DisplayLastError("HidD_GetPreparsedData: ");

	/*
	API function: HidP_GetCaps
	Learn the device's capabilities.
	For standard devices such as joysticks, you can find out the specific
	capabilities of the device.
	For a custom device, the software will probably know what the device is capable of,
	and the call only verifies the information.
	Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
	Returns: a Capabilities structure containing the information.
	*/
	
	HidP_GetCaps (PreparsedData, &Capabilities);
	//DisplayLastError("HidP_GetCaps: ");

	//Display the capabilities

    m_DesrciptorView_frm.m_CapabilitiesList.Format("");

	CString ValueToDisplay;

	ValueToDisplay.Format("%s%X", "Usage Page:                      \t\t", Capabilities.UsagePage);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Input Report Byte Length:        \t\t", Capabilities.InputReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Output Report Byte Length:       \t\t", Capabilities.OutputReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Feature Report Byte Length:      \t\t", Capabilities.FeatureReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Link Collection Nodes: \t", Capabilities.NumberLinkCollectionNodes);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Input Button Caps:     \t\t", Capabilities.NumberInputButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputValue Caps:       \t\t", Capabilities.NumberInputValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputData Indices:     \t\t", Capabilities.NumberInputDataIndices);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Button Caps:    \t", Capabilities.NumberOutputButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Value Caps:     \t\t", Capabilities.NumberOutputValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Data Indices:   \t\t", Capabilities.NumberOutputDataIndices);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Button Caps:   \t", Capabilities.NumberFeatureButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Value Caps:    \t", Capabilities.NumberFeatureValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Data Indices:  \t", Capabilities.NumberFeatureDataIndices);
	DisplayData(ValueToDisplay);

	//No need for PreparsedData any more, so free the memory it's using.

	HidD_FreePreparsedData(PreparsedData);

	//DisplayLastError("HidD_FreePreparsedData: ") ;
}

BOOL CUsbHidDemonstratorDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
	_DEV_BROADCAST_HEADER *hdr;

	if ((nEventType == DBT_DEVICEREMOVECOMPLETE))// || (nEventType == 0x0007))
	{
		hdr=(_DEV_BROADCAST_HEADER*)dwData;
		if (hdr->dbcd_devicetype==DBT_DEVTYP_DEVICEINTERFACE)
		{
			RefreshDevices();
		}
	}
	if ((nEventType == DBT_DEVICEARRIVAL))
	{
		hdr=(_DEV_BROADCAST_HEADER*)dwData;
		if (hdr->dbcd_devicetype==DBT_DEVTYP_DEVICEINTERFACE)
			RefreshDevices();
	}
	return TRUE;
}

CUsbHidDemonstratorDlg::CUsbHidDemonstratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsbHidDemonstratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUsbHidDemonstratorDlg)
	m_HidTarget = _T("");
	m_UseSetxxx = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsbHidDemonstratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbHidDemonstratorDlg)
	DDX_Control(pDX, IDC_GRAPHIC_CONFIG, m_GraphicConfigCtrl);
	DDX_Control(pDX, IDC_SHOW_REPORT_VIEW, m_TransfereCtrl);
	DDX_Control(pDX, IDC_SHOW_DESCROPTOR_VIEW, m_CapabilitiesCtrl);
	DDX_Control(pDX, IDC_SHOW_GRAPHIC_VIEW, m_GraphicViewCtrl);
	DDX_Control(pDX, IDC_TARGETS_CTRL, m_TargetsCtrl);
	DDX_Control(pDX, IDC_HID_TARGETS, m_HidTargetsCtrl);
	DDX_CBString(pDX, IDC_HID_TARGETS, m_HidTarget);
	DDX_Radio(pDX, IDC_USE_SET_REPORT, m_UseSetxxx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUsbHidDemonstratorDlg, CDialog)
	//{{AFX_MSG_MAP(CUsbHidDemonstratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_DESCROPTOR_VIEW, OnShowDescroptorView)
	ON_BN_CLICKED(IDC_SHOW_FEATURE_VIEW, OnShowFeatureView)
	ON_BN_CLICKED(IDC_SHOW_REPORT_VIEW, OnShowReportView)
	ON_BN_CLICKED(IDC_SHOW_GRAPHIC_VIEW, OnShowGraphicView)
	ON_CBN_SELCHANGE(IDC_HID_TARGETS, OnSelchangeHidTargets)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_GRAPHIC_CONFIG, OnGraphicConfig)
	ON_BN_CLICKED(IDC_SET_FEATURE, OnSetFeature)
	ON_BN_CLICKED(IDC_GET_FEATURE, OnGetFeature)
	ON_BN_CLICKED(IDC_USE_SET_REPORT, OnUseSetReport)
	ON_BN_CLICKED(IDC_USE_SET_FEATURE, OnUseSetFeature)
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbHidDemonstratorDlg message handlers

BOOL CUsbHidDemonstratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_GraphicViewCtrl.SetIconID(IDI_ICON1);
	m_GraphicViewCtrl.SetIconRight(FALSE);
	//m_GraphicViewCtrl.SetTipText("Graphic view");
	//m_GraphicViewCtrl.SetFaceName("Graphic view");

	m_CapabilitiesCtrl.SetIconID(IDI_ICON3);
	m_CapabilitiesCtrl.SetIconRight(FALSE);
	//m_CapabilitiesCtrl.SetTipText("Device capabilities");
	//m_CapabilitiesCtrl.SetFaceName("Device capabilities");

	m_TransfereCtrl.SetIconID(IDI_ICON2);
    m_TransfereCtrl.SetIconRight(FALSE);
	//m_TransfereCtrl.SetTipText("Input/Output transfere");
	//m_TransfereCtrl.SetFaceName("Input/Output transfere");

	m_GraphicConfigCtrl.SetIconID(IDI_ICON4);
    m_GraphicConfigCtrl.SetIconRight(FALSE);
	//m_GraphicConfigCtrl.SetTipText("Graphic view customization");
	//m_GraphicConfigCtrl.SetFaceName("Graphic view customization");



	DEV_BROADCAST_DEVICEINTERFACE filter={0};
	filter.dbcc_size=sizeof(filter);
	filter.dbcc_devicetype= DBT_DEVTYP_DEVICEINTERFACE;

	HidD_GetHidGuid(&Guid);
	filter.dbcc_classguid=Guid;
	RegisterDeviceNotification(m_hWnd, (PVOID)&filter, DEVICE_NOTIFY_WINDOW_HANDLE);
	
	m_ReportView_frm.Create(IDD_REPORT_VIEW,this); 
    m_GraphicView_frm.Create(IDD_GRAPHIC_VIEW,this);
    m_FeatureView_frm.Create(IDD_FEATURE_VIEW,this);
    m_DesrciptorView_frm.Create(IDD_DESCRIPTOR_VIEW,this);
	m_GraphicConfig_frm.Create(IDD_GRAPHIC_CONFIG,this);;

	ASSERT(IsWindow(m_ReportView_frm.m_hWnd)); 
    ASSERT(IsWindow(m_GraphicView_frm.m_hWnd));
    ASSERT(IsWindow(m_FeatureView_frm.m_hWnd));
    ASSERT(IsWindow(m_DesrciptorView_frm.m_hWnd));
	ASSERT(IsWindow(m_GraphicConfig_frm.m_hWnd));

	CRect rect;
    CWnd *pWnd = GetDlgItem(IDC_FRAMES_CONTAINER);
    ASSERT(pWnd != NULL);
    ASSERT(IsWindow(pWnd->m_hWnd));
    pWnd->GetWindowRect(&rect);
    ScreenToClient(&rect);

	m_ReportView_frm.SetWindowPos(NULL, rect.left + 5, rect.top + 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
    m_GraphicView_frm.SetWindowPos(NULL, rect.left + 5, rect.top + 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
    m_FeatureView_frm.SetWindowPos(NULL, rect.left + 5, rect.top + 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
    m_DesrciptorView_frm.SetWindowPos(NULL, rect.left + 5, rect.top + 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	m_GraphicConfig_frm.SetWindowPos(NULL, rect.left + 5, rect.top + 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );

	m_ReportView_frm.EnableWindow(TRUE);
    m_GraphicView_frm.EnableWindow(TRUE);
    m_FeatureView_frm.EnableWindow(TRUE);
    m_DesrciptorView_frm.EnableWindow(TRUE);
	m_GraphicConfig_frm.EnableWindow(TRUE);

	m_DesrciptorView_frm.ShowWindow(TRUE);
	// TODO: Add extra initialization here
	
	RefreshDevices();

	SetTimer(1,1, NULL);

	if (ReadThread == NULL) 
	{
		ReadThread = CreateThread( NULL,                        
						   0,                           
						   ReadReport,     
						   NULL,              
						   0,                           
						   &ReadThreadId);   
	}
 
		
	// We check if the thread est ok 
	if (ReadThread == NULL) 
	{
		AfxMessageBox( "Error occured when creating Read thread (%d)\n", GetLastError() ); 
	}


	if (WriteThread == NULL) 
	{
		WriteThread = CreateThread( NULL,                        
						   0,                           
						   WriteReport,     
						   NULL,              
						   0,                           
						   &WriteThreadId); 
	}
 
										/// We check if the thread est ok 
	if (WriteThread == NULL) 
	{
		AfxMessageBox( "Error occured when creating Write thread (%d)\n", GetLastError() ); 
	}
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUsbHidDemonstratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUsbHidDemonstratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUsbHidDemonstratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUsbHidDemonstratorDlg::OnShowDescroptorView() 
{
	// TODO: Add your control notification handler code here
	m_DesrciptorView_frm.ShowWindow(SW_SHOW);
	m_FeatureView_frm.ShowWindow(SW_HIDE);
	m_ReportView_frm.ShowWindow(SW_HIDE);
    m_GraphicView_frm.ShowWindow(SW_HIDE);
	m_GraphicConfig_frm.ShowWindow(SW_HIDE);
}

void CUsbHidDemonstratorDlg::OnShowFeatureView() 
{
	// TODO: Add your control notification handler code here
    /*m_DesrciptorView_frm.ShowWindow(SW_HIDE);
	m_FeatureView_frm.ShowWindow(SW_SHOW);
	m_ReportView_frm.ShowWindow(SW_HIDE);
    m_GraphicView_frm.ShowWindow(SW_HIDE);
	m_GraphicConfig_frm.ShowWindow(SW_HIDE);

	if (ReadThread != NULL)
       CloseHandle(ReadThread);

	if (WriteThread != NULL)
       CloseHandle(WriteThread);*/

}

void CUsbHidDemonstratorDlg::OnShowReportView() 
{
	// TODO: Add your control notification handler code here
	m_DesrciptorView_frm.ShowWindow(SW_HIDE);
	m_FeatureView_frm.ShowWindow(SW_HIDE);
	m_ReportView_frm.ShowWindow(SW_SHOW);
    m_GraphicView_frm.ShowWindow(SW_HIDE);
	m_GraphicConfig_frm.ShowWindow(SW_HIDE);

	m_ReportView_frm.UpdateData(TRUE);

	m_ReportView_frm.m_OutPutHxEditLength.Format("%4x", Capabilities.FeatureReportByteLength/*OutputReportByteLength*/);
	m_ReportView_frm.m_OutPutHxEditLength.Replace((LPCTSTR)" ", (LPCTSTR)"0");

	m_ReportView_frm.m_InPutHxEditLength.Format("%4x", Capabilities.InputReportByteLength);
	m_ReportView_frm.m_InPutHxEditLength.Replace((LPCTSTR)" ", (LPCTSTR)"0");

	m_ReportView_frm.UpdateData(FALSE);

    m_ReportView_frm.SetTimer(1,10,NULL);
}

void CUsbHidDemonstratorDlg::OnShowGraphicView() 
{
	// TODO: Add your control notification handler code here
	m_DesrciptorView_frm.ShowWindow(SW_HIDE);
	m_FeatureView_frm.ShowWindow(SW_HIDE);
	m_ReportView_frm.ShowWindow(SW_HIDE);
    m_GraphicView_frm.ShowWindow(SW_SHOW);
	m_GraphicConfig_frm.ShowWindow(SW_HIDE);

    // Get report IDs

	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	m_GraphicView_frm.UpdateData(TRUE);
    
	m_GraphicView_frm.m_RID_V.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVO", "00"));

	m_GraphicView_frm.m_RID_R1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI1", "00"));
    m_GraphicView_frm.m_RID_R2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI2", "00"));

	m_GraphicView_frm.m_RID_L1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL1", "00"));
    m_GraphicView_frm.m_RID_L2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL2", "00"));
	m_GraphicView_frm.m_RID_L3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL3", "00"));
	m_GraphicView_frm.m_RID_L4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL4", "00"));

	m_GraphicView_frm.m_RID_B1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB1", "00"));
    m_GraphicView_frm.m_RID_B2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB2", "00"));
	m_GraphicView_frm.m_RID_B3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB3", "00"));
    m_GraphicView_frm.m_RID_B4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB4", "00"));
	m_GraphicView_frm.m_RID_B5.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB5", "00"));
    m_GraphicView_frm.m_RID_B6.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB6", "00"));
	m_GraphicView_frm.m_RID_B7.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB7", "00"));

	// Get design configuration
	BOOL RIDV = Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVO", TRUE);
	m_GraphicView_frm.m_VariableCtrl.ShowWindow(RIDV);
	m_GraphicView_frm.m_RID_V_Ctrl.ShowWindow(RIDV);
	m_GraphicView_frm.m_VL_Ctrl.ShowWindow(RIDV);
	m_GraphicView_frm.m_VICtrl.ShowWindow(RIDV);

	BOOL RIDR1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI1" , TRUE);
	m_GraphicView_frm.m_R1Ctrl.ShowWindow(RIDR1);
	m_GraphicView_frm.m_RID_R1_Ctrl.ShowWindow(RIDR1);
	m_GraphicView_frm.m_RL1_Ctrl.ShowWindow(RIDR1);
	m_GraphicView_frm.m_RV1_Ctrl.ShowWindow(RIDR1);

	BOOL RIDR2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI2", TRUE);
    m_GraphicView_frm.m_R2Ctrl.ShowWindow(RIDR2);
	m_GraphicView_frm.m_RID_R2_Ctrl.ShowWindow(RIDR2);
	m_GraphicView_frm.m_RL2_Ctrl.ShowWindow(RIDR2);
	m_GraphicView_frm.m_RV2_Ctrl.ShowWindow(RIDR2);

	BOOL RIDL1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL1", TRUE);
	m_GraphicView_frm.m_L1Ctrl.ShowWindow(RIDL1);
	m_GraphicView_frm.m_RID_L1_Ctrl.ShowWindow(RIDL1);
	m_GraphicView_frm.m_Led1OnOff_Ctrl.ShowWindow(RIDL1);

    BOOL RIDL2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL2", TRUE);
	m_GraphicView_frm.m_L2Ctrl.ShowWindow(RIDL2);
	m_GraphicView_frm.m_RID_L2_Ctrl.ShowWindow(RIDL2);
	m_GraphicView_frm.m_Led2OnOff_Ctrl.ShowWindow(RIDL2);

	BOOL RIDL3 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL3", TRUE);
	m_GraphicView_frm.m_L3Ctrl.ShowWindow(RIDL3);
	m_GraphicView_frm.m_RID_L3_Ctrl.ShowWindow(RIDL3);
	m_GraphicView_frm.m_Led3OnOff_Ctrl.ShowWindow(RIDL3);

	BOOL RIDL4 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL4", TRUE);
	m_GraphicView_frm.m_L4Ctrl.ShowWindow(RIDL4);
	m_GraphicView_frm.m_RID_L4_Ctrl.ShowWindow(RIDL4);
	m_GraphicView_frm.m_Led4OnOff_Ctrl.ShowWindow(RIDL4);

	BOOL RIDB1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB1", TRUE);
	m_GraphicView_frm.m_B1Ctrl.ShowWindow(RIDB1);
	m_GraphicView_frm.m_RID_B1_Ctrl.ShowWindow(RIDB1);
	m_GraphicView_frm.m_BL1_Ctrl.ShowWindow(RIDB1);

    BOOL RIDB2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB2", TRUE);
	m_GraphicView_frm.m_B2Ctrl.ShowWindow(RIDB2);
	m_GraphicView_frm.m_RID_B2_Ctrl.ShowWindow(RIDB2);
	m_GraphicView_frm.m_BL2_Ctrl.ShowWindow(RIDB2);

	BOOL RIDB3 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB3", TRUE);
	m_GraphicView_frm.m_B3Ctrl.ShowWindow(RIDB3);
	m_GraphicView_frm.m_RID_B3_Ctrl.ShowWindow(RIDB3);
	m_GraphicView_frm.m_BL3_Ctrl.ShowWindow(RIDB3);


    BOOL RIDB4 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB4", TRUE);
	m_GraphicView_frm.m_B4Ctrl.ShowWindow(RIDB4);
	m_GraphicView_frm.m_RID_B4_Ctrl.ShowWindow(RIDB4);
	m_GraphicView_frm.m_BL4_Ctrl.ShowWindow(RIDB4);

	BOOL RIDB5 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB5", TRUE);
	m_GraphicView_frm.m_B5Ctrl.ShowWindow(RIDB5);
	m_GraphicView_frm.m_RID_B5_Ctrl.ShowWindow(RIDB5);
	m_GraphicView_frm.m_BL5_Ctrl.ShowWindow(RIDB5);

    BOOL RIDB6 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB6", TRUE);
	m_GraphicView_frm.m_B6Ctrl.ShowWindow(RIDB6);
	m_GraphicView_frm.m_RID_B6_Ctrl.ShowWindow(RIDB6);
	m_GraphicView_frm.m_BL6_Ctrl.ShowWindow(RIDB6);

	BOOL RIDB7 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB7", TRUE);
	m_GraphicView_frm.m_B7Ctrl.ShowWindow(RIDB7);
	m_GraphicView_frm.m_RID_B7_Ctrl.ShowWindow(RIDB7);
	m_GraphicView_frm.m_BL7_Ctrl.ShowWindow(RIDB7);

	m_GraphicView_frm.UpdateData(FALSE);

	m_ReportView_frm.SetTimer(1,10,NULL);
}

void CUsbHidDemonstratorDlg::OnGraphicConfig() 
{
	// TODO: Add your control notification handler code here
	m_DesrciptorView_frm.ShowWindow(SW_HIDE);
	m_FeatureView_frm.ShowWindow(SW_HIDE);
	m_ReportView_frm.ShowWindow(SW_HIDE);
    m_GraphicView_frm.ShowWindow(SW_HIDE);
	m_GraphicConfig_frm.ShowWindow(SW_SHOW);

	// Get report IDs
	CString Path(AfxGetApp()->m_pszHelpFilePath);
	char Drive[3], Dir[256], Fname[256], Ext[256];
    _splitpath(Path,Drive,Dir,Fname,Ext);
	
	CString ConfFile;
	ConfFile.Format("%s%s%s", Drive, Dir , "Conf\\Default.conf");

	CIni Ini((LPCSTR)ConfFile);

	m_GraphicConfig_frm.UpdateData(TRUE);
    
	m_GraphicConfig_frm.m_VO.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVO", "00"));

	m_GraphicConfig_frm.m_VI1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI1", "00"));
    m_GraphicConfig_frm.m_VI2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDVI2", "00"));

	m_GraphicConfig_frm.m_L1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL1", "00"));
    m_GraphicConfig_frm.m_L2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL2", "00"));
	m_GraphicConfig_frm.m_L3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL3", "00"));
	m_GraphicConfig_frm.m_L4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDL4", "00"));

	m_GraphicConfig_frm.m_B1.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB1", "00"));
    m_GraphicConfig_frm.m_B2.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB2", "00"));
	m_GraphicConfig_frm.m_B3.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB3", "00"));
    m_GraphicConfig_frm.m_B4.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB4", "00"));
	m_GraphicConfig_frm.m_B5.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB5", "00"));
    m_GraphicConfig_frm.m_B6.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB6", "00"));
	m_GraphicConfig_frm.m_B7.Format((LPCTSTR) Ini.GetString((LPCTSTR)"RIDs",(LPCTSTR)"RIDB7", "00"));

	// Get design configuration
	/*BOOL RIDV = Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVO", TRUE);*/
	m_GraphicConfig_frm.m_shvo =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVO" , TRUE);
	m_GraphicConfig_frm.m_shvi1 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI1" , TRUE);
	m_GraphicConfig_frm.m_shvi2 =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDVI2", TRUE);
	m_GraphicConfig_frm.m_shl1  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL1", TRUE);
    m_GraphicConfig_frm.m_shl2  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL2", TRUE);
	m_GraphicConfig_frm.m_shl3  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL3", TRUE);
	m_GraphicConfig_frm.m_shl4  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDL4", TRUE);
	m_GraphicConfig_frm.m_shb1  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB1", TRUE);
    m_GraphicConfig_frm.m_shb2  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB2", TRUE);
    m_GraphicConfig_frm.m_shb3  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB3", TRUE);
    m_GraphicConfig_frm.m_shb4  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB4", TRUE);
	m_GraphicConfig_frm.m_shb5  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB5", TRUE);
    m_GraphicConfig_frm.m_shb6  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB6", TRUE);
	m_GraphicConfig_frm.m_shb7  =Ini.GetBool((LPCTSTR)"Design",(LPCTSTR)"RIDB7", TRUE);


	m_GraphicConfig_frm.UpdateData(FALSE);
}

void CUsbHidDemonstratorDlg::RefreshDevices()
{
	int		i,j;
 
	char	Product[253];
	CString	Prod, String;

	int Sel=m_HidTargetsCtrl.GetCurSel();
	CString LinkCurSel;

	if (Sel!=-1)
		m_TargetsCtrl.GetText(Sel, LinkCurSel);

	m_HidTargetsCtrl.ResetContent();
	m_TargetsCtrl.ResetContent();

	HDEVINFO info;
    info=SetupDiGetClassDevs(&Guid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if (info!=INVALID_HANDLE_VALUE)  
	{
		DWORD devIndex;
		SP_INTERFACE_DEVICE_DATA ifData;
		ifData.cbSize=sizeof(ifData);

		for (devIndex=0;SetupDiEnumDeviceInterfaces(info, NULL, &Guid, devIndex, &ifData);++devIndex)
		{
			DWORD needed;

			SetupDiGetDeviceInterfaceDetail(info, &ifData, NULL, 0, &needed, NULL);

			PSP_INTERFACE_DEVICE_DETAIL_DATA detail=(PSP_INTERFACE_DEVICE_DETAIL_DATA)new BYTE[needed];
			detail->cbSize=sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
			SP_DEVINFO_DATA did={sizeof(SP_DEVINFO_DATA)};
			
			if (SetupDiGetDeviceInterfaceDetail(info, &ifData, detail, needed, NULL, &did))
			{
				// Add the link to the list of all HID devices
				if(strstr(detail->DevicePath, "vid_0483") != NULL)
				{
					CString Tmp;
					Tmp=detail->DevicePath;
					Tmp.MakeUpper();
					m_TargetsCtrl.AddString(Tmp);
				}
			}
			else
				m_TargetsCtrl.AddString("");

			if(strstr(detail->DevicePath, "vid_0483") != NULL)
			{
				if (SetupDiGetDeviceRegistryProperty(info, &did, SPDRP_DEVICEDESC, NULL, (PBYTE)Product, 253, NULL))
					Prod= Product;
				else
					Prod="(Unnamed HID device)";
					// Add the name of the device
				m_HidTargetsCtrl.AddString(Prod);
			}


			delete[] (PBYTE)detail;
		}
		SetupDiDestroyDeviceInfoList(info);
	}

	Sel=0;
	if (LinkCurSel!="")
	{
		Sel=m_TargetsCtrl.FindString(0, LinkCurSel);
		if (Sel==-1)
			Sel=0;
	}

	m_HidTargetsCtrl.SetCurSel(Sel);
    OnSelchangeHidTargets();
}

void CUsbHidDemonstratorDlg::OnSelchangeHidTargets() 
{

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char* DevicePath = (char*)malloc(256);
    m_TargetsCtrl.GetText(m_HidTargetsCtrl.GetCurSel(), DevicePath); 

	HidDeviceObject = CreateFile (
                              (LPCTSTR)DevicePath,
						      GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL, //&SecurityAttributes,  //no SECURITY_ATTRIBUTES structure
                              OPEN_EXISTING,  //No special create flags
                              FILE_FLAG_OVERLAPPED, // No special attributes
                              NULL); // No template file

	if (HidDeviceObject != INVALID_HANDLE_VALUE)
	{
		 PHIDD_ATTRIBUTES Attributes = (PHIDD_ATTRIBUTES)malloc(sizeof(HIDD_ATTRIBUTES));
	     if(HidD_GetAttributes(HidDeviceObject, Attributes))
		 {
			m_DesrciptorView_frm.UpdateData(TRUE);

			m_DesrciptorView_frm.m_PIDValue.Format("0x%4X", Attributes->ProductID );
			m_DesrciptorView_frm.m_VIDValue.Format("0x%4X", Attributes->VendorID );
			m_DesrciptorView_frm.m_VersionNumber.Format("0x%4X", Attributes->VersionNumber );

			m_DesrciptorView_frm.m_PIDValue.Replace((LPCTSTR)" ", (LPCTSTR)"0");
			m_DesrciptorView_frm.m_VIDValue.Replace((LPCTSTR)" ", (LPCTSTR)"0");
			m_DesrciptorView_frm.m_VersionNumber.Replace((LPCTSTR)" ", (LPCTSTR)"0");

			GetDeviceCapabilities();

			m_ReportView_frm.UpdateData(TRUE);

			m_ReportView_frm.m_OutPutHxEditLength.Format("%4x", Capabilities.OutputReportByteLength);
			m_ReportView_frm.m_OutPutHxEditLength.Replace((LPCTSTR)" ", (LPCTSTR)"0");

			m_ReportView_frm.m_InPutHxEditLength.Format("%4x", Capabilities.InputReportByteLength);
			m_ReportView_frm.m_InPutHxEditLength.Replace((LPCTSTR)" ", (LPCTSTR)"0");

			WORD  OutSize = _tcstoul(m_ReportView_frm.m_OutPutHxEditLength, 0, 16); 
			m_ReportView_frm.m_OutputHexEditorCtrl.SetDataSize(OutSize);

			WORD  InSize = _tcstoul(m_ReportView_frm.m_InPutHxEditLength, 0, 16); 
			m_ReportView_frm.m_InputHexEditorCtrl.SetDataSize(InSize);

			m_ReportView_frm.UpdateData(FALSE);

			m_DesrciptorView_frm.UpdateData(FALSE);
		 }
	}


	UpdateData(FALSE);
}

BOOL CUsbHidDemonstratorDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

LRESULT CUsbHidDemonstratorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::WindowProc(message, wParam, lParam);
}

void CUsbHidDemonstratorDlg::DisplayData(CString Data)
{
   UpdateData(TRUE);

   m_DesrciptorView_frm.m_CapabilitiesList.Format(m_DesrciptorView_frm.m_CapabilitiesList + "\n" + Data);

   UpdateData(FALSE);
}

void CUsbHidDemonstratorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_GraphicView_frm.UpdateData(TRUE);

	BYTE ReporID    = InputReport[0];
	BYTE ReporValue = InputReport[1];

    BYTE ReportID_R1 = _tcstoul(m_GraphicView_frm.m_RID_R1, 0, 16) ;
	BYTE ReportID_R2 = _tcstoul(m_GraphicView_frm.m_RID_R2, 0, 16) ;

	BYTE ReportID_B1 = _tcstoul(m_GraphicView_frm.m_RID_B1, 0, 16) ;
	BYTE ReportID_B2 = _tcstoul(m_GraphicView_frm.m_RID_B2, 0, 16) ;
	BYTE ReportID_B3 = _tcstoul(m_GraphicView_frm.m_RID_B3, 0, 16) ;
	BYTE ReportID_B4 = _tcstoul(m_GraphicView_frm.m_RID_B4, 0, 16) ;
	BYTE ReportID_B5 = _tcstoul(m_GraphicView_frm.m_RID_B5, 0, 16) ;
	BYTE ReportID_B6 = _tcstoul(m_GraphicView_frm.m_RID_B6, 0, 16) ;
	BYTE ReportID_B7 = _tcstoul(m_GraphicView_frm.m_RID_B7, 0, 16) ;

    m_GraphicView_frm.UpdateData(FALSE);

	// Rollers update
	if(ReporID == ReportID_R1/*0x03*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		m_GraphicView_frm.m_R1Ctrl.SetPos(ReporValue);
        m_GraphicView_frm.m_RV1.Format("%2Xh", ReporValue); 

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_R2/*0x03*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		m_GraphicView_frm.m_R2Ctrl.SetPos(ReporValue);
        m_GraphicView_frm.m_RV2.Format("%2Xh", ReporValue); 

		m_GraphicView_frm.UpdateData(FALSE);
	}

	// Buttons update
	if(ReporID == ReportID_B1 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B1Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B1Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B2 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B2Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B2Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B3 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B3Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B3Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B4 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B4Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B4Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B5 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B5Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B5Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B6 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B6Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B6Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	if(ReporID == ReportID_B7 /*0x02*/) 
	{
		m_GraphicView_frm.UpdateData(TRUE);

		if(ReporValue == 0x00)
		   m_GraphicView_frm.m_B7Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF));
	    else /*if(InputReport[0] == 0x00)*/
		   m_GraphicView_frm.m_B7Ctrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LED_ON));

		m_GraphicView_frm.UpdateData(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}

DWORD WINAPI CUsbHidDemonstratorDlg::ReadReport(void*)
{

    while(TRUE)
	{
		if(!WRITE_ROPRT)
		{
			if (HidDeviceObject != INVALID_HANDLE_VALUE)
			{
				CancelIo(HidDeviceObject);
				//InputReport[0]=0;
				int Result = ReadFile 
				(HidDeviceObject, 
				&InputReport, 
				Capabilities.InputReportByteLength, 
				&NumberOfBytesRead,
				(LPOVERLAPPED) &HIDOverlapped);
			}
		}
		_sleep(25);
	}

}

DWORD WINAPI CUsbHidDemonstratorDlg::WriteReport(void*)
{
	BOOL Result = TRUE;
    while(TRUE)
	{
		if(WRITE_ROPRT)
		{
			if (HidDeviceObject != INVALID_HANDLE_VALUE)
			{
				CancelIo(HidDeviceObject);
				
				if(Use_Setxxx == 1 )
				{
					Result = HidD_SetFeature 
					(HidDeviceObject,
					   OutputReport,
					   Capabilities.FeatureReportByteLength); 
				}
				else
				{
				    Result = WriteFile 
					   (HidDeviceObject, 
					   &OutputReport, 
					   Capabilities.OutputReportByteLength, 
					   &NumberOfBytesWriten,
					   (LPOVERLAPPED) &HIDOverlapped);
				}


				WRITE_ROPRT = FALSE;
			}
		}
		_sleep(25);
	}
}



void CUsbHidDemonstratorDlg::OnSetFeature() 
{
	if (HidDeviceObject != INVALID_HANDLE_VALUE)
	{
		BYTE Fetaure_buffer[0xFF];
		Fetaure_buffer[0] = 0x01;
        Fetaure_buffer[1] = 0x01;
		/*BOOLEAN __stdcall */HidD_SetFeature (
		/*IN    HANDLE*/   HidDeviceObject,
		/*IN    PVOID    ReportBuffer*/ Fetaure_buffer,
		/*IN    ULONG    ReportBufferLength*/ Capabilities.OutputReportByteLength
		); 
	}
}

void CUsbHidDemonstratorDlg::OnGetFeature() 
{
	if (HidDeviceObject != INVALID_HANDLE_VALUE)
	{
		BYTE Fetaure_buffer[0xFF];
		Fetaure_buffer[0] = 0x01;
        Fetaure_buffer[1] = 0x00;
		/*BOOLEAN __stdcall */HidD_SetFeature (
		/*IN    HANDLE*/   HidDeviceObject,
		/*IN    PVOID    ReportBuffer*/ Fetaure_buffer,
		/*IN    ULONG    ReportBufferLength*/ Capabilities.OutputReportByteLength
		); 
	}
}

void CUsbHidDemonstratorDlg::OnUseSetReport() 
{
	// TODO: Add your control notification handler code here
	m_ReportView_frm.UpdateData(TRUE);
	Use_Setxxx = 0;
	m_ReportView_frm.UpdateData(FALSE);
}

void CUsbHidDemonstratorDlg::OnUseSetFeature() 
{
	// TODO: Add your control notification handler code here
	m_ReportView_frm.UpdateData(TRUE);
	Use_Setxxx = 1;
	m_ReportView_frm.UpdateData(FALSE);
}
