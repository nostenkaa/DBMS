// TreeTables.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
#include "DBMSDoc.h"
#include "DBMSView.h"
#include "TreeTables.h"


// TreeTables
IMPLEMENT_DYNCREATE(CTreeTables, CTreeView)

CTreeTables::CTreeTables()
{
}

CTreeTables::~CTreeTables()
{
}

BEGIN_MESSAGE_MAP(CTreeTables, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// TreeTables diagnostics

#ifdef _DEBUG
void CTreeTables::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hCustomers = tree.InsertItem(L"Customers", -1, -1, NULL, TVI_ROOT);
	m_hOrders = tree.InsertItem(L"Orders", -1, -1, NULL, TVI_ROOT);
	m_hPhones = tree.InsertItem(L"Phones", -1, -1, NULL, TVI_ROOT);

	tree.SetCheck(m_hCustomers, m_pDoc->m_bCustomers);
	tree.SetCheck(m_hOrders, m_pDoc->m_bOrders);
	tree.SetCheck(m_hPhones, m_pDoc->m_bPhones);
}


void CTreeTables::AssertValid() const
{
	CTreeView::AssertValid();
}


#ifndef _WIN32_WCE
void CTreeTables::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// TreeTables message handlers


int CTreeTables::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES
		| TVS_HASBUTTONS
		| TVS_LINESATROOT
		| TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CTreeTables::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;
	auto selTreeItem = tree.GetSelectedItem();
	if (selTreeItem == nullptr) {
		return;
	}
	auto selTable = tree.GetItemText(selTreeItem);
	if (selTable == "Customers") {
		m_pDoc->m_bCustomers = true;
		m_pDoc->m_pView->currTable = "Customers";
		m_pDoc->m_bOrders = m_pDoc->m_bPhones = false;
	}
	
	if (selTable == "Orders") {
		m_pDoc->m_bOrders = true;
		m_pDoc->m_pView->currTable = "Orders";
		m_pDoc->m_bCustomers = m_pDoc->m_bPhones = false;
	}

	if (selTable == "Phones") {
		m_pDoc->m_bPhones = true;
		m_pDoc->m_pView->currTable = "Phones";
		m_pDoc->m_bCustomers = m_pDoc->m_bOrders = false;
	}
	
	ShowNewTable();
}

void CTreeTables::ShowNewTable()
{
	m_pDoc->m_pView->ClearView();
	m_pDoc->m_pView->FillTable();
}

