#pragma once
#include "CGeometryDataBase.h"
#include"CPointF.h"
#include <algorithm> // For std::min and std::max
// 取消 min 和 max 宏定义
#undef min
#undef max
class mypolygon :
    public CGeometryDataBase
{
public:
    // 构造函数
    mypolygon(int id, int code, const std::vector<CPointF>& members)
        : CGeometryDataBase(id, code, members) {
        type = "面";
    }

    // 绘制面对象
    void Draw(CDC* pDC) override {
        CPen pen(PS_SOLID, 2, RGB(0, 0, 255));  // 定义画笔
        CBrush brush(RGB(0, 0, 255));  // 定义刷子
        CPen* oldPen = pDC->SelectObject(&pen);
        CBrush* oldBrush = pDC->SelectObject(&brush);

        // 转换CPointF到CPoint以适应Polygon函数
       
		if (code == 20003)//河流湖泊
		{
			type = "河流湖泊";
			CPen pen;
			//pDC->SelectStockObject(NULL_BRUSH);
			pen.CreatePen(0, 2, RGB(0, 143, 215));//河流边界
			pDC->SelectObject(&pen);

			CBrush br;
			br.CreateSolidBrush(RGB(160, 217, 246));
			CBrush* pOld = pDC->SelectObject(&br);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len - 1; i++)
			{
				pt[i].x = long(mMembers[i].x );
				pt[i].y = long(mMembers[i].y );
				pt[i + 1].x = long(mMembers[i + 1].x );
				pt[i + 1].y = long(mMembers[i + 1].y );
			}
			pDC->Polygon(pt, len);
			pDC->SelectObject(pOld);//置于最后
		}
		else if (code == 20004)//居民地
		{
			type = "居民地";
			CPen pen;
			pen.CreatePen(0, 2, RGB(0, 0, 0));//居民地边界
			pDC->SelectObject(&pen);
			CBrush br;
			br.CreateSolidBrush(RGB(150, 150, 170));
			CBrush* pOld = pDC->SelectObject(&br);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = long(mMembers[i].x );
				pt[i].y = long(mMembers[i].y );
			}
			pDC->Polygon(pt, len);
			pDC->SelectObject(pOld);//置于最后
		}
		else if (code == 20002)//铁路中转站
		{
			type = "铁路中转站";
			CPen pen;
			pen.CreatePen(0, 2, RGB(0, 0, 0));
			pDC->SelectObject(&pen);
			CBrush br(HS_BDIAGONAL, RGB(0, 0, 0));
			CBrush* pOld = pDC->SelectObject(&br);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = long(mMembers[i].x);
				pt[i].y = long(mMembers[i].y);
			}
			pDC->Polygon(pt, len);
			pDC->SelectObject(pOld);
		}
		else if (code == 20001)//码头
		{
			type = "码头";
			CPen pen;
			pen.CreatePen(0, 1, RGB(0, 0, 0));
			pDC->SelectObject(&pen);
			CBrush br;
			br.CreateSolidBrush(RGB(150, 150, 30));
			CBrush* pOld = pDC->SelectObject(&br);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = long(mMembers[i].x);
				pt[i].y = long(mMembers[i].y);
			}
			pDC->Polygon(pt, len);
			pDC->SelectObject(pOld);//置于最后
		}
    }
	CRect minirect(){
			/*std::vector<CPointF> points2(2);

			float maxX = mMembers[0].x;
			float minX = mMembers[0].x;
			float maxY = mMembers[0].y;
			float minY = mMembers[0].y;

			for (size_t i = 1; i < mMembers.size(); ++i) {
				maxX = max(maxX, mMembers[i].x);
				minX = min(minX, mMembers[i].x);
				maxY = max(maxY, mMembers[i].y);
				minY = min(minY, mMembers[i].y);
			}

			points2[0].x = minX;
			points2[0].y = maxY;
			points2[1].x = maxX;
			points2[1].y = minY;
			CRect minr(points2[0].x, points2[0].y,points2[1].x, points2[1].y);
			return minr;*/
		
	}
	void GetBoundingBox(int& xMin, int& yMin, int& xMax, int& yMax) const override 
	{
		xMin = xMax = mMembers[0].x;
		yMin = yMax = mMembers[0].y;
		for (const auto& pt : mMembers)
{
			if (pt.x < xMin) xMin = pt.x;
			if (pt.x > xMax) xMax = pt.x;
			if (pt.y < yMin) yMin = pt.y;
			if (pt.y > yMax) yMax = pt.y; // 计算多边形的包围盒
		}
	}

	double distanceTo(CPoint& point)
	{
		double minDistance = std::numeric_limits<double>::max(); // 初始化最小距离为最大可能值
		int px = point.x; // 获取目标点的x坐标
		int py = point.y; // 获取目标点的y坐标

		// 遍历多边形的每个边
		for (size_t i = 0; i < mMembers.size(); ++i) {
			int x1 = mMembers[i].x; // 当前顶点的x坐标
			int y1 = mMembers[i].y; // 当前顶点的y坐标
			int x2 = mMembers[(i + 1) % mMembers.size()].x; // 下一个顶点的x坐标（环绕到第一个顶点）
			int y2 = mMembers[(i + 1) % mMembers.size()].y; // 下一个顶点的y坐标（环绕到第一个顶点）

			double A = px - x1; // 向量px - x1
			double B = py - y1; // 向量py - y1
			double C = x2 - x1; // 边的向量x2 - x1
			double D = y2 - y1; // 边的向量y2 - y1

			double dot = A * C + B * D; // 点乘A和C，B和D
			double len_sq = C * C + D * D; // 边的长度平方
			double param = (len_sq != 0) ? (dot / len_sq) : -1; // 投影参数，防止除零

			double xx, yy;

			if (param < 0) { // 投影点在边的起点之前
				xx = x1;
				yy = y1;
			}
			else if (param > 1) { // 投影点在边的终点之后
				xx = x2;
				yy = y2;
			}
			else { // 投影点在边的中间
				xx = x1 + param * C;
				yy = y1 + param * D;
			}

			double dx = px - xx; // 投影点与目标点的x差
			double dy = py - yy; // 投影点与目标点的y差
			double distance = sqrt(dx * dx + dy * dy); // 计算欧几里得距离
			minDistance = std::min(minDistance, distance); // 更新最小距离
		}

		return minDistance; // 返回最小距离
	}

	void Drawbuing(CDC* pDC)
	{
		int len = mMembers.size();
		POINT* pt = new POINT[len];
		for (int i = 0; i < len; i++)
		{
			pt[i].x = mMembers[i].x;
			pt[i].y = mMembers[i].y;
		}
		CPen pen;
		pen.CreatePen(1, 8, RGB(144, 253, 0));
		pDC->SelectObject(&pen);
		pDC->Polyline(pt, len);
	}

};

