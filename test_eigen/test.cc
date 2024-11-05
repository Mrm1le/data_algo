#include "Eigen/Dense"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void feedMartrix(Eigen::MatrixXd &A, const std::string file_name) {
  std::ifstream file(file_name);
  std::string line;
  int row = 0;
  // 逐行读取文件内容
  while (std::getline(file, line) && row < A.rows()) {
    std::istringstream ss(line);
    double value;
    int col = 0;
    // 逐个读取值，自动跳过多余空格
    while (ss >> value && col < A.cols()) {
      A(row, col) = value;
      col++;
    }
    row++;
  }
  file.close();
}
int main() {
  // 定义60x60的Eigen矩阵
  Eigen::MatrixXd A(60, 60);
  Eigen::MatrixXd B(60, 2);
  Eigen::MatrixXd C(60, 2);
  Eigen::MatrixXd T(60, 6);

  feedMartrix(A, "df_A_martrix.txt");
  feedMartrix(B, "df_b_martrix.txt");
  feedMartrix(C, "df_c_martrix.txt");
  feedMartrix(T, "df_t_vec.txt");
  Eigen::Matrix<double, 6, 1> t0;
  Eigen::Matrix<double, 6, 1> t1;
  Eigen::Matrix<double, 6, 1> tInv;
  t0 << 1, 0, 0, 0, 0, 0;
  t1 = T.block<6, 1>(0, 0).transpose();
  // t = T.block<6, 1>(0, 0);
  tInv = t1.cwiseInverse();
  Eigen::Matrix<double, 6, 1> beta0 = Eigen::Matrix<double, 6, 1>::Zero();
  Eigen::Matrix<double, 6, 1> beta1 = Eigen::Matrix<double, 6, 1>::Zero();
  Eigen::Matrix<double, 6, 1> beta2 = Eigen::Matrix<double, 6, 1>::Zero();
  Eigen::Matrix<double, 6, 1> beta3 = Eigen::Matrix<double, 6, 1>::Zero();
  Eigen::Matrix<double, 6, 1> beta4 = Eigen::Matrix<double, 6, 1>::Zero();
  Eigen::Matrix<double, 6, 1> beta5 = Eigen::Matrix<double, 6, 1>::Zero();
  const double s1 = 0;
  const double s2 = s1 * s1;
  const double s3 = s2 * s1;
  const double s4 = s2 * s2;
  const double s5 = s4 * s1;
  beta0 = t0;
  beta1(1, 0) = 1.0;
  beta1(2, 0) = 2.0 * s1;
  beta1(3, 0) = 3.0 * s2;
  beta1(4, 0) = 4.0 * s3;
  beta1(5, 0) = 5.0 * s4;
  beta2(2, 0) = 2.0;
  beta2(3, 0) = 6.0 * s1;
  beta2(4, 0) = 12.0 * s2;
  beta2(5, 0) = 20.0 * s3;
  beta3(3, 0) = 6.0;
  beta3(4, 0) = 24 * s1;
  beta3(5, 0) = 60 * s2;
  beta4(4, 0) = 24.0;
  beta4(5, 0) = 120 * s1;
  beta5(5, 0) = 120;
  double sigma =
      C.block<6, 1>(6, 0).dot(beta0); // c0 = sigma0 c * beta0 = sigma1
  double dsigma = C.block<6, 1>(6, 0).dot(beta1);   // c1 = dsigma0
  double ddsigma = C.block<6, 1>(6, 0).dot(beta2);  // c2 * 2 = ddsigma0
  double dddsigma = C.block<6, 1>(6, 0).dot(beta3); // c3 * 6 = dddsigma0
  double ddddsigma = C.block<6, 1>(6, 0).dot(beta4);
  double dddddsigma = C.block<6, 1>(6, 0).dot(beta5);
  std::cout << "T(0, 1)" << T(0, 1) << std::endl;
  std::cout << "beta1 " << beta1.transpose() << std::endl;
  std::cout << "tInv " << tInv.transpose() << std::endl;
  std::cout << "sigma: " << sigma << std::endl;
  std::cout << "dsigma: " << dsigma << std::endl;
  std::cout << "ddsigma: " << ddsigma / 2 << std::endl;
  std::cout << "dddsigma: " << dddsigma / 6 << std::endl;
  std::cout << "ddddsigma: " << ddddsigma / 24 << std::endl;
  std::cout << "dddddsigma: " << dddddsigma / 120 << std::endl;
  return 0;
}