/*
计算直线到椭圆的最短距离，1030-智驾大陆面试
椭圆的方程为x(t), y(t)的解析形式，t的范围是0～2pi。
此外点到直线的距离函数。
距离函数对t求导，等于距离函数对x求导乘x对t求导 +
距离函数对y求导乘y对t求导，再除以dist，使梯度缩放到合适的范围
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include "../utils/time.h"

// 椭圆参数
const double a = 5.0; // 半长轴
const double b = 3.0; // 半短轴

// 直线方程 y = mx + c
double m = 1.0;  // 斜率
double c = 10.0; // 截距

// Wolfe 条件参数
const double c1 = 1e-4; // Armijo 参数
const double c2 = 0.9;  // Curvature 参数
const double step_reduction = 0.5; // 每次不满足条件时步长减少为原来的 0.5 倍
const double initial_alpha = 1.0; // 初始步长

std::ofstream outputFile("gradient_descent_data.txt");
// 距离函数
double distanceFunction(double t) {
  double x = a * std::cos(t);
  double y = b * std::sin(t);
  return std::pow((m * x - y + c), 2) / (m * m + 1);
}

// 计算梯度
double gradient(double t) {
  double x = a * std::cos(t);
  double y = b * std::sin(t);
  double dist = distanceFunction(t);

  // 计算偏导数
  double dDist_dX = (2 * m * (m * x - y + c)) / (m * m + 1);
  double dDist_dY = (2 * (-1) * (m * x - y + c)) / (m * m + 1);

  double dx_dt = -a * std::sin(t);
  double dy_dt = b * std::cos(t);
  double grad = (dDist_dX * dx_dt + dDist_dY * dy_dt) / dist;
  //   outputFile << t << "," << grad << "," << dist << "\n";
  return grad; // 返回 t 的导数
}

double hessian(double t) {
  double x = a * std::cos(t);
  double y = b * std::sin(t);

  // 计算一阶导数
  double dDist_dX = (2 * m * (m * x - y + c)) / (m * m + 1);
  double dDist_dY = (2 * (-1) * (m * x - y + c)) / (m * m + 1);

  // 计算对 t 的一阶导数
  double dx_dt = -a * std::sin(t);
  double dy_dt = b * std::cos(t);

  // 计算二阶导数
  double d2Dist_dX2 = (2 * m * m) / (m * m + 1);
  double d2Dist_dY2 = -2 / (m * m + 1);
  double dist = distanceFunction(t);
  // 计算 Hessian
  double hessianValue =
      (d2Dist_dX2 * (dx_dt * dx_dt) + d2Dist_dY2 * (dy_dt * dy_dt)) / dist;

  return hessianValue; // 返回 Hessian
}

// 梯度下降方法
double gradientDescent(double initialT, double learningRate,
                       int maxIterations) {
  double t = initialT;
  outputFile << "t,grad,distance\n"; // CSV 格式的表头
  for (int i = 0; i < maxIterations; ++i) {
    double grad = gradient(t);
    t -= learningRate * grad; // 更新 t
    std::cout << "grad: " << grad << ", t: " << t << std::endl;
    // 限制 t 的范围在 [0, 2π]
    while (t < 0)
      t += 2 * M_PI;
    while (t > 2 * M_PI)
      t -= 2 * M_PI;
  }

  return t;
}

// 使用 Wolfe 条件调整步长
double wolfeStep(double t, double grad, double hess) {
  double alpha = initial_alpha;
  double currentDistSquared = distanceFunction(t);

  // 牛顿更新的方向
  double newtonStep = -grad / hess;
  bool brackt = false;
  // Wolfe 条件循环：调整步长 alpha 直到满足 Armijo 和 Curvature 条件
  while (true) {
    double newDistSquared = distanceFunction(t + alpha * newtonStep);
    double newGrad = gradient(t + alpha * newtonStep);

    // 检查 Armijo 条件
    if (newDistSquared > currentDistSquared + c1 * alpha * grad * newtonStep) {
      std::cout << "not satisfy armijo condition, newDistSquared: "
                << newDistSquared
                << ", currentDistSquared: " << currentDistSquared
                << ", alpha: " << alpha << std::endl;
      brackt = true;
    }
    // 检查 Curvature 条件
    else if (std::abs(newGrad) < c2 * std::abs(grad)) {
      std::cout << "not satisfy Curvature condition, new grad: " << newGrad
                << ", grad: " << grad << ", alpha: " << alpha << std::endl;
      brackt = false;
    } else {
      std::cout << "both satisfy armijo condition and wolfe, step: " << alpha
                << std::endl;
      break; // 两个条件都满足
    }
    if (brackt) {
      alpha *= step_reduction;
    } else {
      alpha *= 1.5;
    }
  }
  std::cout << "return alpha: " << alpha << std::endl;
  return alpha;
}

// 牛顿法
double newtonMethod(double initialT, double learningRate, int maxIterations,
                    double alpha, bool is_newton) {
  std::ofstream outputFile("gradient_descent_data.txt", std::ios::app);
  outputFile << "t,grad,distance,hessian\n"; // CSV 格式的表头

  double t = initialT;
  double gradThreshold = 1e-6;        // 梯度阈值
  double hessianThreshold = 1e-6;     // 梯度阈值
  double paramChangeThreshold = 1e-6; // 参数变化阈值
  double disChangeThreshold = 1e-3;   // 参数变化阈值
  for (int i = 0; i < maxIterations; ++i) {
    double dis = distanceFunction(t);
    double grad = gradient(t);
    double hess = hessian(t);
    // 防止 Hessian 为零的情况
    if (std::abs(hess) < 1e-8) {
      std::cout << "Hessian is too small" << std::endl;
      hess += hessianThreshold;
    }
    if (hess < 0) {
      hess = alpha / learningRate;
    }
    // double t_new = t - alpha * grad / hess;
    double step = wolfeStep(t, grad, hess);
    double t_new = t - step * grad / hess;
    // 限制 t 的范围在 [0, 2π]
    while (t_new < 0)
      t_new += 2 * M_PI;
    while (t_new > 2 * M_PI)
      t_new -= 2 * M_PI;
    double dis_new = distanceFunction(t_new);
    std::cout << "iter:" << i << ", t: " << t << ", t_new: " << t_new
              << ", dis: " << dis << ", dist_new: " << dis_new << std::endl;
    if (std::abs(grad) < gradThreshold ||
        std::abs(t_new - t) < paramChangeThreshold ||
        std::abs(dis_new - dis) < disChangeThreshold) {
      std::cout << "iter:" << i << ", Convergence reached." << std::endl;
      break;
    }
    t = t_new;
    // 保存数据到文件
    outputFile << t << "," << grad << "," << dis << "," << hess << "\n";
  }
  outputFile.close();
  return t;
}

// 主函数
int main() {
  double initialT = 5.0; // 初始 t 值
  double learningRate = 0.01;
  int maxIterations = 1000;
  bool test_newton = true;
  double alpha = 0.3;
  utils::Timer<true>newton_timer("Newton Method");
  newton_timer.Tic();
  double optimalT =
      newtonMethod(initialT, learningRate, maxIterations, alpha, test_newton);
  newton_timer.Toc();
  double minDistance = std::sqrt(distanceFunction(optimalT));
  std::cout << "最短距离: " << minDistance << "，在 t = " << optimalT
            << " 时取得。"
            << "x = " << a * std::cos(optimalT)
            << ", y = " << b * std::sin(optimalT) << std::endl;
  return 0;
}
