#include <vector>
// #include <bits/stdc++.h>


using namespace std;
//random values are stuffed into these functions so that output is printed. These values should be changed. 
//no late pass will be used for this assignment.
//driver program should be indexed at zero. He will fix this? 

std::pair<std::vector<float>, std::vector<int> > WWWWW(std::vector<float> w, std::vector<float> p, int s, int t)
{
    int j = w.size();
    std::vector<float> E(j, 0);
    std::vector<int> Q(j, 0);
    E[0] = w[0] * p[0];
    Q[0] = 0;
    for (int i = 1; i < j; i++) {
        float max_val = w[i];
        for (int k = 0; k < i; k++) {
            float val = w[k] + (1 - p[k]) * E[k];
            if (val > max_val) {
                max_val = val;
            }
        }
        E[i] = max_val;
        if (w[i] > max_val) {
            Q[i] = 1;
        }
    }
    return std::make_pair(E, Q);
}

pair<vector<vector<float> >, vector<vector<int> > > WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    if (w.size() != p.size()) {
        throw invalid_argument("Weight and profit vectors must have the same size.");
    }
    if (s < 0 || s > t || t >= w.size()) {
        throw out_of_range("Invalid range for selecting items from the knapsack.");
    }

    int n = w.size();
    float selected_items_weight = 0;

    vector<vector<float> > dp(n + 1, vector<float>(t + 1, 0));
    vector<vector<int> > path(n + 1, vector<int>(t + 1, -1));
    for (int i = 1; i <= n; i++) {
        for (int j = s; j <= t; j++) {
            if (j >= w[i - 1]) {
                float val = dp[i - 1][j - w[i - 1]] + p[i - 1];
                if (val > dp[i - 1][j]) {
                    dp[i][j] = val;
                    path[i][j] = i - 1;
                } else {
                    dp[i][j] = dp[i - 1][j];
                    path[i][j] = path[i - 1][j];
                }
            } else {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = path[i - 1][j];
            }
        }
    }

    vector<vector<float> > selected_items(2);
    vector<vector<int> > selected_indices(2);

    for (int k = 0; k <= 1; k++) {
        selected_items_weight = 0;  // initialize selected_items_weight to 0
        for (int i = s; i <= t; i++) {
            if (dp[n][i] > dp[n][selected_items_weight]) {
                selected_items_weight = i;
            }
        }

        vector<float> weights;
        vector<float> profits;
        vector<int> indices;

        for (int i = n; i >= 1; i--) {
            if (path[i][selected_items_weight] != -1 && dp[i][selected_items_weight] > dp[i-1][selected_items_weight]) {
                indices.push_back(i-1);
                weights.push_back(w[i-1]);
                profits.push_back(p[i-1]);
                selected_items_weight -= w[i-1];
            }
        }

        // Reverse the order of the vectors and add them to selected_items and selected_indices
        reverse(weights.begin(), weights.end());
        reverse(profits.begin(), profits.end());
        reverse(indices.begin(), indices.end());
        selected_items[k] = weights;
        selected_items[k] = profits;
        selected_indices[k] = indices;
    }

    return make_pair(selected_items, selected_indices);
}




pair< vector< vector<float> > ,vector< vector<int> > > WWWWW_2(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size();
    vector<vector<float> > a(4, vector<float>(j));
    vector<vector<int> > b(4, vector<int>(j-1));

    for (int i = 0; i < j; i++) {
        a[0][i] = i < s ? 0 : (i >= t ? w[t-1] : w[s-1]);
        a[1][i] = a[2][i] = a[3][i] = a[0][i];
    }

    for (int i = j-2; i >= 0; i--) {
        for (int k = 0; k < 4; k++) {
            float expected_val = p[i] * a[k][i+1] + (1-p[i]) * a[0][i];
            float expected_val_using_get_easier = (k == 1 || k == 3) ? p[i] * a[k-1][i+1] + (1-p[i]) * a[0][i] - i * 10 : 0;
            float expected_val_using_get_through = (k == 2 || k == 3) ? a[k-2][i+1] - i * 10 : 0;

            if (expected_val >= a[k][i]) {
                a[k][i] = expected_val;
                b[k][i] = 1;
            }

            if (k == 1 || k == 3) {
                if (expected_val_using_get_easier >= a[k][i]) {
                    a[k][i] = expected_val_using_get_easier;
                    b[k][i] = 2;
                }
            }

            if (k == 2 || k == 3) {
                if (expected_val_using_get_through >= a[k][i]) {
                    a[k][i] = expected_val_using_get_through;
                    b[k][i] = 3;
                }
            }
        }
    }

    return make_pair(a, b);
}

 
