// CGrid.h
#pragma once
#include"pch.h"
#include <vector>
#include <unordered_map>
#include <memory>

class CGeometryDataBase;

class CGrid {
public:
    // ���캯������ʼ�������С�͵�Ԫ���С
    CGrid(int width, int height, int cellSize);

    // ��Ӽ��ζ�������
    void AddGeometry(int id, std::shared_ptr<CGeometryDataBase> geom);

    // ��ȡλ��ָ������Ԫ�еļ��ζ���ID
    std::vector<int> GetGeometriesInCell(int x, int y) const;
     std::vector<std::vector<std::vector<int>>> m_grid; // �洢���ζ���ID������
private:
    int m_width;  // ������
    int m_height; // ����߶�
    int m_cellSize; // ��Ԫ���С
    
};
