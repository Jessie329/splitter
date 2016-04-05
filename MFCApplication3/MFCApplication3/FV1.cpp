// FV1.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "FV1.h"
#include "MyDoc2.h"
#include "MyDocument.h"
#include "MyView.h"
#include "DisView.h"

// FV1

IMPLEMENT_DYNCREATE(FV1, CFormView)

FV1::FV1()
	: CFormView(FV1::IDD)
{
}

FV1::~FV1()
{
}

void FV1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void FV1::OnInitialUpdate()
{
    CRect rc;
    GetWindowRect(rc);
    ScreenToClient(rc);
    GetDlgItem(IDC_STA_SPLIT)->GetWindowRect(rc);
    ScreenToClient(rc);

    m_pSplit.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_STA_SPLIT);
    m_pSplit.SetRange(300, 300, -1);

    //GetDlgItem(IDC_STA_VIEW)->GetWindowRect(rc);
    GetWindowRect(rc);
    ScreenToClient(rc);

    m_pSplit.AddRootView(0, 1, rc);
    m_pSplit.ShowWindow(SW_HIDE);
}

BEGIN_MESSAGE_MAP(FV1, CFormView)
    ON_STN_CLICKED(IDC_STA_VIEW, &FV1::OnStnClickedStaView)
END_MESSAGE_MAP()


// FV1 diagnostics

#ifdef _DEBUG
void FV1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FV1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FV1 message handlers


void FV1::OnStnClickedStaView()
{
    // TODO: Add your control notification handler code here
}

/************************************************************************/
/*			made by Lava_sdb
/* Action:
/*		  Split View using add new view
/* In:
/*	  docNum   ---  selected doc type
/*    viewNum  ---  selected view type
/*	  type     ---  the type of split
/*					1  VERTICAL
/*					2  HORIZONTAL
/*	  splitter ---  the Point that will add view
/************************************************************************/

void FV1::AddView(UINT docNum, UINT viewNum, UINT type,
    CSplitterControl *splitter,
    CView *pCurView)
{
    CRect rect;
    CView *pAddView = NULL;
    pCurView->GetWindowRect(rect);
    ScreenToClient(rect);


    //create the new Split	
    CSplitterControl *pNewSplit = new CSplitterControl;
    CRect rc;
    if (type == 1)   //Ver
    {
        rc.left = rect.left + rect.Width() / 2;
        rc.top = rect.top / 2;
        rc.right = rect.left + 5;
        rc.bottom = rect.top + rect.Height();

        pNewSplit->m_rect0.left = rect.left;
        pNewSplit->m_rect0.right = rect.left + rect.Width() / 2;
        pNewSplit->m_rect0.top = rect.top;
        pNewSplit->m_rect0.bottom = rect.bottom;

        pNewSplit->m_rect1.left = rect.left + rect.Width() / 2;
        pNewSplit->m_rect1.right = rect.left + rect.Width();
        pNewSplit->m_rect1.top = rect.top;
        pNewSplit->m_rect1.bottom = rect.bottom;
    }
    else if (type == 2)  //h
    {
        rc.left = rect.left;
        rc.top = rect.top + rect.Height() / 2;
        rc.right = rc.left + rect.Width();
        rc.bottom = rc.top + 5;

        pNewSplit->m_rect0.left = rect.left;
        pNewSplit->m_rect0.right = rect.right;
        pNewSplit->m_rect0.top = rect.top;
        pNewSplit->m_rect0.bottom = rect.top + rect.Height() / 2;

        pNewSplit->m_rect1.left = rect.left;
        pNewSplit->m_rect1.right = rect.right;
        pNewSplit->m_rect1.top = rect.top + rect.Height() / 2;
        pNewSplit->m_rect1.bottom = rect.top + rect.Height();
    }

    pNewSplit->Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_STA_SPLIT);
    pNewSplit->SetRange(300, 300, -1);

    //judge the type of view on his parent,(Left<top> or Right<bottom>)
    if (*pCurView == *(splitter->m_pLView))
    {
        splitter->m_pSplit0 = pNewSplit;
    }
    else
    {
        splitter->m_pSplit1 = pNewSplit;
    }


    CWnd* pFrameWnd = this;
    //decide the type of Doc
    switch (docNum) {
    case 0:
        m_pContext.m_pCurrentDoc = new CMyDoc2;
        break;
    case 1:
        m_pContext.m_pCurrentDoc = new CMyDocument;
        break;
    }
    //decide the type of view
    switch (viewNum) {
    case 0:
    {
        m_pContext.m_pNewViewClass = RUNTIME_CLASS(CMyView);
        CMyView  *pView = (CMyView  *)((CFrameWnd*)pFrameWnd)->CreateView(&m_pContext);
        pAddView = pView;
    }
    break;
    case 1:
    {
        m_pContext.m_pNewViewClass = RUNTIME_CLASS(CDisView);
        CDisView *pView = (CDisView *)((CFrameWnd*)pFrameWnd)->CreateView(&m_pContext);
        pAddView = pView;
    }
    break;
    }
    //adjust views point
    static_cast<CDisplayView *>(pAddView)->m_Split = pNewSplit;
    static_cast<CDisplayView *>(pCurView)->m_Split = pNewSplit;
    pNewSplit->m_pLView = pCurView;
    pNewSplit->m_pRView = pAddView;
    //adjust the new view's pos
    CRect recttemp;

    if (type == 1)        //Ver
    {
        recttemp.left = rect.left + rect.Width() / 2;
        recttemp.top = rect.top;
        recttemp.right = recttemp.left + rect.Width() / 2;
        recttemp.bottom = recttemp.top + rect.Height();

        rect.right = rect.left + rect.Width() / 2;
    }
    else if (type == 2)  //H
    {
        recttemp.top = rect.top + rect.Height() / 2;
        recttemp.left = rect.left;
        recttemp.right = recttemp.left + rect.Width();
        recttemp.bottom = recttemp.top + rect.Height() / 2;

        rect.bottom = rect.top + rect.Height() / 2;
    }
    pCurView->MoveWindow(rect);
    pAddView->MoveWindow(recttemp);
}

/************************************************************************/
/*			made by Lava_sdb
/* Action:
/*		  Create the Split Root View
/* In:
/*	  docNum   ---  selected doc type
/*    viewNum  ---  selected view type
/*	  rect     ---  view's display region
/************************************************************************/

CDisplayView *FV1::AddRootView(UINT docNum, UINT viewNum, CRect rect,
    CSplitterControl *splitter)
{
    ASSERT(splitter != NULL);
    CWnd* pFrameWnd = this;
    //Decide the type of doc
    switch (docNum) {
    case 0:
    {
        m_pContext.m_pCurrentDoc = new CMyDoc2;
    }
    break;
    case 1:
        m_pContext.m_pCurrentDoc = new CMyDocument;
        break;
    }
    //decide the type of view
    switch (viewNum) {
    case 0:
    {
        m_pContext.m_pNewViewClass = RUNTIME_CLASS(CMyView);
        CMyView  *pView = (CMyView  *)((CFrameWnd*)pFrameWnd)->CreateView(&m_pContext);
        pView->m_Split = splitter;
        pView->MoveWindow(rect);
        return pView;
    }
    break;
    case 1:
    {
        m_pContext.m_pNewViewClass = RUNTIME_CLASS(CDisView);
        CDisView *pView = (CDisView *)((CFrameWnd*)pFrameWnd)->CreateView(&m_pContext);
        pView->m_Split = splitter;
        pView->MoveWindow(rect);
        return pView;
    }
    break;
    }
    return NULL;
}




/************************************************************************/
/*   Name:
/*			UpdateRect()
/*	 Action:
/*       iterative compute the Rect AND redraw the rect
/*   In:
/*       pSplitter  --- the first split that will iterative
/************************************************************************/

static int DEBUG_COUNT = 0;   //Debug
void FV1::UpdateRect(CSplitterControl *pSplitter)
{

    if (DEBUG_COUNT == 0)
    {
        //iterator the Left(Top) Tree
        if (pSplitter->m_pSplit0 != NULL)
        {
            CRect rect;
            pSplitter->m_pSplit0->GetWindowRect(rect);
            ScreenToClient(rect);

            //change the position of split
            if (pSplitter->m_pSplit0->GetStyle() == 1)  //Ver Split
            {
                rect.left = pSplitter->m_rect0.left + pSplitter->m_rect0.Width() / 2;
                rect.top = pSplitter->m_rect0.top;
                rect.right = rect.left + 5;
                rect.bottom = pSplitter->m_rect0.bottom;

            }
            else
            {
                rect.top = pSplitter->m_rect0.top + pSplitter->m_rect0.Height() / 2;
                rect.left = pSplitter->m_rect0.left;
                rect.right = pSplitter->m_rect0.right;
                rect.bottom = rect.top + 5;
            }

            pSplitter->m_pSplit0->MoveWindow(rect);

            //Resizzing the m_rect of the split
            if (pSplitter->m_pSplit0->GetStyle() == 2)  //Hor Split
            {
                pSplitter->m_pSplit0->m_rect0.left = pSplitter->m_rect0.left;
                pSplitter->m_pSplit0->m_rect0.right = pSplitter->m_rect0.right;
                pSplitter->m_pSplit0->m_rect0.top = pSplitter->m_rect0.top;
                pSplitter->m_pSplit0->m_rect0.bottom = pSplitter->m_rect0.top + pSplitter->m_rect0.Height() / 2;

                pSplitter->m_pSplit0->m_rect1.left = pSplitter->m_rect0.left;
                pSplitter->m_pSplit0->m_rect1.right = pSplitter->m_rect0.right;
                pSplitter->m_pSplit0->m_rect1.top = pSplitter->m_rect0.top + pSplitter->m_rect0.Height() / 2;
                pSplitter->m_pSplit0->m_rect1.bottom = pSplitter->m_rect0.top + pSplitter->m_rect0.Height();
            }
            else
            {
                pSplitter->m_pSplit0->m_rect0.left = pSplitter->m_rect0.left;
                pSplitter->m_pSplit0->m_rect0.right = pSplitter->m_rect0.left + pSplitter->m_rect0.Width() / 2;
                pSplitter->m_pSplit0->m_rect0.top = pSplitter->m_rect0.top;
                pSplitter->m_pSplit0->m_rect0.bottom = pSplitter->m_rect0.bottom;

                pSplitter->m_pSplit0->m_rect1.left = pSplitter->m_rect0.left + pSplitter->m_rect0.Width() / 2;
                pSplitter->m_pSplit0->m_rect1.right = pSplitter->m_rect0.left + pSplitter->m_rect0.Width();
                pSplitter->m_pSplit0->m_rect1.top = pSplitter->m_rect0.top;
                pSplitter->m_pSplit0->m_rect1.bottom = pSplitter->m_rect0.bottom;
            }

            UpdateRect(pSplitter->m_pSplit0);
        }
        if (pSplitter->m_pSplit0 == NULL)
        {
            pSplitter->m_pLView->MoveWindow(pSplitter->m_rect0);
            pSplitter->m_pRView->MoveWindow(pSplitter->m_rect1);
        }
        //DEBUG_COUNT=1;


        //iterator the Right(Bottom) Tree
        if (pSplitter->m_pSplit1 != NULL)
        {
            CRect rect;
            pSplitter->m_pSplit1->GetWindowRect(rect);
            ScreenToClient(rect);

            //change the position of split
            if (pSplitter->m_pSplit1->GetStyle() == 1)  ///Ver Split
            {
                rect.left = pSplitter->m_rect1.left + pSplitter->m_rect1.Width() / 2;
                rect.top = pSplitter->m_rect1.top;
                rect.right = rect.left + 5;
                rect.bottom = pSplitter->m_rect1.bottom;

            }
            else
            {
                rect.top = pSplitter->m_rect1.top + pSplitter->m_rect1.Height() / 2;
                rect.left = pSplitter->m_rect1.left;
                rect.right = pSplitter->m_rect1.right;
                rect.bottom = rect.top + 5;
            }

            pSplitter->m_pSplit1->MoveWindow(rect);

            //Resizzing the m_rect of the split
            if (pSplitter->m_pSplit1->GetStyle() == 2)  //Hor Split
            {
                pSplitter->m_pSplit1->m_rect0.left = pSplitter->m_rect1.left;
                pSplitter->m_pSplit1->m_rect0.right = pSplitter->m_rect1.right;
                pSplitter->m_pSplit1->m_rect0.top = pSplitter->m_rect1.top;
                pSplitter->m_pSplit1->m_rect0.bottom = pSplitter->m_rect1.top + pSplitter->m_rect1.Height() / 2;

                pSplitter->m_pSplit1->m_rect1.left = pSplitter->m_rect1.left;
                pSplitter->m_pSplit1->m_rect1.right = pSplitter->m_rect1.right;
                pSplitter->m_pSplit1->m_rect1.top = pSplitter->m_rect1.top + pSplitter->m_rect1.Height() / 2;
                pSplitter->m_pSplit1->m_rect1.bottom = pSplitter->m_rect1.top + pSplitter->m_rect1.Height();
            }
            else
            {
                pSplitter->m_pSplit1->m_rect0.left = pSplitter->m_rect1.left;
                pSplitter->m_pSplit1->m_rect0.right = pSplitter->m_rect1.left + pSplitter->m_rect1.Width() / 2;
                pSplitter->m_pSplit1->m_rect0.top = pSplitter->m_rect1.top;
                pSplitter->m_pSplit1->m_rect0.bottom = pSplitter->m_rect1.bottom;

                pSplitter->m_pSplit1->m_rect1.left = pSplitter->m_rect1.left + pSplitter->m_rect1.Width() / 2;
                pSplitter->m_pSplit1->m_rect1.right = pSplitter->m_rect1.left + pSplitter->m_rect1.Width();
                pSplitter->m_pSplit1->m_rect1.top = pSplitter->m_rect1.top;
                pSplitter->m_pSplit0->m_rect1.bottom = pSplitter->m_rect0.bottom;
            }

            UpdateRect(pSplitter->m_pSplit1);
        }
        if (pSplitter->m_pSplit1 == NULL)
        {
            pSplitter->m_pRView->MoveWindow(pSplitter->m_rect1);
        }
    }

}