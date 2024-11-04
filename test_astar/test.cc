#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

// 定义方向：上、下、左、右
const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct Node {
    int x, y, cost, estimate;
    Node(int x, int y, int cost, int estimate) : x(x), y(y), cost(cost), estimate(estimate) {}
    
    // A* 算法的优先队列比较函数
    bool operator<(const Node& other) const {
        return (cost + estimate) > (other.cost + other.estimate);
    }
};

// 曼哈顿距离，作为 A* 的启发式函数
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* 算法找到从起点 (startX, startY) 到最近垃圾点的最短路径
vector<pair<int, int>> a_star(vector<vector<int>>& map, int startX, int startY, int& trashX, int& trashY) {
    int rows = map.size();
    int cols = map[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    priority_queue<Node> pq;
    pq.push(Node(startX, startY, 0, 0));

    // 记录路径
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int x = current.x, y = current.y;

        if (visited[x][y]) continue;
        visited[x][y] = true;

        // 如果找到垃圾
        if (map[x][y] == 2) {
            trashX = x;
            trashY = y;
            
            // 构建路径
            vector<pair<int, int>> path;
            while (!(x == startX && y == startY)) {
                path.push_back({x, y});
                std::tie(x, y) = parent[x][y];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // 探索邻居节点
        for (int i = 0; i < 4; ++i) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];

            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && !visited[nx][ny] && map[nx][ny] != 1) {
                parent[nx][ny] = {x, y};
                int newCost = current.cost + 1;
                int estimate = heuristic(nx, ny, trashX, trashY);
                pq.push(Node(nx, ny, newCost, estimate));
            }
        }
    }

    // 未找到垃圾，返回空路径
    return {};
}

// 清扫所有垃圾的主函数
vector<pair<int, int>> clean_all_trash(vector<vector<int>>& map, int startX, int startY) {
    vector<pair<int, int>> total_path;
    int currentX = startX, currentY = startY;

    while (true) {
        int trashX = -1, trashY = -1;

        // 找到最近的垃圾
        vector<pair<int, int>> path = a_star(map, currentX, currentY, trashX, trashY);
        
        if (trashX == -1 && trashY == -1) { // 没有找到垃圾，清扫完成
            break;
        }

        // 清扫垃圾并更新地图
        map[trashX][trashY] = 0;

        // 记录路径并更新当前位置
        total_path.insert(total_path.end(), path.begin(), path.end());
        currentX = trashX;
        currentY = trashY;
    }

    return total_path;
}

int main() {
    // 初始化地图
    vector<vector<int>> map = {
        {0, 0, 1, 0, 2},
        {0, 1, 0, 0, 1},
        {0, 0, 0, 2, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };

    // 随机的起始位置
    int startX = 0, startY = 0;

    // 清扫所有垃圾
    vector<pair<int, int>> total_path = clean_all_trash(map, startX, startY);

    // 输出路径
    cout << "清扫路径: ";
    for (auto& p : total_path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    return 0;
}
