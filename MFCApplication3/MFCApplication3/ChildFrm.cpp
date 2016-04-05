// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MFCApplication3.h"

#include "ChildFrm.h"
#include "MyDoc2.h"
#include "MyDocument.h"
#include "MyView.h"
#include "DisView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnUpdateFilePrintPreview)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers

void CChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}
///////////////////////////////
void CChildFrame::AddView(UINT docNum, UINT viewNum, UINT type,
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

CDisplayView *CChildFrame::AddRootView(UINT docNum, UINT viewNum, CRect rect,
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
void CChildFrame::UpdateRect(CSplitterControl *pSplitter)
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