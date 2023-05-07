#include <vector>
#include <iostream> 
#include <cmath>

using namespace std;

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

    int numCorrect = 15; //keeps track of how many questions the contestant has correct. starts at 15 because bottom up 
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
    moneyRecieved.push_back(0); //bottom up so finish the game at start so no money earned 
    //cout << "60: " << endl; 
    for(int i = 1; i <= numCorrect; i++){
        if(i < 5){//i want 60 
            for(int i = 0; i < s; i++){
                cout << w[s] << " " << flush; 
                moneyRecieved.push_back(w[s]);
            }
        }
        //cout << "8: " << endl; 
        if(i < 10){ //i want 8 
            for(int i = 5; i < t; i++){
                //cout << w[t] << " " << flush;
                moneyRecieved.push_back(w[t]);
            }
        }
        //cout << endl; 
        if(i < 15){ //i want 0 
            for(int i = 10; i < j; i++){
                //cout << w[j] << " " << flush;
                moneyRecieved.push_back(w[j]);
            }
        }
        numCorrect--; //decrement numCorrect to simulate the contestant getting a question correct 
    }

    //cout << endl; 
    // cout << "ME R: " << endl; 
    // for(int i = 0; i < moneyRecieved.size(); i++){
    //     cout <<  moneyRecieved[i] << " " << flush; 
    // }
    // cout << endl; 

    // moneyRecieved.push_back(60);
    // moneyRecieved.push_back(60);
    // moneyRecieved.push_back(60);
    // moneyRecieved.push_back(60);
    // moneyRecieved.push_back(60);
    // moneyRecieved.push_back(8); 
    // moneyRecieved.push_back(8);
    // moneyRecieved.push_back(8);
    // moneyRecieved.push_back(8);
    // moneyRecieved.push_back(8);
    // moneyRecieved.push_back(0); 
    // moneyRecieved.push_back(0);
    // moneyRecieved.push_back(0);
    // moneyRecieved.push_back(0);
    // moneyRecieved.push_back(0);




    

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

pair< vector< vector<float> > ,vector< vector<int> > > WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    int n = w.size();
    vector< vector<float> > a(2, vector<float>(n+1));
    vector< vector<int> > b(2, vector<int>(n));
    float q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        a[0][i] = q * w[i];
        q *= 1.0 - p[i];
    }
    a[0][n] = q * s;
    q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        float p_with_lifeline = min(static_cast<float>(p[i] * 0.5 + p[i] * 0.5), 0.999f);
        float expected_reward_without_lifeline = q * w[i];
        float expected_reward_with_lifeline = q * ((1.0 - p[i]) * w[i] + p_with_lifeline * s);
        if (expected_reward_with_lifeline >= expected_reward_without_lifeline)
        {
            a[1][i] = expected_reward_with_lifeline;
            b[1][i] = 1;
        }
        else
        {
            a[1][i] = expected_reward_without_lifeline;
            b[1][i] = 2;
        }
        q *= 1.0 - p[i];
    }
    a[1][n] = q * s;
    b[0][n-1] = 0;
    for (int i = n-1; i >= 1; i--)
    {
        if (a[0][i-1] >= a[1][i-1])
        {
            b[0][i-1] = 0;
        }
        else
        {
            if (a[0][i] >= a[1][i])
            {
                b[0][i-1] = 1;
            }
            else
            {
                b[0][i-1] = 2;
            }
        }
    }
    if (a[0][0] >= a[1][0])
    {
        b[0][n-1] = 0;
    }
    else
    {
        b[0][n-1] = 2;
    }
    return make_pair(a, b);
}





pair< vector< vector<float> > ,vector< vector<int> > > WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
    int n = w.size();
    vector< vector<float> > a(4, vector<float>(n+1));
    vector< vector<int> > b(4, vector<int>(n));
    float q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        a[0][i] = q * w[i];
        q *= 1.0 - p[i];
    }
    a[0][n] = q * s;

    q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        float p_with_lifeline = min(static_cast<float>(p[i] * 0.5 + p[i] * 0.5), 0.999f);
        float expected_reward_without_lifeline = q * w[i];
        float expected_reward_with_lifeline = q * ((1.0 - p[i]) * w[i] + p_with_lifeline * s);
        if (expected_reward_with_lifeline >= expected_reward_without_lifeline)
        {
            a[1][i] = expected_reward_with_lifeline;
            b[1][i] = 1;
        }
        else
        {
            a[1][i] = expected_reward_without_lifeline;
            b[1][i] = 2;
        }
        q *= 1.0 - p[i];
    }
    a[1][n] = q * s;

    q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        float expected_reward_without_lifeline = q * w[i];
        float expected_reward_with_lifeline = (1 - p[i]) * s;
        if (expected_reward_with_lifeline >= expected_reward_without_lifeline)
        {
            a[2][i] = expected_reward_with_lifeline - 10.0 * (n - i - 1);
            b[2][i] = 3;
        }
        else
        {
            a[2][i] = expected_reward_without_lifeline;
            b[2][i] = 2;
        }
        q *= 1.0 - p[i];
    }
    a[2][n] = q * s;

    q = 1.0;
    for (int i = n-1; i >= 0; i--)
    {
        float p_with_lifeline = min(static_cast<float>(p[i] * 0.5 + p[i] * 0.5), 0.999f);
        float expected_reward_without_lifeline = q * w[i];
        float expected_reward_with_get_easier = q * ((1.0 - p[i]) * w[i] + p_with_lifeline * s) - 5.0 * (n - i - 1);
        float expected_reward_with_get_through = (1 - p[i]) * s - 10.0 * (n - i - 1);
        if (expected_reward_with_get_easier >= expected_reward_without_lifeline && expected_reward_with_get_easier >= expected_reward_with_get_through)
        {
            a[3][i] = expected_reward_with_get_easier;
            b[3][i] = 2;
        }
        else if (expected_reward_with_get_through >= expected_reward_without_lifeline && expected_reward_with_get_through >= expected_reward_with_get_easier)
                {
                    a[3][i] = expected_reward_with_get_through;
                    b[3][i] = 3;
                }
                else
                {
                    a[3][i] = expected_reward_without_lifeline;
                    b[3][i] = 1;
                }
                
                if (i == n - 1)
                {
                    a[0][i] = q * w[i];
                    a[1][i] = q * ((1.0 - p[i]) * w[i] + p[i] * s) - 5.0 * (n - i - 1);
                    a[2][i] = (1 - p[i]) * s - 10.0 * (n - i - 1);
                    b[0][i] = 1;
                    b[1][i] = 1;
                    b[2][i] = 1;
                }
                else
                {
                    a[0][i] = q * w[i] + (1 - q) * a[0][i + 1];
                    a[1][i] = q * ((1.0 - p[i]) * w[i] + p[i] * s) - 5.0 * (n - i - 1) + (1 - q) * a[1][i + 1];
                    a[2][i] = (1 - p[i]) * s - 10.0 * (n - i - 1) + (1 - q) * a[2][i + 1];
                    
                    float expected_reward_with_both_lifelines = q * ((1.0 - p[i]) * w[i] + p_with_lifeline * s - (i == 0 ? 0 : 10.0 * (n - i))) + (1 - q) * a[3][i + 1] - 5.0 * (n - i - 1);
                    if (expected_reward_with_both_lifelines >= expected_reward_with_get_easier && expected_reward_with_both_lifelines >= expected_reward_with_get_through && expected_reward_with_both_lifelines >= expected_reward_without_lifeline)
                    {
                        a[3][i] = expected_reward_with_both_lifelines;
                        b[3][i] = 4;
                    }
                }
            }
            
            return make_pair(a, b);
        }