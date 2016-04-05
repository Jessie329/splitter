// DisView.cpp : implementation file
//

#include "stdafx.h"
#include "DisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisView

IMPLEMENT_DYNCREATE(CDisView,  CDisplayView)

CDisView::CDisView()
{ 
	
}

CDisView::~CDisView()
{
}


BEGIN_MESSAGE_MAP(CDisView,  CDisplayView)
	//{{AFX_MSG_MAP(CDisView)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisView drawing

void CDisView::OnDraw(CDC* pDC)
{
	CMyDocument* pDoc =(CMyDocument *)GetDocument();
	// TODO: add draw code here
	CRect rect;
	GetClientRect(&rect);

	pDC->MoveTo(0,0);
	pDC->LineTo(pDoc->m_point2);
	
	CBrush *pOldBr, br(RGB(255, 0, 0)), br1(RGB(255,255,0));
	CPen *pOldPen, pen(PS_SOLID, 2, RGB(0,0, 255));
	
	//pDC->TextOut(rect.left+10, rect.top+20, "This is a view");
	pOldBr = pDC->SelectObject(&br);
	pOldPen = pDC->SelectObject(&pen);
	
	rect.DeflateRect(50, 50, 50, 50);
	pDC->Rectangle(rect);
	
	pDC->SelectObject(&br1);
	rect.DeflateRect(50, 50, 50, 50);
	pDC->Ellipse(rect);
	
	pDC->SelectObject(pOldBr);
	pDC->SelectObject(pOldPen);
	
	CDisplayView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CDisView diagnostics

#ifdef _DEBUG
void CDisView::AssertValid() const
{
	 CDisplayView::AssertValid();
}

void CDisView::Dump(CDumpContext& dc) const
{
	 CDisplayView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisView message handlers

void CDisView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	//AfxMessageBox("View was double click!");
	
	 CDisplayView::OnLButtonDblClk(nFlags, point);
}
