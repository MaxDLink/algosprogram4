#include <vector>

using namespace std;
//random values are stuffed into these functions so that output is printed. These values should be changed. 
//no late pass will be used for this assignment.
//driver program should be indexed at zero. He will fix this? 

pair< vector<float>, vector<int> >  WWWWW(vector<float> w, vector<float> p, int s, int t)
{
    int j = w.size() - 1;
    vector<float> E(j+1, 0);
    vector<int> Q(j+1, 0);
    E[1] = w[1]*p[1];
    Q[1] = 0;
    for (int i=2; i<=j; i++) {
        float max_val = w[i];
        for (int k=1; k<i; k++) {
            float val = w[k] + (1-p[k])*E[k-1];
            if (val > max_val) {
                max_val = val;
            }
        }
        E[i] = max_val;
        if (w[i] > max_val) {
            Q[i] = 1;
        }
    }
    return make_pair(E, Q);

}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    int n = w.size();
    vector<vector<float> > dp(n + 1, vector<float>(t + 1, 0));
    vector<vector<int> > prev(n + 1, vector<int>(t + 1, -1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = s; j <= t; j++)
        {
            if (j >= w[i - 1])
            {
                float val = dp[i - 1][j - w[i - 1]] + p[i - 1];
                if (val > dp[i][j])
                {
                    dp[i][j] = val;
                    prev[i][j] = j - w[i - 1];
                }
            }
            if (dp[i - 1][j] > dp[i][j])
            {
                dp[i][j] = dp[i - 1][j];
                prev[i][j] = j;
            }
        }
    }

    vector<int> items;
    int j = t;
    for (int i = n; i >= 1; i--)
    {
        if (prev[i][j] != j)
        {
            items.push_back(i - 1);
            j = prev[i][j];
        }
    }
    reverse(items.begin(), items.end());

    return make_pair(dp, vector<vector<int> >(1, items));

}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
   int n = w.size();
    vector<vector<float> > dist(n, vector<float>(n, numeric_limits<float>::infinity()));
    vector<vector<int> > parent(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0.0;
        for (int j = i + 1; j < n; j++) {
            float d = w[i] + w[j];
            if (d <= p[j]) {
                dist[i][j] = dist[j][i] = d;
                parent[i][j] = j;
                parent[j][i] = i;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[i][k];
                }
            }
        }
    }

    vector<vector<float> > weights;
    vector<vector<int> > paths;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i == s && j == t || parent[i][j] != -1 && parent[j][i] != -1) {
                vector<int> path;
                int curr = i;
                while (curr != j) {
                    path.push_back(curr);
                    curr = parent[curr][j];
                }
                path.push_back(j);

                reverse(path.begin(), path.end());

                vector<float> path_weights(path.size());
                path_weights[0] = w[path[0]];
                for (int k = 1; k < path.size(); k++) {
                    path_weights[k] = w[path[k]];
                    for (int l = 0; l < k; l++) {
                        int u = path[l], v = path[k];
                        path_weights[k] += (dist[u][v] - w[u] - w[v]) / 2.0;
                    }
                }

                weights.push_back(path_weights);
                paths.push_back(path);
            }
        }
    }

    return make_pair(weights, paths);
}

 
