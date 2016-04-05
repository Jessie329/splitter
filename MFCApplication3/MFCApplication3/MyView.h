#if !defined(AFX_MYVIEW_H__162E80A3_7868_4EA4_8283_E897418A5857__INCLUDED_)
#define AFX_MYVIEW_H__162E80A3_7868_4EA4_8283_E897418A5857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyView view
#include "MyDocument.h"
#include "DisplayView.h"
class CMyView : public  CDisplayView
{
protected:
	CMyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYVIEW_H__162E80A3_7868_4EA4_8283_E897418A5857__INCLUDED_)
