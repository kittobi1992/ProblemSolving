#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define EPS 10e-9

vector<vector<int>> t = {{0,1,2},{1,3,5},{0,4,5},{2,3,4}};

bool isTriangle(int a, int b, int c) {
    vector<int> triangle = {a,b,c};
    sort(triangle.begin(),triangle.end());
    return triangle[0] + triangle[1] - triangle[2] > 0;
}

double areaOfTriangle (double a, double b, double c) {
    double s = (a + b + c) / 2;
    if(isTriangle(a,b,c))
        return sqrt(s) * sqrt(s-a) * sqrt(s-b) * sqrt(s-c);
    else
        return 0.0;
}

bool isTetrahedron(vector<double>& tetra, bool debug = false) {
    vector<double> area;
    for(int i = 0; i < 4; i++) {
            double a = areaOfTriangle(tetra[t[i][0]],tetra[t[i][1]],tetra[t[i][2]]);
            if(abs(a) < EPS)
                return false;
            area.push_back(a);
    }
    if(debug)  {
	cout << area[0] << ", " << area[1] << ", " << area[2] << ", " << area[3] << endl;
    }
    return (area[0] - (area[1]+area[2]+area[3])) <= EPS;
}

int main() {

    int test; cin >> test;
    while(test--) {
        vector<double> te(6);
        for(int i = 0; i < 6; i++)
            cin >> te[i];
        sort(te.begin(),te.end());
        
	if(te[0] > 10000) {
		for(int i = 0; i < 6; i++)
			te[i] = (te[i])/(10000.0);
	}

     
        bool non_zero = false;
        do {
            non_zero = isTetrahedron(te);
            if(non_zero) {
		/*for(int i = 0; i < 6; i++)
		    cout << te[i] << "(" << i << "), ";
		cout << endl;*/
                break;
	    }
        } while(next_permutation(te.begin(),te.end()));
        
	isTetrahedron(te,true);

        if(non_zero)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        
    }
  
    return 0;

}
