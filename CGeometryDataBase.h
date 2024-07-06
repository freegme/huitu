#pragma once
#include"vector"
#include"CPointF.h"
#include"string"
class CGeometryDataBase
{
public:
    int id;             // ���ζ���ID
    int code;           // ���ζ������
    std::vector<CPointF> mMembers; // ����㼯��
    CString type;
    // ���캯��
    CGeometryDataBase(int id, int code, const std::vector<CPointF>& members)
        : id(id), code(code), mMembers(members) {}

    // ����������
    virtual ~CGeometryDataBase() {}
    int GetID() { return id; }
    int GetCode() { return code; }
    // ���麯�������ڻ��Ƽ��ζ���
    virtual void Draw(CDC* pDC) = 0;
    CString GetType() { return type; }
    virtual void GetBoundingBox(int& xMin, int& yMin, int& xMax, int& yMax) const = 0; // ��ȡ��Χ��
    virtual double distanceTo(CPoint& point)=0 ;
    virtual void Drawbuing(CDC* pDC) = 0;
};


