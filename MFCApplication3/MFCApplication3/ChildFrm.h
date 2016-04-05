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

// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "DisplayView.h"
#include "SplitterControl.h"
class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
    /*¡K¡K¡K¡K*/
    void UpdateRect(CSplitterControl *pSplitter);
    CDisplayView *AddRootView(UINT docNum, UINT viewNum, CRect
        rect, CSplitterControl *splitter);
    void AddView(UINT docNum, UINT viewNum, UINT type,
        CSplitterControl *splitter,
        CView *pCurView);
    /*¡K¡K¡K¡K*/
    /* Split vector*/
    CSplitterControl m_pSplit;
    CCreateContext m_pContext;
    /*¡K¡K¡K¡K¡K¡K*/
protected:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
