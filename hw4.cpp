#include <vector>
#include <iostream> 

using namespace std;


std::pair<std::vector<float>, std::vector<int> > WWWWW3(std::vector<float> w, std::vector<float> p, int s, int t)
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

pair< vector<float>, vector<int> > WWWWW(vector<float> w, vector<float> p, int s, int t)
{
    int initialVal = w.back(); //save last element for later appending
    w.pop_back(); 
    p.pop_back(); 
    w.push_back(0.0); //push back 0 to entry 0, as there is no question 0
    p.push_back(0.0); //push back 0 to entry 0, as there is no question 0
    reverse(w.begin(), w.end()); //reverse the order of the vector
    reverse(p.begin(), p.end()); //reverse the order of the vector

    w.pop_back(); //pop back the last element of the vector
    p.pop_back(); //pop back the last element of the vector

    // cout << "CHECkING VALUES in function : " << endl; 
    // for (int i = 0; i < w.size() ; i++)
    //     {
    //         cout << w[i] << " ";
    //     }
    // cout << endl;
    // for(int i = 0; i < p.size(); i++)
    //     {
    //         cout << p[i] << " ";
    //     }
    //     cout << endl; 

    int numCorrect = 1; //keeps track of how many questions the contestant has correct 
    //int moneyRecieved = 0; //keeps track of how much money the contestant has recieved
    int j = w.size(); //infer j based on length of w array 

    vector <float> pf(j, 0); //profit values 
    vector <int> q(j, 0); //quit values 

    //math for predicting profit and loss
    //pk * ck+1 + (1- pk) * w 
    //1,000,000 * (35/100) + 32,000 * (65/100) = 248,300
    //w * (p/100) + missing value * ((100-p)/100) = profit 
    //6.13548 * 0.99 + 0 * 0.01 

    //predetermined values 
    vector <float> moneyRecieved; 
    moneyRecieved.push_back(0);
    moneyRecieved.push_back(60);
    moneyRecieved.push_back(60);
    moneyRecieved.push_back(60);
    moneyRecieved.push_back(60);
    moneyRecieved.push_back(60);
    moneyRecieved.push_back(8); 
    moneyRecieved.push_back(8);
    moneyRecieved.push_back(8);
    moneyRecieved.push_back(8);
    moneyRecieved.push_back(8);
    moneyRecieved.push_back(0); 
    moneyRecieved.push_back(0);
    moneyRecieved.push_back(0);
    moneyRecieved.push_back(0);
    moneyRecieved.push_back(0);

    //initial value for profit
    //pf[0] = w[0]; //profit is equal to the current amount of money (Wk)
    //pf.push_back(w[0]); //assign profit value to the vector 

    for (int k = 0; k <= j; k++)
    {
         
        // cout << "P[k]: " << p[k] << endl;
        // cout << "pf[k+1]: " << pf[k+1] << endl;
        // cout << "1 - p[k]: " << 1 - p[k-1] << endl;
        // cout << "w[k]: " << w[k] << endl;

        //pf[k] = p[k] * pf[k + 1] + (1 - p[k]) * w[k];
        //pf[k] = (p[k] * (pf[k + 1]) + (0 * ((100 - w[k])/100));
        //pf[k] = 6.13548 * p[k] + pf[k+1] * ((1 - p[k]));
        //cout << "previous profit value: " << pf[k-1] << endl; 
        //pf[k] = pf[k-1] * p[k] + pf[k+1] * ((1 - p[k]));
        //pf[k] = pf[k-1] * p[k-1] + 60 * ((1 - p[k-1]));
        //cout << "1-p[k]: " << 1-p[k] << endl;
        //cout << "K: " << k << endl; 

        // if(numCorrect == s){
        //     moneyRecieved = w[s];  
        //     cout << "moneyS: " << moneyRecieved << endl;
        // }
        // if(numCorrect == t){
        //     moneyRecieved = w[t]; 
        //     cout << "moneyT: " << moneyRecieved << endl;

        // }

        //cout << "W[k]:" << w[k] << endl;
        pf[k] = pf[k-1] * p[k-1] +  moneyRecieved[k] * ((1 - p[k-1]));
        //cout << "PFK calc: " << pf[k] << endl;
        // cout << "pf[k]: " << pf[k] << endl;
        // cout << "W[k]: " << w[k] << endl;
    
        if (pf[k] > w[k]) //if profit greater than current amount of money (Wk)
        {
            q[k] = 1; //not quit
            if(q.size() < 15)
                q.push_back(1); //answer 
            //pf[k] = pf[k + 1]; //profit is equal to the next profit value
            //pf[k] = w[k]; //profit is equal to the current amount of money (Wk)
            if(q.size() < 15)
                pf.push_back(pf[k]); //assign profit value to the vector 
            //cout << "Decided not to quit: " << pf[k] << endl;

            //cout << "PROFIT: " << pf[k] << endl;
            numCorrect++; //increment number of correct answers
        }
        else //quit 
        {
            q[k] = 0; //quit 
            if(q.size() < 15)
                q.push_back(0); //quit 
            pf[k] = w[k]; //profit is equal to the current amount of money (Wk)
            //cout << "W[K] Vertex value: " << w[k] << endl;
            if(q.size() < 15)
                pf.push_back(w[k]); //assign profit value to the vector
            //cout << "Decided to quit: " << pf[k] << endl;

            //cout << "PF vertex value: " << pf[k] << endl;
            //break; //game ends 
        }
    }
    
    reverse(pf.begin(), pf.end()); //reverse the order of the vector
    reverse(q.begin(), q.end()); //reverse the order of the vector
    pf.pop_back(); //remove the last element of the vector
    //cout << "Initial value: " << initialVal << endl;
    pf.push_back(initialVal); //add the initial value to the end of the vector

    return make_pair(pf, q);
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

 
