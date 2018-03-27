#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-8
#define PI acos(-1)
#define P(X,Y) make_pair(X,Y)
#define x first
#define y second

typedef pair<double,double> pt;

vector<pt> poly;
int n;
vector<pt> points;

void createPolygon(int k, pt p) {
    poly.clear();
    poly.push_back(p);
    double gamma = (2*PI)/k;
    for(int i = 0; i < k-1; ++i) {
        pt q = P(poly[i].x * cos(gamma) - poly[i].y * sin(gamma), poly[i].y * cos(gamma) + poly[i].x * sin(gamma));
        poly.push_back(q);
    }
}

double dot(pt v1, pt v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

double magnitude(pt v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double angle(pt p1, pt p2, pt p3) {
    pt v1 = P(p2.x - p1.x, p2.y - p1.y);
    pt v2 = P(p3.x - p1.x, p3.y - p1.y);
    double mag_v1 = magnitude(v1);
    double mag_v2 = magnitude(v2);
    if(mag_v1 <= EPS) mag_v1 = EPS;
    if(mag_v2 <= EPS) mag_v2 = EPS;
    return acos(dot(v1,v2)/(mag_v1*mag_v2));
}

bool isInsidePolygon(pt p) {
    int k = poly.size();
    double gamma = 0;
    for(int i = 0; i < k - 1; ++i) {
        gamma += angle(p, poly[i], poly[i+1]);
    }
    gamma += angle(p, poly[k-1], poly[0]);
    return abs(gamma - 2*PI) <= EPS;
}

double calculateAreaTriangle(pt p1, pt p2, pt p3) {
    double a = magnitude(P(p2.x-p1.x,p2.y-p1.y));
    double b = magnitude(P(p3.x-p2.x,p3.y-p2.y));
    double c = magnitude(P(p1.y-p3.x,p1.y-p3.y));
    double s = (a+b+c)/2.0;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double calculateAreaPolygon() {
    int k = poly.size();
    double area = 0.0;
    for(int i = 0; i < k; ++i) {
        area += calculateAreaTriangle(P(0,0),poly[i],poly[(i+1) % k]);
    }
    return area;
}

template<bool inside = true>
void findPolygon(int k) {
    double l = 0.0, r = 1e16;
    while(abs(r-l) > EPS) {
        double m = (l+r)/2.0;
        createPolygon(k,P(m,0));
        bool res = true;
        for(int i = 0; i < n; ++i) {
            bool isInside = isInsidePolygon(points[i]);
            if(!inside) isInside = !isInside;
            res &= isInside;
        }
        if(res && inside) r = m;
        else if(!res && inside) l = m;
        else if(res && !inside) l = m;
        else r = m;
    }
}

int main() {

    cin >> n;
    points.assign(n,P(0,0));
    for(int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    int max_k = 0;
    double max_score = 0.0;
    for(int k = 3; k <= 8; ++k) {
        findPolygon<true>(k);
        double A_outer = calculateAreaPolygon();
        findPolygon<false>(k);
        double A_inner = calculateAreaPolygon();
        double score = A_inner/A_outer;
        if(score >= max_score) {
            max_k = k;
            max_score = score;
        }
    } 

    cout << max_k << " " << fixed << setprecision(10) << max_score << endl;

    return 0;
}