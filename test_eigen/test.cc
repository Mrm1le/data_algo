#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <sstream>
#include <string>
#include <stdexcept>

int main() {
    // 定义60x60的Eigen矩阵
    Eigen::MatrixXd A(60, 60);
    Eigen::MatrixXd B(60, 2);
    Eigen::MatrixXd C(60, 2);
    Eigen::MatrixXd T(60, 6);
    // 打开txt文件
    std::ifstream file("df_A_martrix.txt");
    std::string line;
    int row = 0;
    // 逐行读取文件内容
    while (std::getline(file, line) && row < 60) {
        std::istringstream ss(line);
        double value;
        int col = 0;
        // 逐个读取值，自动跳过多余空格
        while (ss >> value && col < 60) {
            A(row, col) = value;
            col++;
        }
        row++;
    }
    file.close();

    // 打开txt文件
    std::ifstream file2("df_b_martrix.txt");
    row = 0;
    // 逐行读取文件内容
    while (std::getline(file2, line) && row < 60) {
        std::istringstream ss(line);
        double value;
        int col = 0;
        // 逐个读取值，自动跳过多余空格
        while (ss >> value && col < 2) {
            B(row, col) = value;
            col++;
        }
        row++;
    }
    file2.close();
    // 打开txt文件
    std::ifstream file3("df_c_martrix.txt");
    row = 0;
    // 逐行读取文件内容
    while (std::getline(file3, line) && row < 60) {
        std::istringstream ss(line);
        double value;
        int col = 0;
        // 逐个读取值，自动跳过多余空格
        while (ss >> value && col < 2) {
            C(row, col) = value;
            col++;
        }
        row++;
    }
    file3.close();

    std::ifstream file4("df_t_vec.txt");
    row = 0;
    // 逐行读取文件内容
    while (std::getline(file4, line) && row < 60) {
        std::istringstream ss(line);
        double value;
        int col = 0;
        // 逐个读取值，自动跳过多余空格
        while (ss >> value && col < 6) {
            T(row, col) = value;
            col++;
        }
        row++;
    }
    file4.close();

    double result = C.block<6, 1>(6, 0).dot(T.block<6, 1>(0, 0).transpose());
    std::cout << "result: " << result << std::endl;
    return 0;


}

// c:
//                                  22.6601                                 23.7754
//                                  4.95331                                 -3.3867
//                                 -2.24087                                 1.36541
//                                  2.33686                               -0.861707
//                                 -0.90048                              -0.0509022
//                                 0.125223                               0.0935533

// b:

//                                  22.6601                                 23.7754
//                                  4.95331                                 -3.3867
//                                 -4.48175                                 2.73082
//                                        0                                       0
//                                        0                                       0
//                                  26.9341                                  20.935

// T 
//                   1             12.0008              144.02             1728.36             20741.7              248918
