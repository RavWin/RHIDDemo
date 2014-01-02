/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : HexEditctrl.cpp
* Author             : MCD Application Team
* Version            : V1.0.2
* Date               : 06/14/2010
* Description        : HexEditor class implementation
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#include "HexEditCtrl.h"
#include <ctype.h>
#include <afxole.h>
#include <afxdisp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


char hextable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
#define TOHEX(a, b)	{*b++ = hextable[a >> 4];*b++ = hextable[a&0xf];}
/////////////////////////////////////////////////////////////////////////////
// CHexEditor

CHexEditor::CHexEditor()
{
//#if !defined(DEMO)
//	m_pData			= NULL;		// pointer to data
//	m_length		= 0;		// length of data
//#else
	
//	for(int i = 0; i < 0x40; i++)
//		m_pData[i] = i;
//#endif
	m_length		= 0xFFFF;

	m_pData			= (LPBYTE)malloc(m_length);
	memset(m_pData, 0xFF, m_length);

	m_topindex		= 0;
	m_bpr			= 16;		// byte per row 
	m_lpp			= 1;

	m_bShowHex		= TRUE;
	m_bShowAscii	= TRUE;
	m_bShowAddress	= TRUE;
	m_bAddressIsWide= FALSE;		// 4/8 byte address

	m_offAddress	= 0;
	m_offHex		= 0;
	m_offAscii		= 0;

	m_bUpdate = TRUE;			// update font info
	m_bNoAddressChange = FALSE;
	m_currentMode = EDIT_NONE;

	m_editPos.x = m_editPos.y = 0;
	m_currentAddress = 0;
	m_bHalfPage = TRUE;

	m_selStart	= 0xffffffff;
	m_selEnd	= 0xffffffff;

	m_Font.CreateFont(-12, 0,0,0,0,0,0,0,0,0,0,0,0, "Courier New");

	//AfxOleInit();
}

CHexEditor::~CHexEditor()
{
}


BEGIN_MESSAGE_MAP(CHexEditor, CEdit)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CHexEditor)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_GETDLGCODE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditor message handlers


void CHexEditor::OnPaint() 
{
	CPaintDC pdc(this); // device context for painting

	CRect rc;
	GetClientRect(rc);
	
	CDC	dc;
	dc.CreateCompatibleDC(CDC::FromHandle(pdc.m_ps.hdc));
	CBitmap bm;

	bm.CreateCompatibleBitmap(CDC::FromHandle(pdc.m_ps.hdc), rc.Width(), rc.Height());
	dc.SelectObject(bm);

	CBrush b;
	b.CreateSolidBrush(RGB(0xff,0xff,0xff));
	dc.FillRect(rc, &b);

	ASSERT(m_currentAddress >= 0);
	ASSERT(m_topindex >= 0);

	dc.SelectObject(m_Font);
	int		height		= 0;
	int		x,y;
	char	buf[256];

	x = rc.TopLeft().x;
	y = rc.TopLeft().y;

	dc.SetBoundsRect(&rc, DCB_DISABLE);

	if(m_pData)
	{
		//
		// get char dimensions
		//
		if(m_bUpdate)
		{
			dc.GetCharWidth('0', '0', &m_nullWidth);
			CSize sz = dc.GetTextExtent("0", 1);
			m_lineHeight = sz.cy;
			
			m_offHex	= m_bShowAddress ? (m_bAddressIsWide ? m_nullWidth * 9 : m_nullWidth * 5) : 0;
			m_offAscii	= m_bShowAddress ? (m_bAddressIsWide ? m_nullWidth * 9 : m_nullWidth * 5) : 0;
			m_offAscii += m_bShowHex	 ? (m_bpr * 3 * m_nullWidth) : 0;

			m_lpp = rc.Height() / m_lineHeight;
			m_bHalfPage = FALSE;
			if(m_lpp * m_bpr > m_length)
			{
				m_lpp = (m_length + (m_bpr/2)) / m_bpr ;
				if(m_length % m_bpr != 0)
				{
					m_bHalfPage = TRUE;
					m_lpp++;
				}
			}
			m_bUpdate = FALSE;
			UpdateScrollbars();
		}

		TRACE("%i %i\n", m_topindex, m_selStart);
		
		height = rc.Height() / m_lineHeight;
		height *= m_lineHeight;

		if(m_bShowAddress)
		{
			char fmt[8] = {'%','0','8','l','X'};
			fmt[2] = m_bAddressIsWide ? '8' : '4';
			int w = m_bAddressIsWide ? 8 : 4;
			y = 0;
			CRect rcd = rc;
			rcd.TopLeft().x = m_offAddress;
			for(int	 i = m_topindex; (i < m_length) && (rcd.TopLeft().y < height); i+= m_bpr)
			{
				sprintf(buf, fmt, i);
				dc.DrawText(buf, w, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
				rcd.TopLeft().y += m_lineHeight;
			}
		}
		if(m_bShowHex)
		{
			y = 0;
			CRect rcd = rc;
			rcd.TopLeft().x = x = m_offHex;

			if(m_selStart != 0xffffffff && (m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW))
			{
				int	 i;
				int	 n = 0;
				int	 selStart = m_selStart, selEnd = m_selEnd;
				if(selStart > selEnd)
					selStart ^= selEnd ^= selStart ^= selEnd;

				for(i = m_topindex; (i < selStart) && (y < height); i++)
				{
					char* p = &buf[0];
					TOHEX(m_pData[i], p);
					*p++ = ' ';
					dc.TextOut(x, y, buf, 3);
					x += m_nullWidth * 3;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offHex;
						y += m_lineHeight;
					}
				}
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
				for(; (i < selEnd) && (i < m_length) && (y < height); i++)
				{
					char* p = &buf[0];
					TOHEX(m_pData[i], p);
					*p++ = ' ';
					dc.TextOut(x, y, buf, 3);
					x += m_nullWidth * 3;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offHex;
						y += m_lineHeight;
					}
				}
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				dc.SetBkColor(GetSysColor(COLOR_WINDOW));
				for(; (i < m_length) && (y < height); i++)
				{
					char* p = &buf[0];
					TOHEX(m_pData[i], p);
					*p++ = ' ';
					dc.TextOut(x, y, buf, 3);
					x += m_nullWidth * 3;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offHex;
						y += m_lineHeight;
					}
				}
			}
			else
			{
				for(int	 i = m_topindex; (i < m_length) && (rcd.TopLeft().y < height);)
				{
					char* p = &buf[0];
					int n;
					for(n = 0; (n < m_bpr) && (i < m_length); n++)
					{
						TOHEX(m_pData[i], p);
						*p++ = ' ';
						i++;
					}
					while(n < m_bpr)
					{
						*p++ = ' ';	*p++ = ' ';	*p++ = ' ';
						n++;
					}

					dc.DrawText(buf, m_bpr*3, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
					rcd.TopLeft().y += m_lineHeight;
				}
			}
		}
		if(m_bShowAscii)
		{
			y = 0;
			CRect rcd = rc;
			rcd.TopLeft().x = x = m_offAscii;
			if(m_selStart != 0xffffffff && m_currentMode == EDIT_ASCII)
			{
				int	 i;
				int	 n = 0;
				int	 selStart = m_selStart, selEnd = m_selEnd;
				if(selStart > selEnd)
					selStart ^= selEnd ^= selStart ^= selEnd;

				for(i = m_topindex; (i < selStart) && (y < height); i++)
				{
					buf[0] = isprint(m_pData[i]) ? m_pData[i] : '.';
					dc.TextOut(x, y, buf, 1);
					x += m_nullWidth;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offAscii;
						y += m_lineHeight;
					}
				}
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
				for(; (i < selEnd) && (y < height); i++)
				{
					buf[0] = isprint(m_pData[i]) ? m_pData[i] : '.';
					dc.TextOut(x, y, buf, 1);
					x += m_nullWidth;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offAscii;
						y += m_lineHeight;
					}
				}
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				dc.SetBkColor(GetSysColor(COLOR_WINDOW));
				for(; (i < m_length) && y < height; i++)
				{
					buf[0] = isprint(m_pData[i]) ? m_pData[i] : '.';
					dc.TextOut(x, y, buf, 1);
					x += m_nullWidth;
					n++;
					if(n == m_bpr)
					{
						n = 0;
						x = m_offAscii;
						y += m_lineHeight;
					}
				}
			}
			else
			{
				for(int	 i = m_topindex; (i < m_length) && (rcd.TopLeft().y < height);)
				{
					char* p = &buf[0];
					int n;
					for(n = 0; (n < m_bpr) && (i < m_length); n++)
					{
						*p++ = isprint(m_pData[i]) ? m_pData[i] : '.';
						i++;
					}
					dc.DrawText(buf, n, rcd, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
					rcd.TopLeft().y += m_lineHeight;
				}
			}
		}
	}
	pdc.BitBlt(0, 0, rc.Width(), rc.Height(), &dc, 0, 0, SRCCOPY);
}

void CHexEditor::OnSetFocus(CWnd* pOldWnd) 
{
	if(m_pData && !IsSelected())
	{
		if(m_editPos.x == 0 && m_bShowAddress)
			CreateAddressCaret();
		else
			CreateEditCaret();
		SetCaretPos(m_editPos);
		ShowCaret();
	}
    SetSel(0,0);
	CWnd::OnSetFocus(pOldWnd);
}

void CHexEditor::OnKillFocus(CWnd* pNewWnd) 
{
	DestroyCaret();
	CWnd::OnKillFocus(pNewWnd);
}

void CHexEditor::OnSize(UINT nType, int cx, int cy) 
{
	CEdit::OnSize(nType, cx, cy);
}

void CHexEditor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	pScrollBar;
	if(!m_pData)
		return;

	int oa = m_topindex;
	switch(nSBCode)
	{
		case SB_LINEDOWN:
			if(m_topindex < m_length - m_lpp*m_bpr)
			{
				//ScrollWindow(0, -m_lineHeight, rc);
				m_topindex += m_bpr;
				RedrawWindow();
			}
			break;
		
		case SB_LINEUP:
			if(m_topindex > 0)
			{
				//ScrollWindow(0, m_lineHeight, rc);
				m_topindex -= m_bpr;
				RedrawWindow();
			}
			break;
		
		case SB_PAGEDOWN:
			if(m_topindex < m_length - m_lpp*m_bpr)
			{
				m_topindex += m_bpr * m_lpp;
				if(m_topindex > m_length - m_lpp*m_bpr)
					m_topindex = m_length - m_lpp*m_bpr;
				RedrawWindow();
			}
			break;

		case SB_PAGEUP:
			if(m_topindex > 0)
			{
				m_topindex -= m_bpr * m_lpp;
				if(m_topindex < 0)
					m_topindex = 0;
				RedrawWindow();
			}
			break;

		case SB_THUMBTRACK:
			m_topindex = nPos * m_bpr;
			RedrawWindow();
			break;
	}
	::SetScrollPos(this->m_hWnd, SB_VERT, m_topindex / m_bpr, TRUE);
	if(!m_bNoAddressChange)
		m_currentAddress += (m_topindex - oa);
	RepositionCaret(m_currentAddress);
}

void CHexEditor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	nSBCode;nPos; pScrollBar;
}

UINT CHexEditor::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

BOOL CHexEditor::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_HSCROLL|WS_VSCROLL;
	return CEdit::PreCreateWindow(cs);
}

BOOL CHexEditor::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle |= WS_HSCROLL|WS_VSCROLL;
	BOOL bRet = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	if(bRet)
		SetFont(&m_Font);
	return bRet;
}

BOOL CHexEditor::OnEraseBkgnd(CDC* pDC) 
{
	pDC;
	return TRUE;
}

void CHexEditor::SetOptions(BOOL a, BOOL h, BOOL c, BOOL w)
{
	m_bShowHex		= h;
	m_bShowAscii	= c;
	m_bShowAddress	= a;
	m_bAddressIsWide= w;		// 4/8 byte address
	m_bUpdate		= TRUE;
}

void CHexEditor::SetBPR(int bpr)
{
	m_bpr = bpr;
	m_bUpdate		= TRUE;
}

void CHexEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	if(!m_pData)
		return;

	if(nFlags & MK_SHIFT)
	{
		m_selStart = m_currentAddress;
	}
	CPoint pt = CalcPos(point.x, point.y);
	if(pt.x > -1)
	{
		m_editPos = pt;
		pt.x *= m_nullWidth;
		pt.y *= m_lineHeight;
		
		if(pt.x == 0 && m_bShowAddress)
			CreateAddressCaret();
		else
			CreateEditCaret();

		SetCaretPos(pt);
		if(nFlags & MK_SHIFT)
		{
			m_selEnd = m_currentAddress;
			if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
				m_selEnd++;
			RedrawWindow();
		}
	}
	if(!(nFlags & MK_SHIFT))
	{
#ifdef _VS6_USED
		if(DragDetect(this->m_hWnd, point))
#else
		if(DragDetect(point))
#endif
		{
			m_selStart = m_currentAddress;
			m_selEnd   = m_selStart;
			SetCapture();
		}
		else
		{
			BOOL bsel = m_selStart != 0xffffffff;

			m_selStart = 0xffffffff;
			m_selEnd   = 0xffffffff;
			if(bsel)
				RedrawWindow();
		}
	}
	if(!IsSelected())
	{
		ShowCaret();
	}
}

void CHexEditor::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	nFlags; point;
}

CPoint CHexEditor::CalcPos(int x, int y)
{
	y /= m_lineHeight;
	if(y < 0 || y > m_lpp)
		return CPoint(-1, -1);

	if(y * m_bpr > m_length)
		return CPoint(-1, -1);

	x += m_nullWidth;
	x /= m_nullWidth;

	int xp;

	if(m_bShowAddress && x <= (m_bAddressIsWide ? 8 : 4))
	{
		m_currentAddress = m_topindex + (m_bpr * y);
		m_currentMode = EDIT_NONE;
		return CPoint(0, y);
	}

	xp = (m_offHex  / m_nullWidth) + m_bpr * 3;
	if(m_bShowHex && x < xp)
	{
		if(x%3)
			x--;
		m_currentAddress = m_topindex + (m_bpr * y) + (x - (m_offHex  / m_nullWidth)) / 3;
		m_currentMode =  ((x%3) & 0x01) ? EDIT_LOW : EDIT_HIGH;
		return CPoint(x, y);
	}

	xp = (m_offAscii  / m_nullWidth) + m_bpr;
	if(m_bShowAscii && x <= xp)
	{
		m_currentAddress = m_topindex + (m_bpr * y) + (x - (m_offAscii  / m_nullWidth));
		m_currentMode = EDIT_ASCII;
		return CPoint(x, y);
	}

	return CPoint(-1,-1);
}

void CHexEditor::CreateAddressCaret()
{
	DestroyCaret();
	CreateSolidCaret(m_nullWidth * (m_bAddressIsWide ? 8 : 4), m_lineHeight);
}

void CHexEditor::CreateEditCaret()
{
	DestroyCaret();
	CreateSolidCaret(m_nullWidth, m_lineHeight);
}

void CHexEditor::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_pData)
		return;

	if(nFlags & MK_LBUTTON && m_selStart != 0xffffffff)
	{
		CRect rc;
		GetClientRect(&rc);
		if(!rc.PtInRect(point))
		{
			if(point.y < 0)
			{
				OnVScroll(SB_LINEUP, 0, NULL);
				point.y = 0;
			}
			else if(point.y > rc.Height())
			{
				OnVScroll(SB_LINEDOWN, 0, NULL);
				point.y = rc.Height() -1;
			}
		}

		//
		// we are selecting
		//
		int	 seo = m_selEnd;
		CPoint pt = CalcPos(point.x, point.y);
		if(pt.x > -1)
		{
			m_selEnd = m_currentAddress;
			if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
				m_selEnd++;
		}
		if(IsSelected())
			DestroyCaret();

		if(seo != m_selEnd)
			RedrawWindow();
	}
}

void CHexEditor::UpdateScrollbars()
{
	SCROLLINFO si;

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = (m_length / m_bpr) - 1;
	si.nPage = m_lpp;
	si.nPos = m_topindex / m_bpr;

	::SetScrollInfo(this->m_hWnd, SB_VERT, &si, TRUE);
	if(si.nMax > (int)si.nPage)
		::EnableScrollBar(this->m_hWnd, SB_VERT, ESB_ENABLE_BOTH);

	CRect rc;
	GetClientRect(&rc);

	si.nMin = 0;
	si.nMax =((m_bShowAddress ? (m_bAddressIsWide ? 8 : 4) : 0) +
			  (m_bShowHex ? m_bpr * 3 : 0) +
			  (m_bShowAscii ? m_bpr : 0) ) * m_nullWidth;
	si.nPage = 1;
	si.nPos = 0;
	::SetScrollInfo(this->m_hWnd, SB_HORZ, &si, TRUE);
}


inline BOOL CHexEditor::IsSelected()
{
	return m_selStart != 0xffffffff;
}

void CHexEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(IsSelected())
		ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CHexEditor::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	nFlags;nRepCnt;
	if(!m_pData)
		return;
	if(nChar == '\t')
		return;
	if(GetKeyState(VK_CONTROL) & 0x80000000)
	{
		switch(nChar)
		{
			case 0x03:
				if(IsSelected())
					OnEditCopy();
				return;
			case 0x16:
				OnEditPaste();
				return;
			case 0x18:
				if(IsSelected())
					OnEditCut();
				return;
			case 0x1a:
				OnEditUndo();
				return;
		}
	}

	if(nChar == 0x08)
	{
		if(m_currentAddress > 0)
		{
			m_currentAddress--;
			SelDelete(m_currentAddress, m_currentAddress+1);
			RepositionCaret(m_currentAddress);
			RedrawWindow();
		}
		return;
	}

	SetSel(-1, -1);
	switch(m_currentMode)
	{
		case EDIT_NONE:
			return;
		case EDIT_HIGH:
		case EDIT_LOW:
			if((nChar >= '0' && nChar <= '9') || (nChar >= 'a' && nChar <= 'f'))
			{
				UINT b = nChar - '0';
				if(b > 9) 
					b = 10 + nChar - 'a';

				if(m_currentMode == EDIT_HIGH)
				{
					m_pData[m_currentAddress] = (unsigned char)((m_pData[m_currentAddress] & 0x0f) | (b << 4));
				}
				else
				{
					m_pData[m_currentAddress] = (unsigned char)((m_pData[m_currentAddress] & 0xf0) | b);
				}
				Move(1,0);
			}
			break;
		case EDIT_ASCII:
			m_pData[m_currentAddress] = (unsigned char)nChar;
			Move(1,0);
			break;
	}
	RedrawWindow();
}

void CHexEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	nFlags;	nRepCnt;

	BOOL bShift = GetKeyState(VK_SHIFT) & 0x80000000;
	BOOL bac = m_bNoAddressChange;
	m_bNoAddressChange = TRUE;
	switch(nChar)
	{
		case VK_DOWN:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				Move(0,1);
				m_selEnd   = m_currentAddress;
				if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
					m_selEnd++;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			Move(0,1);
			break;
		case VK_UP:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				Move(0,-1);
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			Move(0,-1);
			break;
		case VK_LEFT:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				Move(-1,0);
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			Move(-1,0);
			break;
		case VK_RIGHT:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				Move(1,0);
				m_selEnd   = m_currentAddress;
				if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
					m_selEnd++;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			Move(1,0);
			break;
		case VK_PRIOR:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				OnVScroll(SB_PAGEUP, 0, NULL);
				Move(0,0);
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			OnVScroll(SB_PAGEUP, 0, NULL);
			Move(0,0);
			break;
		case VK_NEXT:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				OnVScroll(SB_PAGEDOWN, 0, NULL);
				Move(0,0);
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			OnVScroll(SB_PAGEDOWN, 0, NULL);
			Move(0,0);
			break;
		case VK_HOME:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				if(GetKeyState(VK_CONTROL) & 0x80000000)
				{
					OnVScroll(SB_THUMBTRACK, 0, NULL);
					Move(0,0);
				}
				else
				{
					m_currentAddress /= m_bpr;
					m_currentAddress *= m_bpr;
					Move(0,0);
				}
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			if(GetKeyState(VK_CONTROL) & 0x80000000)
			{
				OnVScroll(SB_THUMBTRACK, 0, NULL);
				m_currentAddress = 0;
				Move(0,0);
			}
			else
			{
				m_currentAddress /= m_bpr;
				m_currentAddress *= m_bpr;
				Move(0,0);
			}
			break;
		case VK_END:
			if(bShift)
			{
				if(!IsSelected())
				{
					m_selStart = m_currentAddress;
				}
				if(GetKeyState(VK_CONTROL) & 0x80000000)
				{
					m_currentAddress = m_length-1;
					OnVScroll(SB_THUMBTRACK, ((m_length+(m_bpr/2)) / m_bpr) - m_lpp, NULL);
					Move(0,0);
				}
				else
				{
					m_currentAddress /= m_bpr;
					m_currentAddress *= m_bpr;
					m_currentAddress += m_bpr - 1;
					if(m_currentAddress > m_length)
						m_currentAddress = m_length-1;
					Move(0,0);
				}
				m_selEnd   = m_currentAddress;
				RedrawWindow();
				break;
			}
			else
				SetSel(-1, -1);
			if(GetKeyState(VK_CONTROL) & 0x80000000)
			{
				m_currentAddress = m_length-1;
				if(m_bHalfPage)
					OnVScroll(SB_THUMBTRACK, 0, NULL);
				else
					OnVScroll(SB_THUMBTRACK, ((m_length+(m_bpr/2)) / m_bpr) - m_lpp, NULL);
				Move(0,0);
			}
			else
			{
				m_currentAddress /= m_bpr;
				m_currentAddress *= m_bpr;
				m_currentAddress += m_bpr - 1;
				if(m_currentAddress > m_length)
					m_currentAddress = m_length-1;
				Move(0,0);
			}
			break;
		case VK_INSERT:
			SelInsert(m_currentAddress, max(1, m_selEnd-m_selStart));
			RedrawWindow();
			break;
		case VK_DELETE:
			if(IsSelected())
			{
				OnEditClear();
			}
			else
			{
				SelDelete(m_currentAddress, m_currentAddress+1);
				RedrawWindow();
			}
			break;
		case '\t':
			switch(m_currentMode)
			{
				case EDIT_NONE:
					m_currentMode = EDIT_HIGH;
					break;
				case EDIT_HIGH:
				case EDIT_LOW:
					m_currentMode = EDIT_ASCII;
					break;
				case EDIT_ASCII:
					m_currentMode = EDIT_HIGH;
					break;
			}
			Move(0,0);
			break;

	}
	m_bNoAddressChange = bac;
}

void CHexEditor::Move(int x, int y)
{
	switch(m_currentMode)
	{
		case EDIT_NONE:
			return;
		case EDIT_HIGH:
			if(x != 0)
				m_currentMode = EDIT_LOW;
			if(x == -1)
				m_currentAddress --;
			m_currentAddress += y* m_bpr;
			break;
		case EDIT_LOW:
			if(x != 0)
				m_currentMode = EDIT_HIGH;
			if(x == 1)
				m_currentAddress++;
			m_currentAddress += y* m_bpr;
			break;
		case EDIT_ASCII:
			{
				m_currentAddress += x;
				m_currentAddress += y*m_bpr;
			}
			break;
	}
	if(m_currentAddress < 0)
		m_currentAddress = 0;

	if(m_currentAddress >= m_length)
	{
		m_currentAddress -= x;
		m_currentAddress -= y*m_bpr;
	}
	m_bNoAddressChange = TRUE;
	if(m_currentAddress < m_topindex)
	{
		OnVScroll(SB_LINEUP, 0, NULL);
	}
	if(m_currentAddress >= m_topindex + m_lpp*m_bpr)
	{
		OnVScroll(SB_LINEDOWN, 0, NULL);
	}
	m_bNoAddressChange = FALSE;
	//ScrollIntoView(m_currentAddress);
	RepositionCaret(m_currentAddress);
}

void CHexEditor::SetSel(int s, int e)
{
	DestroyCaret();
	m_selStart = s;
	m_selEnd = e;
	RedrawWindow();
	if(m_editPos.x == 0 && m_bShowAddress)
		CreateAddressCaret();
	else
		CreateEditCaret();
	SetCaretPos(m_editPos);
	ShowCaret();
}

void CHexEditor::RepositionCaret(int	 p)
{
	int x, y;

	y = (p - m_topindex) / m_bpr;
	x = (p - m_topindex) % m_bpr;

	switch(m_currentMode)
	{
		case EDIT_NONE:
			CreateAddressCaret();
			x = 0;
			break;
		case EDIT_HIGH:
			CreateEditCaret();
			x *= m_nullWidth*3;
			x += m_offHex;
			break;
		case EDIT_LOW:
			CreateEditCaret();
			x *= m_nullWidth*3;
			x += m_nullWidth;
			x += m_offHex;
			break;
		case EDIT_ASCII:
			CreateEditCaret();
			x *= m_nullWidth;
			x += m_offAscii;
			break;
	}
	m_editPos.x = x;
	m_editPos.y = y*m_lineHeight;
	CRect rc;
	GetClientRect(&rc);
	if(rc.PtInRect(m_editPos))
	{
		SetCaretPos(m_editPos);
		ShowCaret();
	}
}

void CHexEditor::ScrollIntoView(int p)
{
	if(p < m_topindex || p > m_topindex + m_lpp*m_bpr)
	{
		m_topindex = (p/m_bpr) * m_bpr;
		m_topindex -= (m_lpp / 3) * m_bpr;
		if(m_topindex < 0)
			m_topindex = 0;

		UpdateScrollbars();
		RedrawWindow();
	}
}

void CHexEditor::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		//VERIFY(menu.LoadMenu(CG_IDR_POPUP_HEX_EDIT));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->EnableMenuItem(ID_EDIT_UNDO, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
		if(!IsSelected())
		{
			pPopup->EnableMenuItem(ID_EDIT_CLEAR, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
			pPopup->EnableMenuItem(ID_EDIT_CUT, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
			pPopup->EnableMenuItem(ID_EDIT_COPY, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
		}
		{
			COleDataObject	obj;	
			if (obj.AttachClipboard()) 
			{
				if(!obj.IsDataAvailable(CF_TEXT) && !obj.IsDataAvailable(RegisterClipboardFormat("BinaryData")))
					pPopup->EnableMenuItem(ID_EDIT_PASTE, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
			}
		}

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			this);
	}
}

void CHexEditor::OnEditClear() 
{
	m_currentAddress = m_selStart;
	SelDelete(m_selStart, m_selEnd);
	RepositionCaret(m_currentAddress);
	RedrawWindow();
}

void CHexEditor::OnEditCopy() 
{
	COleDataSource*		pSource = new COleDataSource();
	EmptyClipboard();
	if(m_currentMode != EDIT_ASCII)
	{
		int			dwLen = (m_selEnd-m_selStart);
		HGLOBAL		hMemb = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
		HGLOBAL		hMema = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, (dwLen) * 3);

		if (!hMema) 
			return;

		// copy binary
		LPBYTE	p = (BYTE*)::GlobalLock(hMemb);
		memcpy(p, m_pData+m_selStart, dwLen);
		::GlobalUnlock(hMemb);
		
		// copy ascii
		p = (BYTE*)::GlobalLock(hMema);
		for(int	 i = 0; i < dwLen;)
		{
			TOHEX(m_pData[m_selStart+i], p);
			*p++ = ' ';
			i++;
		}

		::GlobalUnlock(hMema);

		pSource->CacheGlobalData(RegisterClipboardFormat("BinaryData"), hMemb);	
		pSource->CacheGlobalData(CF_TEXT, hMema);	
	}
	else
	{
		HGLOBAL				hMemb = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
		HGLOBAL				hMema = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, m_selEnd-m_selStart);
		if (!hMemb || !hMema) 
			return;

		// copy binary
		LPBYTE	p = (BYTE*)::GlobalLock(hMemb);
		int		dwLen = m_selEnd-m_selStart;

		memcpy(p, m_pData+m_selStart, dwLen);
		::GlobalUnlock(hMemb);
		
		// copy ascii
		p = (BYTE*)::GlobalLock(hMema);
		memcpy(p, m_pData+m_selStart, dwLen);
		for(int i = 0; i < dwLen; p++, i++)
			if(!isprint(*p))
				*p = '.';
		::GlobalUnlock(hMema);

		pSource->CacheGlobalData(RegisterClipboardFormat("BinaryData"), hMemb);	
		pSource->CacheGlobalData(CF_TEXT, hMema);	
	}
	pSource->SetClipboard();
}

void CHexEditor::OnEditCut() 
{
	OnEditCopy();
	SelDelete(m_selStart, m_selEnd);
	RedrawWindow();
}

void CHexEditor::OnEditPaste() 
{
	COleDataObject	obj;	
	if (obj.AttachClipboard()) 
	{
		HGLOBAL hmem = NULL;
		if (obj.IsDataAvailable(RegisterClipboardFormat("BinaryData"))) 
		{
			hmem = obj.GetGlobalData(RegisterClipboardFormat("BinaryData"));
		}	
		else if (obj.IsDataAvailable(CF_TEXT)) 
		{
			hmem = obj.GetGlobalData(CF_TEXT);
		}
		if(hmem)
		{
			LPBYTE	p = (BYTE*)::GlobalLock(hmem);
			DWORD	dwLen = ::GlobalSize(hmem);
			int		insert;
			int		oa = m_currentAddress;
			
			NormalizeSel();
			if(m_selStart == 0xffffffff)
			{
				if(m_currentMode == EDIT_LOW)
					m_currentAddress++;
				insert = m_currentAddress;
				SelInsert(m_currentAddress, dwLen);
			}
			else
			{
				insert = m_selStart;
				SelDelete(m_selStart, m_selEnd);
				SelInsert(insert, dwLen);
				SetSel(-1, -1);
			}

			memcpy(m_pData+insert, p, dwLen);

			m_currentAddress = oa;
			RedrawWindow();
			::GlobalUnlock(hmem);
		}
	}
}

void CHexEditor::OnEditSelectAll() 
{
	m_selStart = 0;
	m_selEnd = m_length;
	DestroyCaret();
	RedrawWindow();
}

void CHexEditor::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

void CHexEditor::NormalizeSel()
{
	if(m_selStart > m_selEnd)
		m_selStart ^= m_selEnd ^= m_selStart ^= m_selEnd;
}

void CHexEditor::SelDelete(int s, int e)
{
	LPBYTE p = (LPBYTE) malloc(m_length - (e-s)+1);
	memcpy(p, m_pData, s);
	if(s < m_length-(e-s)) 
		memcpy(p+s, m_pData+e, (m_length -e));
	
	free(m_pData);
	SetSel(-1, -1);
	m_pData = p;
	m_length = m_length-(e-s);
	if(m_currentAddress > m_length)
	{
		m_currentAddress = m_length;
		RepositionCaret(m_currentAddress);
	}
	m_bUpdate = TRUE;
}

void CHexEditor::SelInsert(int s, int l)
{
	LPBYTE p = (LPBYTE) calloc(m_length + l, 1);
	memcpy(p, m_pData, s);
	memcpy(p+s+l, m_pData+s, (m_length-s));
	free(m_pData);
	SetSel(-1, -1);
	m_pData = p;
	m_length = m_length+l;
	m_bUpdate = TRUE;
}

CSize CHexEditor::GetSel()
{
	return CSize(m_selStart, m_selEnd);
}

void CHexEditor::SetData(LPBYTE p, int len)
{
	//free(m_pData);
	
	//m_pData = (LPBYTE) malloc(len);
	
	memcpy(m_pData, p, len);
  
	//SetSel(-1, -1);
    RedrawWindow();
	//m_length = len;
	m_currentAddress = 0;
	m_editPos.x = m_editPos.y = 0;
	m_currentMode = EDIT_HIGH;
	m_topindex = 0;
	m_bUpdate = TRUE;
}

int CHexEditor::GetData(LPBYTE p, int len)
{
	memcpy(p, m_pData, min(len, m_length));
	return min(len, m_length);
}

void CHexEditor::SetDataSize(WORD size)
{
	WORD OldSize = size;
	if(size > m_length)
	{
	  OldSize = m_length;
	}
    m_length = size;
	m_pData			= (LPBYTE)realloc(m_pData,m_length);
	memset(m_pData + OldSize  , 0xFF, m_length - OldSize );
	SetData(m_pData,m_length);
	m_bUpdate		= TRUE;
    OnPaint();	
}
