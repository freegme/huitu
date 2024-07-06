
// MFCApplication2View.cpp: CMFCApplication2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"
#include"myfile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGeometryDialog.h"
#include "CGrid.h"

// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFCApplication2View::Ongeodatacode)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplication2View 构造/析构

CMFCApplication2View::CMFCApplication2View() noexcept : grid(1000, 1000, 50) // 初始化网格，假设视图大小为 1000x1000，网格单元大小为 50
{
	// TODO: 在此处添加构造代码

}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 绘图

void CMFCApplication2View::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	static bool fileRead = false;
	if (!fileRead) {
		if (filedata.ReadFile("武汉实习数据.usr")) {
			fileRead = true;
		}
	}
	
	
	filedata.DrawAllGeometries(pDC);
	// 将几何对象添加到网格中
	for (size_t i = 0; i < filedata.geometries.size(); ++i) {
		grid.AddGeometry(static_cast<int>(i), filedata.geometries[i]);
	}

}
	
	// TODO: 在此处为本机数据添加绘制代码



// CMFCApplication2View 打印


void CMFCApplication2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication2View 诊断

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View 消息处理程序


void CMFCApplication2View::Ongeodatacode()
{
	// TODO: 在此添加命令处理程序代码
	CGeometryDialog dlg;
	dlg.SetGeometriesData(filedata.geometries); // 传递几何数据到对话框

	if (dlg.DoModal() == IDOK) {
		// 获取用户输入的 code
		int code = dlg.GetCode();
		std::vector<std::shared_ptr<CGeometryDataBase>> foundGeometries;

		// 在几何数据中找到相同 code 的对象
		for (const auto& geom : filedata.geometries) {
			if (geom->GetCode() == code) {
				foundGeometries.push_back(geom);
			}
		}

		// 更新对话框的 ListBox
		

		// 在视图中更新选中的几何对象并重绘
		//if (!foundGeometries.empty()) {
		//	m_selectedGeometry = foundGeometries.front(); // 选中第一个符合条件的几何对象
		//	Invalidate(); // 触发重绘
		//}
	}

}


void CMFCApplication2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonDown(nFlags, point);
	int row = point.y / 50 ;
	int col = point.x / 50 ;
	grid.m_grid[row][col];
	double minDistance = 100; // 初始化为一个很大的值，表示无穷大
	for (auto& geom : grid.m_grid[row][col])
	{
		double distance = filedata.geometries[geom]->distanceTo(point);
			if (distance < 4) 
			{
				CDC* pdc = GetDC();
				filedata.geometries[geom]->Drawbuing(pdc);
				// 准备ID、Code和Type信息
				CString message;
				message.Format(_T("ID: %d, Code: %d, Type: %s"),
					filedata.geometries[geom]->GetID(),
					filedata.geometries[geom]->GetCode(),
					filedata.geometries[geom]->GetType());

				AfxMessageBox(message);
				break;
			}
	}


}
