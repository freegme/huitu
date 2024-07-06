// CGrid.h
#pragma once
#include"pch.h"
#include <vector>
#include <unordered_map>
#include <memory>

class CGeometryDataBase;

class CGrid {
public:
    // 构造函数：初始化网格大小和单元格大小
    CGrid(int width, int height, int cellSize);

    // 添加几何对象到网格
    void AddGeometry(int id, std::shared_ptr<CGeometryDataBase> geom);

    // 获取位于指定网格单元中的几何对象ID
    std::vector<int> GetGeometriesInCell(int x, int y) const;
     std::vector<std::vector<std::vector<int>>> m_grid; // 存储几何对象ID的网格
private:
    int m_width;  // 网格宽度
    int m_height; // 网格高度
    int m_cellSize; // 单元格大小
    
};
