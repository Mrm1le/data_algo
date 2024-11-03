import numpy as np
import matplotlib.pyplot as plt
import os
# 获取当前目录

# 椭圆参数
a = 5  # 半长轴
b = 3  # 半短轴

# 直线方程 y = mx + c
m = 1  # 斜率
c = 10  # 截距

# 生成椭圆点
theta = np.linspace(0, 2 * np.pi, 100)
ellipse_x = a * np.cos(theta)
ellipse_y = b * np.sin(theta)

# 直线点
line_x = np.array([-20, 20])
line_y = m * line_x + c

# 绘制图形
plt.figure(figsize=(8, 6))
plt.plot(ellipse_x, ellipse_y, label='椭圆', color='blue')
plt.plot(line_x, line_y, label='直线', color='red')

# 设置图形属性
plt.xlabel("X")
plt.ylabel("Y")
plt.title("椭圆与直线")
plt.axhline(0, color='black', linewidth=0.5, ls='--')
plt.axvline(0, color='black', linewidth=0.5, ls='--')
plt.axis('equal')
plt.grid(True)
plt.legend()

# 保存图形
plt.savefig("ellipse_line.png")
plt.show()


# 读取数据
data = np.loadtxt("gradient_descent_data.txt", delimiter=",", skiprows=1)

# 提取列
t = data[:, 0]
grad = data[:, 1]
distance = data[:, 2]
hessian = data[:, 3]

# 绘制图形
plt.figure(figsize=(12, 6))

# 绘制 t vs distance
plt.subplot(1, 3, 1)
plt.plot(t, distance, label='dist', color='blue')
plt.title("t vs Distance")
plt.xlabel("t")
plt.ylabel("Distance")
plt.grid()
plt.legend()

# 绘制迭代次数 vs grad
plt.subplot(1, 3, 2)
plt.plot(np.arange(len(grad)), grad, label='grad', color='red')
plt.plot(np.arange(len(grad)), t, label='t', color='k')
plt.title("Iteration vs Gradient")
plt.xlabel("Iteration")
plt.ylabel("Gradient")
plt.grid()
plt.legend()

# 绘制迭代次数 vs hessian
plt.subplot(1, 3, 3)
plt.plot(np.arange(len(hessian)), hessian, label='hess', color='red')
plt.plot(np.arange(len(hessian)), t, label='t', color='k')
plt.title("Iteration vs Hessian")
plt.xlabel("Iteration")
plt.ylabel("Hessian")
plt.grid()
plt.legend()
# 显示图形
plt.tight_layout()
plt.savefig("gradient_descent_results.png")
plt.show()
