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
    int j = w.size() - 1; // number of questions
    vector<vector<float> > a(3, vector<float>(j+1)); // expected money won
    vector<vector<int> > b(3, vector<int>(j)); // decisions
    float lifeline1_penalty = 10.0;
    float lifeline2_penalty = 15.0;

    // First, calculate the expected money won with no lifelines available
    for (int i = 1; i <= j; i++) {
        // The expected money won after answering the i-th question correctly is the maximum
        // of two possibilities: quitting and taking the current winnings, or continuing and
        // risking a wrong answer.
        float quit_winnings = w[i-1];
        float continue_winnings = p[i] * (a[0][i-1] + w[i]) + (1.0 - p[i]) * a[0][0];
        a[0][i] = max(quit_winnings, continue_winnings);
        b[0][i-1] = (continue_winnings > quit_winnings) ? 1 : 0;
    }

    // Now, calculate the expected money won with the "Get easier" lifeline available
    for (int i = 1; i <= j; i++) {
        float quit_winnings = w[i-1];
        float continue_winnings_no_lifeline = p[i] * (a[1][i-1] + w[i]) + (1.0 - p[i]) * a[1][0];
        float continue_winnings_with_lifeline = 0.0;
        float lifeline1_p = min(0.5 + p[i]/2.0, 0.999);
        if (i >= s) {
            // If the contestant has answered at least s questions correctly, they get the larger prize
            continue_winnings_with_lifeline = lifeline1_p * (a[1][i-1] + w[t]) + (1.0 - lifeline1_p) * a[1][i];
        } else if (i >= t) {
            // If the contestant has answered at least t questions correctly, they get the smaller prize
            continue_winnings_with_lifeline = lifeline1_p * (a[1][i-1] + w[s]) + (1.0 - lifeline1_p) * a[1][i];
        } else {
            // Otherwise, the contestant gets nothing
            continue_winnings_with_lifeline = 0.0;
        }
        // Check if using the lifeline is worth it
        if (continue_winnings_with_lifeline >= continue_winnings_no_lifeline - lifeline1_penalty) {
            a[1][i] = continue_winnings_with_lifeline - lifeline1_penalty;
            b[1][i-1] = 2;
        } else {
            a[1][i] = continue_winnings_no_lifeline;
            b[1][i-1] = 1;
        }
    }

    // Finally, calculate the expected money won with the "Get through" lifeline available
    for (int i = 1; i <= j; i++) {
        float quit_winnings = w[i-1];
        float continue_winn;

    }

    return make_pair(a[2], b[2]);

 }

 
