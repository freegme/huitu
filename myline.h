#pragma once
#include "CGeometryDataBase.h"
#include"CPointF.h"
#define NOMINMAX // 在包含Windows头文件之前定义这个宏
#include <windows.h>
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>
#undef min
#undef max
// 取消 min 和 max 宏定义

class myline :
    public CGeometryDataBase
{
public:
    // 构造函数
    myline(int id, int code, const std::vector<CPointF>& members)
        : CGeometryDataBase(id, code, members) {
        type = "线";
    }

    // 绘制线对象
    void Draw(CDC* pDC) override {
       
		if (code == 10000)//图廓点
		{
			type = "图廓点";
			CPen pen;
			pDC->SelectStockObject(NULL_BRUSH);
			pen.CreatePen(0, 3, RGB(0, 0, 0));
			CPen* pOldPen = pDC->SelectObject(&pen);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = mMembers[i].x;
				pt[i].y = mMembers[i].y;
			}
			pDC->Polyline(pt, len);
		}

		else if (code == 10004 )//主要道路
		{
			type = "主要道路";
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = mMembers[i].x;
				pt[i].y = mMembers[i].y;
			}
			CPen pen1;	//黑色外框
			pen1.CreatePen(1, 5, RGB(0, 0, 0));
			pDC->SelectObject(&pen1);
			pDC->Polyline(pt, len);

			CPen pen;//黄色道路
			pDC->SelectStockObject(NULL_BRUSH);
			pen.CreatePen(1, 3, RGB(255, 200, 0));
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->Polyline(pt, len);
		}

		else if (code == 10001 )//铁路
		{
			type = "铁路";
			CPen pen1;//外部黑色边框
			pen1.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
			pDC->SelectObject(&pen1);
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = mMembers[i].x;
				pt[i].y = mMembers[i].y;
			}
			pDC->Polyline(pt, len);
			//内部黑白相间
			DWORD dwdstyles[] = { 15,15 };
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(255, 255, 255);
			CPen pen(PS_GEOMETRIC | PS_USERSTYLE, 2, &lb, 2, dwdstyles);
			pDC->SelectObject(&pen);
			pDC->Polyline(pt, len);
		}
		else if (code == 10003)//汽渡虚线
		{
			type = "汽渡虚线";
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = mMembers[i].x;
				pt[i].y = mMembers[i].y;
			}
			CPen pen1;
			pen1.CreatePen(PS_DOT, 1, RGB(0, 0, 255));
			pDC->SelectObject(&pen1);
			pDC->Polyline(pt, len);
		}
    }
	

	void GetBoundingBox(int& xMin, int& yMin, int& xMax, int& yMax)const {
		if (mMembers.empty()) return;

		float maxX = mMembers[0].x;
		float minX = mMembers[0].x;
		float maxY = mMembers[0].y;
		float minY = mMembers[0].y;

		for (size_t i = 1; i < mMembers.size(); ++i) {
			maxX = std::max(maxX, static_cast<float>(mMembers[i].x));
			minX = std::min(minX, static_cast<float>(mMembers[i].x));
			maxY = std::max(maxY, static_cast<float>(mMembers[i].y));
			minY = std::min(minY, static_cast<float>(mMembers[i].y));
		}

		xMin = static_cast<int>(minX);
		yMin = static_cast<int>(minY);
		xMax = static_cast<int>(maxX);
		yMax = static_cast<int>(maxY);
	}

	void Drawbuing(CDC* pDC) {
		int len = mMembers.size();
		POINT* pt = new POINT[len];
		for (int i = 0; i < len; i++) {
			pt[i].x = mMembers[i].x;
			pt[i].y = mMembers[i].y;
		}
		CPen pen;
		pen.CreatePen(1, 8, RGB(144, 253, 0));
		pDC->SelectObject(&pen);
		pDC->Polyline(pt, len);
		delete[] pt; // 释放内存
	}

	double distanceTo( CPoint& point)  {
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
	
};

