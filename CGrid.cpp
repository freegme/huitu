// CGrid.cpp
#include"pch.h"
#include "CGrid.h"
#include "CGeometryDataBase.h"
#include <algorithm>
#include <unordered_map>
#include <memory>

// 构造函数：初始化网格大小和单元格大小
CGrid::CGrid(int width, int height, int cellSize)
    : m_width(width), m_height(height), m_cellSize(cellSize) {
    // 计算行和列的数量
    int rows = (height + cellSize - 1) / cellSize;
    int cols = (width + cellSize - 1) / cellSize;
    // 初始化网格
    m_grid.resize(rows, std::vector<std::vector<int>>(cols));
}

// 将几何对象添加到网格中
void CGrid::AddGeometry(int id, std::shared_ptr<CGeometryDataBase> geom) {
    // 获取几何对象的包围盒
    int xMin, yMin, xMax, yMax;
    geom->GetBoundingBox(xMin, yMin, xMax, yMax);

    // 计算几何对象覆盖的网格单元范围
    int rowStart =max(0, yMin / m_cellSize);
    int rowEnd = min((m_height - 1) / m_cellSize, yMax / m_cellSize);
    int colStart = max(0, xMin / m_cellSize);
    int colEnd = min((m_width - 1) / m_cellSize, xMax / m_cellSize);

    // 将几何对象ID添加到相应的网格单元中
    for (int row = rowStart; row <= rowEnd; ++row) {
        for (int col = colStart; col <= colEnd; ++col) {
            m_grid[row][col].push_back(id);
        }
    }
}

// 获取位于指定网格单元中的几何对象ID
std::vector<int> CGrid::GetGeometriesInCell(int x, int y) const {
    int row = y / m_cellSize;
    int col = x / m_cellSize;

    if (row >= 0 && row < m_grid.size() && col >= 0 && col < m_grid[row].size()) {
        return m_grid[row][col];
    }
    return {};
}