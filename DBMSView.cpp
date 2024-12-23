
// DBMSView.cpp : implementation of the CDBMSView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DBMS.h"
#endif

#include "DBMSDoc.h"
#include "MainFrm.h"
#include "DBMSView.h"
#include "TreeTables.h"

#include "mysql.h"
#include "EditDB.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CMainFrame;
// CDBMSView

IMPLEMENT_DYNCREATE(CDBMSView, CListView)

BEGIN_MESSAGE_MAP(CDBMSView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CDBMSView::OnNMDblclk)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ACTIONS_ADDDATA, &CDBMSView::OnActionsAdddata)
END_MESSAGE_MAP()

// CDBMSView construction/destruction

CDBMSView::CDBMSView() noexcept
{
	// TODO: add construction code here

}

CDBMSView::~CDBMSView()
{
}

BOOL CDBMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}


void CDBMSView::FillTable()
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl& listCtrl = GetListCtrl();	

	if (pDoc->m_bCustomers) {
		
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Firstname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Lastname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Middlename"), LVCFMT_LEFT, 250);
		listCtrl.InsertColumn(4, _T("BirthDate"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("City"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(6, _T("Email"), LVCFMT_LEFT, 150);
		countColumns = 7;

		string tableName = "customers";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bOrders) {
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("OrderDate"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("OrderTotal"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Customer Lastname"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(4, _T("Model"), LVCFMT_LEFT, 175);

		countColumns = 5;

		string tableName = "orders";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bPhones) {
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Brand"), LVCFMT_LEFT, 200);
		listCtrl.InsertColumn(2, _T("Model"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Price"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(4, _T("StockQuantity"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(5, _T("ReleaseYear"), LVCFMT_LEFT, 100);
		
		countColumns = 6;

		string tableName = "phones";
		GetData(tableName, listCtrl);
	}
}

void CDBMSView::ClearView()
{
	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.DeleteAllItems();
	for (int i = 0; i < countColumns; i++)
		listCtrl.DeleteColumn(0);
}

void CDBMSView::GetData(string tableName, CListCtrl& listCtrl)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (!pFrame)
		return;

	if (!pFrame->OpenTrans())
		return;

	vector<MYSQL_ROW>* data;

	if (currTable == "Orders") {
		string query = "\
			 SELECT\
            o.order_id AS order_id, \
            o.order_date AS OrderDate, \
            o.order_total AS OrderTotal, \
            c.last_name AS ClientLastname, \
            p.model AS PhoneModel \
        FROM orders o \
        JOIN customers c ON o.customer_id = c.customer_id \
        JOIN phones p ON o.phone_id = p.phone_id";
		pFrame->SendQuery(query);
		data = pFrame->GetData();
	}
	else {
		string sql = "SELECT * FROM " + tableName;
		pFrame->SendQuery(sql);
		data = pFrame->GetData();
	}

	for (int rowNumb = 0; rowNumb < data->size(); rowNumb++) {
		MYSQL_ROW row = (*data)[rowNumb];
		listCtrl.SetItemData(rowNumb, 777);
		CString cstrRow;
		cstrRow.Format(_T("%d"), rowNumb + 1);
		listCtrl.InsertItem(rowNumb, cstrRow);
		for (int columnNumb = 1; columnNumb < mysql_num_fields(pFrame->res); columnNumb++) {
			cstrRow = CString(row[columnNumb]);
			
			listCtrl.SetItemText(rowNumb, columnNumb, cstrRow);
		}
	}
	auto t = listCtrl.GetItemData(1);

}

void CDBMSView::OnDraw(CDC* pDC)
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CDBMSView::OnInitialUpdate() 
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.ModifyStyle(0, LVS_REPORT);
	//listCtrl.sub
}


// CDBMSView printing

BOOL CDBMSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBMSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBMSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDBMSView diagnostics

#ifdef _DEBUG
void CDBMSView::AssertValid() const
{
	CListView::AssertValid();
}

void CDBMSView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDBMSDoc* CDBMSView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBMSDoc)));
	return (CDBMSDoc*)m_pDocument;
}
#endif //_DEBUG

void CDBMSView::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Проверяем главное окно
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (!pFrame) {
		AfxMessageBox(_T("Ошибка: главное окно приложения не найдено!"));
		return;
	}

	// Проверяем pNMHDR
	if (!pNMHDR) {
		AfxMessageBox(_T("Ошибка: данные о событии не переданы!"));
		return;
	}

	// Получаем элемент управления
	CListCtrl& listCtrl = GetListCtrl();
	if (!listCtrl.GetSafeHwnd()) {
		AfxMessageBox(_T("Ошибка: доступ к элементу ListCtrl невозможен!"));
		return;
	}

	// Преобразуем указатель события
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem == -1) {
		AfxMessageBox(_T("Ошибка: не выбран элемент для редактирования!"));
		return;
	}

	// Создаем диалоговое окно редактирования
	EditDB dlg;
	dlg.C1 = listCtrl.GetItemText(pNMItemActivate->iItem, 1);
	dlg.C2 = listCtrl.GetItemText(pNMItemActivate->iItem, 2);
	dlg.C3 = listCtrl.GetItemText(pNMItemActivate->iItem, 3);
	dlg.C4 = listCtrl.GetItemText(pNMItemActivate->iItem, 4);
	dlg.C5 = listCtrl.GetItemText(pNMItemActivate->iItem, 5);
	dlg.C6 = listCtrl.GetItemText(pNMItemActivate->iItem, 6);

	
	const vector<CString>& vecData = dlg.GetData();
	if (vecData.empty()) {
		AfxMessageBox(_T("Ошибка: данные для редактирования отсутствуют!"));
		return;
	}

	
	dlg.id = pFrame->GetId(vecData, currTable);
	dlg.currTable = currTable;
	dlg.pFrame = pFrame;
	dlg.typeAccess = EDIT;

	
	if (dlg.DoModal() == IDOK) {
		pFrame->SendQuery(dlg.query);
		ClearView();
		FillTable();
	}


	if (pResult) {
		*pResult = 0;
	}
}


void CDBMSView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CListView::OnRButtonDown(nFlags, point);
	
	ClientToScreen(&point);

	CCmdUI state;
	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	//CListView::OnRButtonDown(nFlags, point);
}


void CDBMSView::OnActionsAdddata()
{
	// TODO: Add your command handler code here

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CListCtrl& listCtrl = GetListCtrl();

	EditDB dlg;

	dlg.currTable = currTable;
	dlg.pFrame = pFrame;
	dlg.typeAccess = ADD;


	if (dlg.DoModal() == IDOK)
	{
		pFrame->SendQuery(dlg.query);
		ClearView();
		FillTable();
	}
}
