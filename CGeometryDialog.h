// CGeometryDialog.h
#pragma once

#include "afxdialogex.h"
#include <vector>
#include <memory>
#include "CGeometryDataBase.h"

class CGeometryDialog : public CDialogEx {
    DECLARE_DYNAMIC(CGeometryDialog)

public:
    CGeometryDialog(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CGeometryDialog();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

private:
    CEdit m_EditCode;
    CListBox m_ListBox;
    int code;
    std::vector<std::shared_ptr<CGeometryDataBase>> geometriesdata;

public:
    int GetCode() const;
    void UpdateListBox(const std::vector<std::shared_ptr<CGeometryDataBase>>& geometries);
    void SetGeometriesData(const std::vector<std::shared_ptr<CGeometryDataBase>>& geometries);
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnLbnSelchangeList1();
};
