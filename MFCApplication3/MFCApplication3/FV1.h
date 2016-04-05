#pragma once



// FV1 form view
#include "resource.h"
#include "DisplayView.h"
#include "SplitterControl.h"
class FV1 : public CFormView
{
	DECLARE_DYNCREATE(FV1)

protected:
	FV1();           // protected constructor used by dynamic creation
	virtual ~FV1();

public:
    enum { IDD = IDD_FV1 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
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
    CWnd m_splitter;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStaView();
};


