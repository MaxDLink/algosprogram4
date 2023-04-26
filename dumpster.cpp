//this is a file for brainstorming code 

#include <vector>
#include <algorithm>
using namespace std;

pair<vector<float>, vector<int>> WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size() - 1;
    vector<vector<float>> dp(j+1, vector<float>(j+1, 0));
    vector<int> quit(j, 0);

    for (int i = j; i >= s; i--) {
        dp[i][j] = *max_element(w.begin()+s, w.begin()+t+1);
    }

    for (int i = j-1; i >= 0; i--) {
        for (int j = i+1; j >= s; j--) {
            dp[i][j] = p[i] * dp[i+1][j+1] + (1 - p[i]) * *max_element(w.begin()+s, w.begin()+t+1);
        }

        for (int j = s-1; j >= 0; j--) {
            dp[i][j] = p[i] * dp[i+1][j+1] + (1 - p[i]) * 0;
        }

        quit[i] = (dp[0][i+1] >= *max_element(dp[0].begin()+i+2, dp[0].begin()+j+1)) ? 1 : 0;
    }

    return make_pair(dp[0], quit);
}

pair<vector<vector<float>>, vector<vector<int>>> WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    int n = w.size(); // number of questions

    vector<vector<float>> a(2, vector<float>(n)); // expected amount of money won
    vector<vector<int>> b(2, vector<int>(n)); // decision to quit or answer

    // initialize values for the last question
    a[0][n-1] = w[n-1];
    a[1][n-1] = w[n-1] * (p[n-1] + 0.5) + (1 - w[n-1]) * w[n-1]; // probability of correct answer is at least 0.5
    b[0][n-1] = 0;
    b[1][n-1] = 0;

    for (int i = n-2; i >= 0; i--) {
        // expected amount of money won without using lifeline
        a[0][i] = w[i] * (a[0][i+1] + p[i] * (t-s+1)) + (1 - w[i]) * a[0][i+1];

        // expected amount of money won with using lifeline
        float p_lifeline = min(p[i] * 0.5 + 0.5, 0.999f); // new probability cannot exceed 0.999
        a[1][i] = w[i] * (a[1][i+1] + p_lifeline * (t-s+1)) + (1 - w[i]) * (a[1][i+1] + w[i]);
        
        // decision to quit or answer without using lifeline
        if (w[i] * (p[i] * (t-s+1) + a[0][i+1]) + (1 - w[i]) * a[0][i+1] >= w[i] * w[i]) {
            b[0][i] = 1;
        } else {
            b[0][i] = 0;
        }
        
        // decision to quit, continue without lifeline, or continue with lifeline
        if (w[i] * (p[i] * (t-s+1) + a[1][i+1]) + (1 - w[i]) * (w[i] + a[1][i+1]) >= max(w[i] * w[i], w[i] * (p[i] + 0.5) * (t-s+1) + (1 - w[i]) * w[i])) {
            b[1][i] = 1;
        } else if (w[i] * (p[i] * (t-s+1) + a[0][i+1]) + (1 - w[i]) * a[0][i+1] >= w[i] * w[i]) {
            b[1][i] = 2;
        } else {
            b[1][i] = 0;
        }
    }

    return make_pair(a, b);
}
pair<vector<vector<float>>, vector<vector<int>>> WWWWW_2(vector<float> w, vector<float> p, int s, int t) {
    int n = p.size();
    vector<vector<float>> a(4, vector<float>(n + 1));
    vector<vector<int>> b(4, vector<int>(n));
    // No lifeline available
    a[0][0] = s;
    for (int i = 1; i <= n; i++) {
        a[0][i] = a[0][i - 1] + w[i - 1] * p[i - 1];
    }
    // Only "get easier" lifeline available
    a[1][0] = s;
    for (int i = 1; i <= n; i++) {
        a[1][i] = max(a[1][i - 1] + w[i - 1] * p[i - 1], a[0][i - 1] + (w[i - 1] * (0.5 + p[i - 1] / 2)));
        if (a[1][i] < a[1][i - 1] + w[i - 1] * p[i - 1]) {
            b[1][i - 1] = 2; // Use the "get easier" lifeline
        } else {
            b[1][i - 1] = 1; // Don't use the lifeline
        }
        a[1][i] = max(a[1][i], a[1][i - 1] + w[i - 1] * p[i - 1]); // Don't answer the current question
    }
    // Only "get through" lifeline available
    a[2][0] = s;
    for (int i = 1; i <= n; i++) {
        a[2][i] = max(a[2][i - 1] + w[i - 1] * p[i - 1], a[0][i - 1] + w[i - 1]);
        if (i > 1) {
            a[2][i] = max(a[2][i], a[3][i - 2] + w[i - 2] * (1 - p[i - 2]) * (1 - p[i - 1]) * (10 * (i - 2)));
        }
        if (a[2][i] < a[2][i - 1] + w[i - 1] * p[i - 1]) {
            b[2][i - 1] = 3; // Use the "get through" lifeline
        } else {
            b[2][i - 1] = 1; // Don't use the lifeline
        }
        a[2][i] = max(a[2][i], a[2][i - 1] + w[i - 1] * p[i - 1]); // Don't answer the current question
    }
    // Both lifelines available
    a[3][0] = s;
    for (int i = 1; i <= n; i++) {
        a[3][i] = max(a[3][i - 1] + w[i - 1] * p[i - 1], a[0][i
