#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <sstream>
#include <string>
#include <stdexcept>

void feedMartrix(Eigen::MatrixXd& A, const std::string file_name){
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
    double result = C.block<6, 1>(0, 0).dot(T.block<6, 1>(0, 0).transpose());
    Eigen::VectorXd dot_T(6); 
    dot_T << 0, 1, 2*T(0, 1), 3*T(0, 1)*T(0, 1), 4*T(0, 1)*T(0, 1)*T(0, 1), 5*T(0, 1)*T(0, 1)*T(0, 1)*T(0, 1);
    double result2 = C.block<6, 1>(0, 0).dot(dot_T);
    std::cout << "T(0, 1)" << T(0, 1) << std::endl;
    std::cout << "result: " << result << std::endl;
    std::cout << "result2: " << result2 << std::endl;
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
