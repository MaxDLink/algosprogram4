#include <vector>
#include <bits/stdc++.h>


using namespace std;
//random values are stuffed into these functions so that output is printed. These values should be changed. 
//no late pass will be used for this assignment.
//driver program should be indexed at zero. He will fix this? 

std::pair<std::vector<float>, std::vector<int>> WWWWW(std::vector<float> w, std::vector<float> p, int s, int t)
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

vector<vector<int>> WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    int n = w.size();
    float selected_items_weight = 0;

    vector<vector<float>> dp(n + 1, vector<float>(t + 1, 0));
    vector<vector<int>> path(n + 1, vector<int>(t + 1, -1));
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
    vector<vector<float>> selected_items(2);
    vector<vector<int>> selected_indices(2);

    for (int k = 0; k <= 1; k++) {
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

    return selected_indices;
}



 pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
 {
    int j = w.size() - 1;
    vector<vector<float> > a(2, vector<float>(j + 1));
    vector<vector<int> > b(2, vector<int>(j));
    float eps = 1e-3;

    // compute expected winnings without using any lifelines
    for (int k = 0; k <= j; k++)
    {
        a[0][k] = w[k];
    }
    for (int k = 1; k <= j; k++)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            float sum = 0.0;
            for (int l = i + 1; l <= j; l++)
            {
                sum += p[l] * a[0][l];
            }
            a[0][i] = max(sum, w[i]);
        }
    }

    // compute expected winnings using only the "Get Easier" lifeline
    for (int k = 0; k <= j; k++)
    {
        a[1][k] = w[k];
    }
    for (int k = 1; k <= j; k++)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            float sum = 0.0;
            for (int l = i + 1; l <= j; l++)
            {
                float q = min(0.999f, 0.5f + p[l] / 2.0f);
                sum += q * a[1][l];
            }
            a[1][i] = max(sum, w[i]);
        }
    }

    // compute expected winnings using both lifelines
    for (int k = 0; k <= j; k++)
    {
        a[1][k] = max(a[1][k], w[k] - k * 10.0f);
    }
    for (int k = 1; k <= j; k++)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            float sum = 0.0;
            int q_index = -1;
            for (int l = i + 1; l <= j; l++)
            {
                if (a[0][l] - a[0][i] > k * 10.0f)
                {
                    continue;
                }
                if (a[1][l] - a[1][i] > k * 10.0f)
                {
                    continue;
                }
                float q = min(0.999f, 0.5f + p[l] / 2.0f);
                sum += q * a[1][l];
                if (q_index == -1 || q < min(0.999f, 0.5f + p[q_index] / 2.0f))
                {
                    q_index = l;
                }
            }
            a[1][i] = max(sum, w[i] - k * 10.0f);
            b[0][i] = q_index;
        }
    }

    // Resize the vectors to the actual size
    vector<vector<float> > res_first(2, vector<float>(t - s + 1));
    vector<vector<int> > res_second(2, vector<int>(t - s));
    // Copy the relevant part of the result to the resized vectors
    for (int i = 0; i < 2; i++)
    {
        for (int j = s; j <= t; j++)
        {
            res_first[i][j - s] = a[i][j];
            if (j < t)
            {
                res_second[i][j - s] = b[i][j];
            }
        }
    }

    return make_pair(res_first, res_second); 
}

 
