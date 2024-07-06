#pragma once
#include "CGeometryDataBase.h"
#include"CPointF.h"
#include <algorithm> // For std::min and std::max
// ȡ�� min �� max �궨��
#undef min
#undef max
class mypolygon :
    public CGeometryDataBase
{
public:
    // ���캯��
    mypolygon(int id, int code, const std::vector<CPointF>& members)
        : CGeometryDataBase(id, code, members) {
        type = "��";
    }

    // ���������
    void Draw(CDC* pDC) override {
        CPen pen(PS_SOLID, 2, RGB(0, 0, 255));  // ���廭��
        CBrush brush(RGB(0, 0, 255));  // ����ˢ��
        CPen* oldPen = pDC->SelectObject(&pen);
        CBrush* oldBrush = pDC->SelectObject(&brush);

        // ת��CPointF��CPoint����ӦPolygon����
       
		if (code == 20003)//��������
		{
			type = "��������";
			CPen pen;
			//pDC->SelectStockObject(NULL_BRUSH);
			pen.CreatePen(0, 2, RGB(0, 143, 215));//�����߽�
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
			pDC->SelectObject(pOld);//�������
		}
		else if (code == 20004)//�����
		{
			type = "�����";
			CPen pen;
			pen.CreatePen(0, 2, RGB(0, 0, 0));//����ر߽�
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
			pDC->SelectObject(pOld);//�������
		}
		else if (code == 20002)//��·��תվ
		{
			type = "��·��תվ";
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
		else if (code == 20001)//��ͷ
		{
			type = "��ͷ";
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
			pDC->SelectObject(pOld);//�������
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
			if (pt.y > yMax) yMax = pt.y; // �������εİ�Χ��
		}
	}

	double distanceTo(CPoint& point)
	{
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

