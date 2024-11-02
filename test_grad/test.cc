/*
计算直线到椭圆的最短距离，1030-智驾大陆面试
椭圆的方程为x(t), y(t)的解析形式，t的范围是0～2pi。
此外点到直线的距离函数。
距离函数对t求导，等于距离函数对x求导乘x对t求导 + 距离函数对y求导乘y对t求导，再除以dist，使梯度缩放到合适的范围
*/
#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>

// 椭圆参数
const double a = 5.0; // 半长轴
const double b = 3.0; // 半短轴

// 直线方程 y = mx + c
double m = 1.0; // 斜率
double c = 10.0; // 截距
std::ofstream outputFile("gradient_descent_data.txt");
// 距离函数
double distanceFunction(double t) {
    double x = a * std::cos(t);
    double y = b * std::sin(t);
    return std::abs(m * x - y + c) / std::sqrt(m * m + 1);
}

// 计算梯度
double gradient(double t) {
    double x = a * std::cos(t);
    double y = b * std::sin(t);
    double dist = distanceFunction(t);
    
    // 计算偏导数
    double dDist_dX = m / std::sqrt(m * m + 1);
    double dDist_dY = -1.0 / std::sqrt(m * m + 1);
    
    double dx_dt = -a * std::sin(t);
    double dy_dt = b * std::cos(t); 
    double grad = (dDist_dX * dx_dt + dDist_dY * dy_dt) / dist;
    outputFile << t << "," << grad << "," << dist << "\n";
    return  grad;// 返回 t 的导数
}

// 梯度下降方法
double gradientDescent(double initialT, double learningRate, int maxIterations) {
    double t = initialT;
    for (int i = 0; i < maxIterations; ++i) {
        double grad = gradient(t);
        t -= learningRate * grad; // 更新 t
        std::cout << "grad: " << grad << ", t: " << t << std::endl;
        // 限制 t 的范围在 [0, 2π]
        if (t < 0) t += 2 * M_PI;
        if (t > 2 * M_PI) t -= 2 * M_PI;
    }

    return t;
}

// 主函数
int main() {
    double initialT = 3.0; // 初始 t 值
    double learningRate = 0.01;
    int maxIterations = 1000;
    outputFile << "t,grad,distance\n"; // CSV 格式的表头
    double optimalT = gradientDescent(initialT, learningRate, maxIterations);
    double minDistance = distanceFunction(optimalT);

    std::cout << "最短距离: " << minDistance << "，在 t = " << optimalT << " 时取得。" << "x = " << a * std::cos(optimalT) << "y = " << b * std::sin(optimalT) << std::endl;

    return 0;
}
