
// DBMSDoc.h : interface of the CDBMSDoc class
//


#pragma once


class CDBMSView;
class CTreeTables;
class CDBMSDoc : public CDocument
{
protected: // create from serialization only
	CDBMSDoc() noexcept;
	DECLARE_DYNCREATE(CDBMSDoc)

// Attributes
public:
	bool m_bCustomers, m_bOrders, m_bPhones;

	CTreeTables* m_pTree;
	CDBMSView* m_pView;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void OnCloseDocument();
	afx_msg void OnEditDbDlg();
	afx_msg void OnActionsAdddata();
};
