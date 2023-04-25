#include <vector>

using namespace std;
//random values are stuffed into these functions so that output is printed. These values should be changed. 
//no late pass will be used for this assignment.
//driver program should be indexed at zero. He will fix this? 
pair< vector<float>, vector<int> >  WWWWW(vector<float> w, vector<float> p, int s, int t)
{
    // vector <float> res0;
    // vector <int> res1;

    // res0.push_back(1.0);
    // res0.push_back(2.0);
    // res1.push_back(1);
    // return make_pair(res0, res1);
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

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float>, vector<float>, int, int)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float>, vector<float>, int, int)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

 
