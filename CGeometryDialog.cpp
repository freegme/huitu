// CGeometryDialog.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication2.h"
#include "afxdialogex.h"
#include "CGeometryDialog.h"
#include "string"
#include <cmath> 
// CGeometryDialog 对话框

IMPLEMENT_DYNAMIC(CGeometryDialog, CDialogEx)

CGeometryDialog::CGeometryDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG1, pParent), code(-1) {
}

CGeometryDialog::~CGeometryDialog() {
}

void CGeometryDialog::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_EditCode);
    DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(CGeometryDialog, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CGeometryDialog::OnBnClickedButton1)
    ON_EN_CHANGE(IDC_EDIT1, &CGeometryDialog::OnEnChangeEdit1)
    ON_LBN_SELCHANGE(IDC_LIST1, &CGeometryDialog::OnLbnSelchangeList1)
END_MESSAGE_MAP()

BOOL CGeometryDialog::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 初始化控件
    if (!m_EditCode.GetSafeHwnd()) {
        AfxMessageBox(_T("Failed to initialize Edit control"));
        return FALSE;
    }
    if (!m_ListBox.GetSafeHwnd()) {
        AfxMessageBox(_T("Failed to initialize ListBox control"));
        return FALSE;
    }

    return TRUE; // return TRUE unless you set the focus to a control
}

int CGeometryDialog::GetCode() const {
    CString codeStr;
    // 确保 Edit 控件句柄有效
    if (!m_EditCode.GetSafeHwnd()) {
        AfxMessageBox(_T("Edit control is not initialized"));
        return -1;
    }

    // 获取 Edit 控件文本
    m_EditCode.GetWindowText(codeStr);

    // 检查是否为空
    if (codeStr.IsEmpty()) {
        AfxMessageBox(_T("Code cannot be empty"));
        return -1; // 返回非法代码
    }

    int code;
    if (_stscanf_s(codeStr, _T("%d"), &code) != 1) {
        AfxMessageBox(_T("Invalid code format"));
        return -1; // 返回非法代码
    }

    return code;
}

void CGeometryDialog::UpdateListBox(const std::vector<std::shared_ptr<CGeometryDataBase>>& geometries) {
    if (!m_ListBox.GetSafeHwnd()) {
        AfxMessageBox(_T("ListBox control is not initialized"));
        return;
    }

    m_ListBox.ResetContent(); // 清空 ListBox
    for (const auto& geom : geometries) {
       
        CString str;
        str.Format(_T("ID: %d, Code: %d, Type: %s"), geom->GetID(), geom->GetCode(), geom->GetType());
        m_ListBox.AddString(str);
    }
}

void CGeometryDialog::SetGeometriesData(const std::vector<std::shared_ptr<CGeometryDataBase>>& geometries) {
    geometriesdata = geometries;
}

void CGeometryDialog::OnBnClickedButton1() {
    // 获取代码
    code = GetCode();
    if (code == -1) {
        // 获取代码失败，显示错误并阻止对话框关闭
        AfxMessageBox(_T("Invalid code"));
        return;
    }

    // 找到符合条件的几何对象
    std::vector<std::shared_ptr<CGeometryDataBase>> foundGeometries;
    int n = 0;
    for (const auto& geom : geometriesdata) {
        n++;
        if (geom->GetCode() == code) {
            foundGeometries.push_back(geom);
        }
    }

    // 更新 ListBox
    UpdateListBox(foundGeometries);

    // 触发重绘
    Invalidate();
}

void CGeometryDialog::OnEnChangeEdit1() {
    // TODO: 在此添加控件通知处理程序代码
    CString codeStr;
    // 确保 Edit 控件句柄有效
    if (!m_EditCode.GetSafeHwnd()) {
        AfxMessageBox(_T("Edit control is not initialized"));
        return;
    }

    // 获取 Edit 控件文本
    m_EditCode.GetWindowText(codeStr);

    // 检查是否为空
    if (codeStr.IsEmpty()) {
        AfxMessageBox(_T("Code cannot be empty"));
        return; // 返回非法代码
    }

    if (_stscanf_s(codeStr, _T("%d"), &code) != 1) {
        AfxMessageBox(_T("Invalid code format"));
        return; // 返回非法代码
    }
}

void CGeometryDialog::OnLbnSelchangeList1() {
    // TODO: 在此添加控件通知处理程序代码
    if (!m_ListBox.GetSafeHwnd()) {
        AfxMessageBox(_T("ListBox control is not initialized"));
        return;
    }

    int sel = m_ListBox.GetCurSel();
    if (sel == LB_ERR) {
        AfxMessageBox(_T("No item selected"));
        return;
    }

    CString str;
    m_ListBox.GetText(sel, str);
    AfxMessageBox(str);
}
