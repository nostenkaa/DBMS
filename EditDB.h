#pragma once
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "MainFrm.h"

#define ADD 0
#define EDIT 1

// EditDB dialog

class EditDB : public CDialog
{
	DECLARE_DYNAMIC(EditDB)

public:
	EditDB(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditDB();
	
	CString id;
	int typeAccess;
	int countFields;

	CString C1;
	CString C2;
	CString C3;
	CString C4;
	CString C5;
	CString C6;

	//vector<CString> k;

	string currTable;
	string query;

	CMainFrame* pFrame;

	vector<CString> GetData();

	void ConfigureWindow();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EDIT_DB_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();


protected:
	virtual BOOL OnInitDialog();


	CEdit e_C2;
	CEdit e_C1;
	CEdit e_C3;
	CEdit e_C4;
	CEdit e_C5;
	CEdit e_C6;

	CStatic t_C1;
	CStatic t_C2;
	CStatic t_C3;
	CStatic t_C4;
	CStatic t_C5;
	CStatic t_C6;

	CButton btn_OK;
	CButton btn_Cancel;
};
