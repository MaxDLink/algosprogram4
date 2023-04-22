#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

pair<vector<float>, vector<int>> WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size() - 1;
    vector<float> dp(j + 1);
    vector<int> decisions(j);
    dp[0] = 0;
    for (int i = 1; i <= j; i++) {
        float max_money = 0;
        int decision = 0;
        for (int k = 1; k <= i; k++) {
            float money;
            if (k >= t) money = w[k];
            else if (k >= s) money = w[s];
            else money = 0;
            money += p[k] * dp[i - k];
            if (money > max_money) {
                max_money = money;
                decision = k;
            }
        }
        dp[i] = max_money;
        decisions[i - 1] = (decision == i || max_money < dp[i - 1]);
    }
    return {dp, decisions};
}

pair<vector<vector<float>>, vector<vector<int>>> WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size() - 1;
    vector<vector<float>> dp(2, vector<float>(j + 1));
    vector<vector<int>> decisions(2, vector<int>(j));
    dp[0][0] = dp[1][0] = 0;
    for (int i = 1; i <= j; i++) {
        // no lifeline
        float max_money_0 = 0;
        int decision_0 = 0;
        for (int k = 1; k <= i; k++) {
            float money;
            if (k >= t) money = w[k];
            else if (k >= s) money = w[s];
            else money = 0;
            money += p[k] * dp[0][i - k];
            if (money > max_money_0) {
                max_money_0 = money;
                decision_0 = k;
            }
        }
        dp[0][i] = max_money_0;
        decisions[0][i - 1] = (decision_0 == i || max_money_0 < dp[0][i - 1]);

        // with lifeline
        float max_money_1 = 0;
        int decision_1 = 0;
        for (int k = 1; k <= i; k++) {
            float money;
            if (k >= t) money = w[k];
            else if (k >= s) money = w[s];
            else money = 0;
            float prob = min(0.5 + p[k] / 2, 0.999f);
            money += prob * dp[1][i - k] - (i - k) * w[i - k + 1] * 10;
            if (money > max_money_1) {
                max_money_1 = money;
                decision_1 = k;
            }
        }
        dp[1][i] = max_money_1;
        if (decision_1 == i || max_money_1 < dp[0][i]) decisions[1][i - 1] = 1;
        else if (max_money_1 < dp[1][i - 1]) decisions[1][i - 1] = 2;
