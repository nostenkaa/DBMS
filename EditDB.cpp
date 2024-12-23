// EditDB.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
#include "afxdialogex.h"
#include "EditDB.h"
#include <string>
#include <sstream>


// EditDB dialog

IMPLEMENT_DYNAMIC(EditDB, CDialog)

EditDB::EditDB(CWnd* pParent /*=nullptr*/)
	: CDialog(EDIT_DB_DLG, pParent)
{

}

EditDB::~EditDB()
{
}

void EditDB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EDIT_C1, e_C1);
	DDX_Control(pDX, EDIT_C2, e_C2);
	DDX_Control(pDX, EDIT_C3, e_C3);
	DDX_Control(pDX, EDIT_C4, e_C4);
	DDX_Control(pDX, EDIT_C5, e_C5);
	DDX_Control(pDX, EDIT_C6, e_C6);

	DDX_Control(pDX, TEXT_C1, t_C1);
	DDX_Control(pDX, TEXT_C2, t_C2);
	DDX_Control(pDX, TEXT_C3, t_C3);
	DDX_Control(pDX, TEXT_C4, t_C4);
	DDX_Control(pDX, TEXT_C5, t_C5);
	DDX_Control(pDX, TEXT_C6, t_C6);
	DDX_Control(pDX, IDOK, btn_OK);
	DDX_Control(pDX, IDCANCEL, btn_Cancel);
}

//EDIT_C1
//EDIT_C2
//EDIT_C3
//EDIT_C4
//TEXT_C1
//TEXT_C2
//TEXT_C3
//TEXT_C4

//EDIT_C5
//EDIT_C6

//TEXT_C5
//TEXT_C6

BEGIN_MESSAGE_MAP(EditDB, CDialog)
	ON_BN_CLICKED(IDOK, &EditDB::OnBnClickedOk)
END_MESSAGE_MAP()


// EditDB message handlers


void EditDB::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void EditDB::OnBnClickedOk()
{
	UpdateData(TRUE);

	CString newC1;
	e_C1.GetWindowText(newC1);

	CString newC2;
	e_C2.GetWindowText(newC2);

	CString newC3;
	e_C3.GetWindowText(newC3);

	CString newC4;
	e_C4.GetWindowText(newC4);

	CString newC5;
	e_C5.GetWindowText(newC5);

	CString newC6;
	e_C6.GetWindowText(newC6);

	std::ostringstream oss;
	if (typeAccess == EDIT) {
		if (currTable == "Customers") {
			oss << "UPDATE customers SET "
				<< "first_name = '" << CT2A(newC1)
				<< "', last_name = '" << CT2A(newC2)
				<< "', middle_name = '" << CT2A(newC3)
				<< "', birth_date = '" << CT2A(newC4)
				<< "', city = '" << CT2A(newC5)
				<< "', email = '" << CT2A(newC6)
				<< "' WHERE customer_id = " << CT2A(id);
		}
		if (currTable == "Orders") {
			oss << "UPDATE orders "
				<< "SET order_date = '" << CT2A(newC1) << "', "
				<< "order_total = " << CT2A(newC2) << ", "
				<< "customer_id = (SELECT  customer_id FROM customers WHERE last_name = '" << CT2A(newC4) << "'), "
				<< "phone_id = (SELECT phone_id FROM phones WHERE model = '" << CT2A(newC5) << "') "
				<< "WHERE order_id = " << CT2A(id);
		}
		if (currTable == "Phones") {
			oss << "UPDATE phones SET "
				<< "brand = '" << CT2A(newC1)
				<< "', model = '" << CT2A(newC2)
				<< "', price = '" << CT2A(newC3)
				<< "', stock_quantity = '" << CT2A(newC4)
				<< "', release_year = '" << CT2A(newC5)
				<< "' WHERE phone_id = " << CT2A(id);
		}
	}

	if (typeAccess == ADD) {
		if(currTable == "Customers") {
			oss << "INSERT INTO customers(first_name, last_name, middle_name, birth_date, city, email) "
				<< "VALUES('" << CT2A(newC1)
				<< "', '" << CT2A(newC2)
				<< "', '" << CT2A(newC3)
				<< "', '" << CT2A(newC4)
				<< "', '" << CT2A(newC5)
				<< "', '" << CT2A(newC6)
				<< "')";
		}
		if(currTable == "Orders") {
			oss << "INSERT INTO orders (order_date, order_total, customer_id, phone_id) "
				<< "VALUES ('" << CT2A(newC1) << "', " << CT2A(newC2)  << ", " 
				<< "(SELECT customer_id  FROM customers WHERE last_name = '"  << CT2A(newC3) << "'), "
				<< "(SELECT phone_id FROM phones WHERE model = '" << CT2A(newC4) << "'))";
		}
		if (currTable == "Phones") {
			oss << "INSERT INTO phones (brand, model, price, stock_quantity, release_year) "
				<< "VALUES ('"
				<< CT2A(newC1)
				<< "', '" << CT2A(newC2)
				<< "', '" << CT2A(newC3)
				<< "', '" << CT2A(newC4)
				<< "', " << CT2A(newC5)
				<< ")";
		}
	}

	query = oss.str();

	CDialog::OnOK();
}

vector<CString> EditDB::GetData()
{
	vector<CString> data;/*
	for(int i = countFields; i < countFields; i++)*/
	data.push_back(C1);
	data.push_back(C2);
	data.push_back(C3);
	data.push_back(C4);
	data.push_back(C5);
	data.push_back(C6);
	return data;
}

void EditDB::ConfigureWindow()
{
	auto width = GetSystemMetrics(SM_CXSCREEN);
	auto height = GetSystemMetrics(SM_CYSCREEN);
	
	CRect rc;
	GetClientRect(&rc);
	
	int szWndX;
	int szWndY;

	int x1 = 10;
	int y1 = 30;

	int x2 = x1+1;
	int y2 = 10;
	if(currTable == "Customers") {
		countFields = 6;

		szWndX = 900;
		szWndY = 200;

		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);

		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1+=150, y1, 100, 20);
		e_C3.MoveWindow(x1+=150, y1, 100, 20);
		e_C4.MoveWindow(x1+=150, y1, 100, 20);
		e_C5.MoveWindow(x1+=150, y1, 100, 20);
		e_C6.MoveWindow(x1+=150, y1, 100, 20);

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);
		t_C6.MoveWindow(x2 += 150, y2, 100, 20);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);
		
		t_C1.SetWindowTextW(L"First name");
		t_C2.SetWindowTextW(L"Last name");
		t_C3.SetWindowTextW(L"Middle name");
		t_C4.SetWindowTextW(L"Birth date");
		t_C5.SetWindowTextW(L"City");
		t_C6.SetWindowTextW(L"Email");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
		e_C6.SetWindowTextW(C6);
		
	}

	if (currTable == "Orders") {
		countFields = 5;

		szWndX = 850;
		szWndY = 200;
		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);

		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1 += 150, y1, 100, 20);
		e_C3.MoveWindow(x1 += 150, y1, 100, 20);
		e_C4.MoveWindow(x1 += 150, y1, 100, 20);
		

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		


		t_C5.ShowWindow(SW_HIDE);
		e_C5.ShowWindow(SW_HIDE);
		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Order date");
		t_C2.SetWindowTextW(L"Order total");
		t_C3.SetWindowTextW(L"Customers lastname");
		t_C4.SetWindowTextW(L"Model");


		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
	}

	if (currTable == "Phones") {
		countFields = 5;

		szWndX = 750;
		szWndY = 200;

		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);
		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1 += 150, y1, 100, 20);
		e_C3.MoveWindow(x1 += 150, y1, 100, 20);
		e_C4.MoveWindow(x1 += 150, y1, 100, 20);
		e_C5.MoveWindow(x1 += 150, y1, 100, 20);

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);

		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Brand");
		t_C2.SetWindowTextW(L"Model");
		t_C3.SetWindowTextW(L"Price");
		t_C4.SetWindowTextW(L"Stock quantity");
		t_C5.SetWindowTextW(L"Release year");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
	}
}

BOOL EditDB::OnInitDialog()
{
	CDialog::OnInitDialog();

	ConfigureWindow();
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


