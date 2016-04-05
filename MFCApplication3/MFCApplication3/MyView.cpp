// MyView.cpp : implementation file
//

#include "stdafx.h"
#include "MyView.h"
#include <typeinfo>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView,  CDisplayView)

CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}


BEGIN_MESSAGE_MAP(CMyView,  CDisplayView)
	//{{AFX_MSG_MAP(CMyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDocument* pDoc =(CMyDocument *)GetDocument();
	// TODO: add draw code here
	CRect rect;
	GetClientRect(&rect);
	pDC->MoveTo(0,0);
	pDC->LineTo(pDoc->m_point1);	

}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	 CDisplayView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	 CDisplayView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers
