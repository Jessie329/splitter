// MyDoc2.cpp : implementation file
//

#include "stdafx.h"
#include "MyDoc2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDoc2

IMPLEMENT_DYNCREATE(CMyDoc2, CDocument)

CMyDoc2::CMyDoc2()
{
}

BOOL CMyDoc2::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMyDoc2::~CMyDoc2()
{
}


BEGIN_MESSAGE_MAP(CMyDoc2, CDocument)
	//{{AFX_MSG_MAP(CMyDoc2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDoc2 diagnostics

#ifdef _DEBUG
void CMyDoc2::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc2::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDoc2 serialization

void CMyDoc2::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyDoc2 commands
