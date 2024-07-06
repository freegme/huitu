#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <afxwin.h> // For CDC, CPoint
#include"mypoint.h"
#include"myline.h"
#include"mypolygon.h"
#include"CPointF.h"
class myfile
{
public:
    myfile(){};
    // 读取文件内容
    bool ReadFile(const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            std::cerr << "Error: Failed to open file." << std::endl;
            return false;
        }
        int n = 1;//用于识别id、编码和坐标串
        std::string line;
        int currentId = -1;
        int currentCode = -1;
        std::vector<CPointF> points;

        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            double x, y;
            char comma;

            if (!(iss >> x >> comma >> y) || comma != ',') {
                continue;
            }

            // 检查结束标志
            if (x == -999999.0 && y == -999999.0) {
                break;
            }

            // 检查新的几何对象开始标志
            if (x == -666666.0 && y == -666666.0) {
                if (!points.empty()) {
                    AddGeometry(currentId, currentCode, points);
                    points.clear();
                    n = 1;
                }
                continue;
            }
   if (n == 3)
            {
       points.emplace_back(static_cast<int>(x * 5+500), static_cast<int>(y * 5 + 300));//实现坐标的放大倍数
            }
            // 读取几何对象代码
            if (n == 2)
            {
                currentCode = static_cast<int>(x);
                n++;
            }
            // 读取几何对象ID
            if (n == 1)
            {
                currentId = static_cast<int>(x);
                n++;
            }
            
         
            //// 读取几何对象ID和代码
            //if (points.empty()) {
            //    currentId = static_cast<int>(x);
            //    currentCode = static_cast<int>(y);
            //}
            //else {
            //    // 添加点到当前几何对象
            //    points.emplace_back(static_cast<int>(x * 100), static_cast<int>(y * 100));
            //}
        }

        // 最后一个几何对象
        
        inFile.close();
        return true;
    }

    // 绘制所有几何对象
    void DrawAllGeometries(CDC* pDC) const {
        for (const auto& geom : geometries) {
            geom->Draw(pDC);
        }
    }
 // 存储几何对象的集合
    std::vector<std::shared_ptr<CGeometryDataBase>> geometries;
private:
    // 添加几何对象到集合中
    void AddGeometry(int id, int code, const std::vector<CPointF>& points) {
        int type = code / 10000;
        if (type == 3) {
            geometries.push_back(std::make_shared<mypoint>(id, code, points));
        }
        else if (type == 1) {
            geometries.push_back(std::make_shared<myline>(id, code, points));
        }
        else if (type == 2) {
            geometries.push_back(std::make_shared<mypolygon>(id, code, points));
        }
    }

   
};

