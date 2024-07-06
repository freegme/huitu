#pragma once
#include "CGeometryDataBase.h"
#include"CPointF.h"

class mypoint :
    public CGeometryDataBase
{
public:
    // 构造函数
    mypoint(int id, int code, const std::vector<CPointF>& members)
        : CGeometryDataBase(id, code, members) {
        type = "点";
    }

    // 绘制点对象
    void Draw(CDC* pDC) override {
        
      
        CPen pen;
        pen.CreatePen(1, 3, RGB(255, 0, 0));

        CPen* pOldPen = pDC->SelectObject(&pen);
        pDC->Rectangle(mMembers[0].x - 2, mMembers[0].y - 2, mMembers[0].x + 2, mMembers[0].y + 2);
        pDC->SelectObject(pOldPen);
    }

    void GetBoundingBox(int& xMin, int& yMin, int& xMax, int& yMax) const override {
        xMin = xMax = mMembers[0].x;
        yMin = yMax = mMembers[0].y; // 点的包围盒即为点本身
    }
   
    // 计算当前点到另一个点之间的欧氏距离
    double distanceTo(CPoint& other) 
    {
        return sqrt(pow(other.x - mMembers[0].x, 2) +pow(other.y - mMembers[0].y, 2));
    }
    void Drawbuing(CDC* pDC) 
    {


        CPen pen;
        pen.CreatePen(1, 6, RGB(144,253, 0));

        CPen* pOldPen = pDC->SelectObject(&pen);
        pDC->Rectangle(mMembers[0].x - 2, mMembers[0].y - 2, mMembers[0].x + 2, mMembers[0].y + 2);
        pDC->SelectObject(pOldPen);
    }

};

