#include <vector>

using namespace std;
//random values are stuffed into these functions so that output is printed. These values should be changed. 
pair< vector<float>, vector<int> >  WWWWW(vector<float>, vector<float>, int, int)
{
    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);
    return make_pair(res0, res1);

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

 
