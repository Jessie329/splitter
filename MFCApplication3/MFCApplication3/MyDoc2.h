#if !defined(AFX_MYDOC2_H__4E9EE9E1_9717_48B0_B301_F3A4CBBC3334__INCLUDED_)
#define AFX_MYDOC2_H__4E9EE9E1_9717_48B0_B301_F3A4CBBC3334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDoc2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDoc2 document

class CMyDoc2 : public CDocument
{
public:
	CMyDoc2();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyDoc2)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDoc2)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDoc2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDoc2)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDOC2_H__4E9EE9E1_9717_48B0_B301_F3A4CBBC3334__INCLUDED_)
