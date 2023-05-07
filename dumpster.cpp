#include <iostream> 
#include <vector> 
#include <fstream> 
#include <algorithm> 
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

    cout << "CHECkING VALUES in function : " << endl; 
    for (int i = 0; i < w.size() ; i++)
        {
            cout << w[i] << " ";
        }
    cout << endl;
    for(int i = 0; i < p.size(); i++)
        {
            cout << p[i] << " ";
        }
        cout << endl; 

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
            pf.push_back(w[k]); //assign profit value to the vector
            //cout << "Decided to quit: " << pf[k] << endl;

            //cout << "PF vertex value: " << pf[k] << endl;
            //break; //game ends 
        }
    }
    
    


    reverse(pf.begin(), pf.end()); //reverse the order of the vector
    reverse(q.begin(), q.end()); //reverse the order of the vector
    pf.pop_back(); //remove the last element of the vector
    cout << "Initial value: " << initialVal << endl;
    pf.push_back(initialVal); //add the initial value to the end of the vector

    return make_pair(pf, q);
}



int main(int argc, char const *argv[])
{
    int j, s, t;
    cin >> j >> s >> t;
    vector<float> w;
    vector<float> p;

    // push back 0 to entry 0, as there is no question 0
    w.push_back(0.0);
    p.push_back(0.0);

    for (int i = 0; i < j ; i++)
        {
            float s;
            cin >> s;
            w.push_back(s);
        }
    for (int i = 0; i < j ; i++)
        {
            float s;
            cin >> s;
            if (s < 0.25)
            s = 0.25;
            if (s > 0.9999)
            s = 0.9999;
            p.push_back(s);
        }

    cout << "CHECkING VALUES: " << endl; 
    for (int i = 0; i < j ; i++)
        {
            cout << w[i] << " ";
        }
    cout << endl;
    for(int i = 0; i < j; i++)
        {
            cout << p[i] << " ";
        }
        cout << endl; 
 
    pair< vector<float>, vector<int> > res_base = WWWWW(w, p, s, t);
    

    cout << "\nBase case : \n\n";
    for (int i = 0; i < res_base.first.size(); i++)
        {
        float x = round(res_base.first[i] * 1000) / 1000.0;    
        cout << x << " ";
        }
    cout << endl;
    for (int i = 0; i < res_base.second.size(); i++)
        {
        cout << res_base.second[i] << " ";
        }
    cout << endl;


    return 0;
}