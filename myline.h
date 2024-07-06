#pragma once
#include "CGeometryDataBase.h"
#include"CPointF.h"
#define NOMINMAX // �ڰ���Windowsͷ�ļ�֮ǰ���������
#include <windows.h>
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>
#undef min
#undef max
// ȡ�� min �� max �궨��

class myline :
    public CGeometryDataBase
{
public:
    // ���캯��
    myline(int id, int code, const std::vector<CPointF>& members)
        : CGeometryDataBase(id, code, members) {
        type = "��";
    }

    // �����߶���
    void Draw(CDC* pDC) override {
       
		if (code == 10000)//ͼ����
		{
			type = "ͼ����";
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

		else if (code == 10004 )//��Ҫ��·
		{
			type = "��Ҫ��·";
			int len = mMembers.size();
			POINT* pt = new POINT[len];
			for (int i = 0; i < len; i++)
			{
				pt[i].x = mMembers[i].x;
				pt[i].y = mMembers[i].y;
			}
			CPen pen1;	//��ɫ���
			pen1.CreatePen(1, 5, RGB(0, 0, 0));
			pDC->SelectObject(&pen1);
			pDC->Polyline(pt, len);

			CPen pen;//��ɫ��·
			pDC->SelectStockObject(NULL_BRUSH);
			pen.CreatePen(1, 3, RGB(255, 200, 0));
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->Polyline(pt, len);
		}

		else if (code == 10001 )//��·
		{
			type = "��·";
			CPen pen1;//�ⲿ��ɫ�߿�
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
			//�ڲ��ڰ����
			DWORD dwdstyles[] = { 15,15 };
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(255, 255, 255);
			CPen pen(PS_GEOMETRIC | PS_USERSTYLE, 2, &lb, 2, dwdstyles);
			pDC->SelectObject(&pen);
			pDC->Polyline(pt, len);
		}
		else if (code == 10003)//��������
		{
			type = "��������";
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
		delete[] pt; // �ͷ��ڴ�
	}

	double distanceTo( CPoint& point)  {
		double minDistance = std::numeric_limits<double>::max(); // ��ʼ����С����Ϊ������ֵ
		int px = point.x; // ��ȡĿ����x����
		int py = point.y; // ��ȡĿ����y����

		// ��������ε�ÿ����
		for (size_t i = 0; i < mMembers.size(); ++i) {
			int x1 = mMembers[i].x; // ��ǰ�����x����
			int y1 = mMembers[i].y; // ��ǰ�����y����
			int x2 = mMembers[(i + 1) % mMembers.size()].x; // ��һ�������x���꣨���Ƶ���һ�����㣩
			int y2 = mMembers[(i + 1) % mMembers.size()].y; // ��һ�������y���꣨���Ƶ���һ�����㣩

			double A = px - x1; // ����px - x1
			double B = py - y1; // ����py - y1
			double C = x2 - x1; // �ߵ�����x2 - x1
			double D = y2 - y1; // �ߵ�����y2 - y1

			double dot = A * C + B * D; // ���A��C��B��D
			double len_sq = C * C + D * D; // �ߵĳ���ƽ��
			double param = (len_sq != 0) ? (dot / len_sq) : -1; // ͶӰ��������ֹ����

			double xx, yy;

			if (param < 0) { // ͶӰ���ڱߵ����֮ǰ
				xx = x1;
				yy = y1;
			}
			else if (param > 1) { // ͶӰ���ڱߵ��յ�֮��
				xx = x2;
				yy = y2;
			}
			else { // ͶӰ���ڱߵ��м�
				xx = x1 + param * C;
				yy = y1 + param * D;
			}

			double dx = px - xx; // ͶӰ����Ŀ����x��
			double dy = py - yy; // ͶӰ����Ŀ����y��
			double distance = sqrt(dx * dx + dy * dy); // ����ŷ����þ���
			minDistance = std::min(minDistance, distance); // ������С����
		}
		return minDistance; // ������С����
	}
	
};

