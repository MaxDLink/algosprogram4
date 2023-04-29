#include <iostream>
#include <vector>
#include <utility>

using namespace std;

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

    return {a, b};
}

int main() {
    vector<float> w = {100, 500, 1000, 2000, 5000, 10000, 25000, 50000, 100000, 200000};
    vector<float> p = {0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.3, 0.3, 0.3};
    int s = 2, t = 6;

    pair< vector< vector<float> > ,vector< vector<int> > > result = WWWWW_2(w, p, s, t);

    for (const auto &row : result.first) {
        for (float value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (const auto &row : result.second) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    return 0;
}

