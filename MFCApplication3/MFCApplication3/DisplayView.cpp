/************************************************************************/
/*  Copying ringht (C) 2003
/*
/*	Name:	      DisplayView.cpp
/*  Function:     Implement the Specil function for all view,
/*                In this appliction all View must Inherit from 
/*                this View.
/*  
/*  Author:       lava_sdb
/*  Create Date:  2003-8-19
/*  Version:	  1.0                                                                 
/*
/*  Modify:   
/*     Author:
/*	   Change:
/*     Date:
/*	
/*
/************************************************************************/

#include "stdafx.h"
#include "DisplayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayView

IMPLEMENT_DYNCREATE(CDisplayView, CView)

CDisplayView::CDisplayView()
{
}

CDisplayView::~CDisplayView()
{
}


BEGIN_MESSAGE_MAP(CDisplayView, CView)
	//{{AFX_MSG_MAP(CDisplayView)
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	//ON_COMMAND(IDC_MENU_SPLIT_HOR, OnMenuSplitHor)     //²Ëµ¥ÃüÁî
	//ON_COMMAND(IDC_MENU_SPLIT_VER, OnMenuSplitVer)	 //²Ëµ¥ÃüÁî

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayView drawing


void CDisplayView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	LOGBRUSH lb;
	HBRUSH hBrush;

	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(183,123,233);
	lb.lbHatch = HS_FDIAGONAL;
	hBrush=::CreateBrushIndirect(&lb);
	
	::FillRgn(pDC->m_hDC,m_rgnMenu,hBrush);

	::DeleteObject(hBrush);

}

/////////////////////////////////////////////////////////////////////////////
// CDisplayView diagnostics

#ifdef _DEBUG
void CDisplayView::AssertValid() const
{
	CView::AssertValid();
}

void CDisplayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisplayView message handlers

void CDisplayView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{	
	this->m_Split->AddView(0,1,2,this);
	CView::OnRButtonDblClk(nFlags, point);
}

void CDisplayView::OnRButtonDown(UINT nFlags, CPoint point) 
{

	CView::OnRButtonDown(nFlags, point);
}

void CDisplayView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	this->m_Split->AddView(0,1,1,this);	
	CView::OnLButtonDblClk(nFlags, point);
}


int CDisplayView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	rect.right=rect.left+20;
	rect.bottom=rect.top+20;
	CRgn rgnRect,rgnEllipt;
	int tt=rgnRect.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
	int t1=rgnEllipt.CreateEllipticRgn(rect.left , rect.top,
								rect.left+rect.Width()*2,
								rect.top+rect.Height()*2);
	int t2=rgnEllipt.CombineRgn(&rgnRect,&rgnEllipt,RGN_AND);
	int t3=rgnRect.CombineRgn(&rgnRect,&rgnEllipt,RGN_XOR);	
	

	m_rgnMenu.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
	m_rgnMenu.CopyRgn(&rgnRect);
		
	return 0;
}

void CDisplayView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDC *pDC=GetDC();

	if(m_rgnMenu.PtInRegion(point))
	{
		LOGBRUSH lb;
		HBRUSH hBrush;
		
		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(255,155,183);
		lb.lbHatch = HS_FDIAGONAL;
		hBrush=::CreateBrushIndirect(&lb);
		
		::FillRgn(pDC->m_hDC,m_rgnMenu,hBrush);
		
		::DeleteObject(hBrush);
	}
	else
	{
		LOGBRUSH lb;
		HBRUSH hBrush;
		
		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(183,123,233);
		lb.lbHatch = HS_FDIAGONAL;
		hBrush=::CreateBrushIndirect(&lb);
		
		::FillRgn(pDC->m_hDC,m_rgnMenu,hBrush);
		
		::DeleteObject(hBrush);

	}
	CView::OnMouseMove(nFlags, point);
}

void CDisplayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_rgnMenu.PtInRegion(point))
	{		
	/*	
		LPPOINT lpoint=new tagPOINT;
        ::GetCursorPos(lpoint);
        CMenu menu;
		
		VERIFY(menu.LoadMenu(IDR_MENU_VIEW)); 
		
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y ,this);
        HMENU hmenu=menu.Detach();
        menu.DestroyMenu();
        delete lpoint;	
	*/
	}
	CView::OnLButtonDown(nFlags, point);
}

void CDisplayView::OnMenuSplitHor() 
{
	this->m_Split->AddView(0,1,2,this);	
	
}

void CDisplayView::OnMenuSplitVer() 
{
	this->m_Split->AddView(0,1,1,this);	
	
}
