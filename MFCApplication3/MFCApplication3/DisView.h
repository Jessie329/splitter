#if !defined(AFX_DISVIEW_H__0E8A5A50_9D2E_4497_AA3F_D8291DD4ECAA__INCLUDED_)
#define AFX_DISVIEW_H__0E8A5A50_9D2E_4497_AA3F_D8291DD4ECAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisView view
#include "MyDocument.h"
#include "DisplayView.h"
class CDisView : public  CDisplayView
{
protected:
	CDisView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDisView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISVIEW_H__0E8A5A50_9D2E_4497_AA3F_D8291DD4ECAA__INCLUDED_)
