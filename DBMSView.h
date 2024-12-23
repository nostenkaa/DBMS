
// DBMSView.h : interface of the CDBMSView class
//

#pragma once

#include "DBMSDoc.h";
#include <string>
class CDBMSView : public CListView
{
protected: // create from serialization only
	CDBMSView() noexcept;
	DECLARE_DYNCREATE(CDBMSView)

// Attributes
public:
	CDBMSDoc* GetDocument() const;

	int countColumns;

	std::string currTable;
// Operations
public:
	void FillTable();
	void ClearView();
	void GetData(std::string tableName, CListCtrl& listCtrl);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDBMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActionsAdddata();
};

#ifndef _DEBUG  // debug version in DBMSView.cpp
inline CDBMSDoc* CDBMSView::GetDocument() const
   { return reinterpret_cast<CDBMSDoc*>(m_pDocument); }
#endif

