
// MainFrm.h : interface of the CMainFrame class
//
#include "mysql.h"

#include <string>
#include <vector>
using namespace std;



#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	MYSQL_RES* res, * reslogon, * reslogoff;
	struct Customer{
	CString firstName;
	CString lastName;
	CString middleName;
	CString birthDate;
	CString city;
	CString email;
	CString customerId;
	};

	struct Order {
		CString orderDate;
		CString orderTotal;
		CString customerLastName;
		CString phoneModel;
		CString orderId;
	};

	struct Phone {
		CString brand;
		CString model;
		CString price;
		CString stockQuantity;
		CString releaseYear;
		CString phoneId;
	};
// Operations
public:
	bool OpenTrans();
	bool CloseTrans();
	bool SendQuery(string query);
	void SelectAllFromTable(string table);
	vector<MYSQL_ROW>* GetData();
	CString GetId(const vector<CString>& vecData, string currTable);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	CSplitterWnd      m_wndSplitter;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	MYSQL* conn;
	MYSQL_ROW row;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:
	
};


