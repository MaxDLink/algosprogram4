//this is a file for brainstorming code 

#include <vector>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

pair<vector<float>, vector<int> > WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size() - 1;
    vector<vector<float> > dp(j+1, vector<float>(j+1, 0));
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

pair<vector<vector<float> >, vector<vector<int> > > WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    int n = w.size(); // number of questions

    vector<vector<float> > a(2, vector<float>(n)); // expected amount of money won
    vector<vector<int> > b(2, vector<int>(n)); // decision to quit or answer

    // initialize values for the last question
    a[0][n-1] = w[n-1];
    a[1][n-1] = w[n-1] * (p[n-1] + 0.5) + (1 - w[n-1]) * w[n-1]; // probability of correct answer is at least 0.5
    b[0][n-1] = 0;
    b[1][n-1] = 0;

    for (int i = n-2; i >= 0; i--) {
        // expected amount of money won without using lifeline
        a[0][i] = w[i] * (a[0][i+1] + p[i] * (t-s+1)) + (1 - w[i]) * a[0][i+1];

        // expected amount of money won with using lifeline
        float p_lifeline = std::min(p[i] * 0.5f + 0.5f, 0.999f);        
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
pair< vector < vector<float> > ,vector < vector<int> > > WWWWW_2(vector<float> w, vector<float> p, int s, int t) {
    int n = w.size();
    vector< vector<float> > a(4, vector<float>(n+1));
    vector< vector<int> > b(4, vector<int>(n));
    for (int i = 0; i <= n; i++) {
        a[0][i] = s + w[i];
    }
    for (int j = 1; j <= n; j++) {
        float e = 0.0;
        for (int k = 0; k < j; k++) {
            e += p[k] * w[k] * pow(1-p[k], j-k-1);
        }
        for (int i = j; i <= n; i++) {
            float q = 1.0;
            for (int k = j-1; k < i-1; k++) {
                q *= 1.0 - p[k];
            }
            a[0][i] += w[j-1] * q * (1.0 - p[i-1]) * (e + s);
        }
    }
    for (int i = 1; i <= n; i++) {
        a[1][i] = a[0][i];
        b[1][i-1] = 1;
        if (i > 1) {
            a[1][i] -= w[i-2] * p[i-2] * s;
        }
        for (int j = i+1; j <= n; j++) {
            a[1][i] -= w[j-1] * p[j-2] * pow(1.0 - p[i-2], j-i) * s;
        }
    }
    for (int i = 1; i <= n; i++) {
        a[2][i] = a[0][i];
        b[2][i-1] = 1;
        for (int j = i+1; j <= n; j++) {
            a[2][i] -= w[j-1] * pow(1.0 - p[i-1], j-i) * s * pow(p[i-1], t) * (1.0 - p[j-1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        a[3][i] = a[1][i];
        b[3][i-1] = 2;
        for (int j = i+1; j <= n; j++) {
            a[3][i] = max(a[3][i], a[2][j] - w[j-1]*pow(1.0 - p[i-1], j-i)*s*v*10.0);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = (a[i][j+1] > a[i][j]) ? 1 : 0;
        }
    }
    return make_pair(a, b);
}
