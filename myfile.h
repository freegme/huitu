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
    // ��ȡ�ļ�����
    bool ReadFile(const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            std::cerr << "Error: Failed to open file." << std::endl;
            return false;
        }
        int n = 1;//����ʶ��id����������괮
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

            // ��������־
            if (x == -999999.0 && y == -999999.0) {
                break;
            }

            // ����µļ��ζ���ʼ��־
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
       points.emplace_back(static_cast<int>(x * 5+500), static_cast<int>(y * 5 + 300));//ʵ������ķŴ���
            }
            // ��ȡ���ζ������
            if (n == 2)
            {
                currentCode = static_cast<int>(x);
                n++;
            }
            // ��ȡ���ζ���ID
            if (n == 1)
            {
                currentId = static_cast<int>(x);
                n++;
            }
            
         
            //// ��ȡ���ζ���ID�ʹ���
            //if (points.empty()) {
            //    currentId = static_cast<int>(x);
            //    currentCode = static_cast<int>(y);
            //}
            //else {
            //    // ��ӵ㵽��ǰ���ζ���
            //    points.emplace_back(static_cast<int>(x * 100), static_cast<int>(y * 100));
            //}
        }

        // ���һ�����ζ���
        
        inFile.close();
        return true;
    }

    // �������м��ζ���
    void DrawAllGeometries(CDC* pDC) const {
        for (const auto& geom : geometries) {
            geom->Draw(pDC);
        }
    }
 // �洢���ζ���ļ���
    std::vector<std::shared_ptr<CGeometryDataBase>> geometries;
private:
    // ��Ӽ��ζ��󵽼�����
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

