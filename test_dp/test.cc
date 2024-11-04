class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1);
        dp[0] = true;
        // 每个位置为结尾，能否连接上单词
        for (int j = 1; j <= n; j++) {
            for (string & t : wordDict) {
                int len = t.size();
                int i = j - len + 1;
                // 这里的i表示含义比较多
                if (i > 0 && dp[i - 1] && s.substr(i - 1, len) == t) {
                    dp[j] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};


class Solution {
public:
    int numSquares(int n) {
        // 求最小值，则初始化最大或无穷大
        vector<int> dp(n + 1, INT_MAX / 2);
        // 0个数，容纳0个空间
        dp[0] = 0;
        // 遍历物品 (完全平方数)
        for (int i = 1; i * i <= n; i++) {
            int num = i * i;
            // 完全背包
            for (int j = num; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - num] + 1);
            }
        }

        return dp[n];
    }
};

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 定义最少需要数量，初始无穷个
        vector<int> dp(amount+1, INT_MAX);
        // 0空间放0个
        dp[0] = 0;
        // for (int x : coins) {
        for (int i = 0; i <= amount; ++i){
            // 完全背包
            for(auto &coin : coins){
                if(i - coin < 0)
                    continue;
                dp[i] = min(dp[i-coin] + 1, dp[i]);
            }
            for (int j = x; j <= amount; j++) {
                // 已经利用过才能转化，保证空间完全利用
                if (dp[j - x] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - x] + 1);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};