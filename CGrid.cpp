// CGrid.cpp
#include"pch.h"
#include "CGrid.h"
#include "CGeometryDataBase.h"
#include <algorithm>
#include <unordered_map>
#include <memory>

// ���캯������ʼ�������С�͵�Ԫ���С
CGrid::CGrid(int width, int height, int cellSize)
    : m_width(width), m_height(height), m_cellSize(cellSize) {
    // �����к��е�����
    int rows = (height + cellSize - 1) / cellSize;
    int cols = (width + cellSize - 1) / cellSize;
    // ��ʼ������
    m_grid.resize(rows, std::vector<std::vector<int>>(cols));
}

// �����ζ�����ӵ�������
void CGrid::AddGeometry(int id, std::shared_ptr<CGeometryDataBase> geom) {
    // ��ȡ���ζ���İ�Χ��
    int xMin, yMin, xMax, yMax;
    geom->GetBoundingBox(xMin, yMin, xMax, yMax);

    // ���㼸�ζ��󸲸ǵ�����Ԫ��Χ
    int rowStart =max(0, yMin / m_cellSize);
    int rowEnd = min((m_height - 1) / m_cellSize, yMax / m_cellSize);
    int colStart = max(0, xMin / m_cellSize);
    int colEnd = min((m_width - 1) / m_cellSize, xMax / m_cellSize);

    // �����ζ���ID��ӵ���Ӧ������Ԫ��
    for (int row = rowStart; row <= rowEnd; ++row) {
        for (int col = colStart; col <= colEnd; ++col) {
            m_grid[row][col].push_back(id);
        }
    }
}

// ��ȡλ��ָ������Ԫ�еļ��ζ���ID
std::vector<int> CGrid::GetGeometriesInCell(int x, int y) const {
    int row = y / m_cellSize;
    int col = x / m_cellSize;

    if (row >= 0 && row < m_grid.size() && col >= 0 && col < m_grid[row].size()) {
        return m_grid[row][col];
    }
    return {};
}