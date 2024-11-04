#include <vector>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
double maxProbability(int n, vector<vector<int>>& edges,
    vector<double>& succProb, int start_node,
    int end_node) {
    vector<vector<pair<double, int>>> graph(n);
    int sz = edges.size();
    for (int i = 0; i < sz; ++i) {
        graph[edges[i][0]].emplace_back(succProb[i], edges[i][1]);
        graph[edges[i][1]].emplace_back(succProb[i], edges[i][0]);
    }
    priority_queue<pair<double, int>> pq;
    vector<double> prob(n, 0);
    prob[start_node] = 1;
    pq.emplace(1, start_node);
    while (!pq.empty()) {
        auto [pr, node] = pq.top();
        pq.pop();
        if (pr < prob[node])
            continue;
        for (auto& [pr_next, node_next] : graph[node]) {
            if (prob[node_next] < pr_next * prob[node]) {
                prob[node_next] = pr_next * prob[node];
                pq.emplace(make_pair(prob[node_next], node_next));
            }
        }
    }
    return prob[end_node];
}

int main() {
    vector<vector<int>> edges{{0, 1}, {1, 2}, {0, 2}, {2, 3}, {1, 3}};
    vector<double> succ_prob{0.2, 0.3, 0.4, 0.2, 0.3};
    double res = maxProbability(4, edges, succ_prob, 0, 3);
    std::cout << res << std::endl;
}