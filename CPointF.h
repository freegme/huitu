#pragma once
class CPointF
{
public:
    CPointF() : x(0.0), y(0.0) {}
    CPointF(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};

