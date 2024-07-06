#pragma once
#include"vector"
#include"CPointF.h"
#include"string"
class CGeometryDataBase
{
public:
    int id;             // 几何对象ID
    int code;           // 几何对象代码
    std::vector<CPointF> mMembers; // 坐标点集合
    CString type;
    // 构造函数
    CGeometryDataBase(int id, int code, const std::vector<CPointF>& members)
        : id(id), code(code), mMembers(members) {}

    // 虚析构函数
    virtual ~CGeometryDataBase() {}
    int GetID() { return id; }
    int GetCode() { return code; }
    // 纯虚函数，用于绘制几何对象
    virtual void Draw(CDC* pDC) = 0;
    CString GetType() { return type; }
    virtual void GetBoundingBox(int& xMin, int& yMin, int& xMax, int& yMax) const = 0; // 获取包围盒
    virtual double distanceTo(CPoint& point)=0 ;
    virtual void Drawbuing(CDC* pDC) = 0;
};


