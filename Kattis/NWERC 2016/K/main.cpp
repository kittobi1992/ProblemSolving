#include <bits/stdc++.h>

using namespace std;

#define MAX_DIST 4000.0
#define EPS 1e-2
#define EPSILON 1e-4
#define PI acos(-1)

using pt = complex<double>;


int N;
vector<pt> poly;
vector<pt> point;

double dot(pt a, pt b) { return real(conj(a) * b); }

double det(pt a, pt b) { return real(a)*imag(b)-imag(a)*real(b); }

double angle(pt a, pt b) { return PI + atan2(det(a,b),dot(a,b)); }

double cross(pt a, pt b) { return imag(conj(a) * b); }

double orientation(pt a, pt b, pt c) {
  double orien = cross(b - a, c - a);
  if (abs(orien) < EPSILON) return 0; // Braucht großes EPSILON: ~1e-6
  return orien < 0 ? -1 : 1;
}

bool pointOnLineSegment(pt a, pt b, pt p) {
  if (orientation(a, b, p) != 0) return false;
  return real(p) >= min(real(a), real(b)) &&
         real(p) <= max(real(a), real(b)) &&
         imag(p) >= min(imag(a), imag(b)) &&
         imag(p) <= max(imag(a), imag(b));
}

double distToSegment(pt a, pt b, pt p) {
  if (a == b) return abs(p - a);
    double segLength = abs(a - b);
    double u = ((real(p) - real(a)) * (real(b) - real(a)) +
        (imag(p) - imag(a)) * (imag(b) - imag(a))) /
        (segLength * segLength);
    pt projection(real(a) + u * (real(b) - real(a)),
        imag(a) + u * (imag(b) - imag(a)));
    double projectionDist = abs(p - projection);
    if (!pointOnLineSegment(a, b, projection)) projectionDist = 1e30;
    return min(projectionDist, min(abs(p - a), abs(p - b)));
}

pt incircle_point(pt a, pt b, pt c) {
  pt n1 = pt(imag(b-a),-real(b-a));
  n1 /= abs(n1);
  double l = 0.0; double r = 1.0;
  while(abs(r-l) > 1e-8) {
    double m = (l+r)/2.0;
    pt p = b+m*(a-b)+MAX_DIST*n1;
    if(distToSegment(b,c,p) > MAX_DIST-1e-8) r = m;
    else l = m;
  }
  return b+(a-b)*r+MAX_DIST*n1;
}


int main() {
  
  cin >> N;
  poly.assign(N,pt(0,0));
  for(int i = 0; i < N; ++i) {
    double x,y; cin >> x >> y;
    poly[i] = pt(x,y);
  }
  
  for(int i = 0; i < N; ++i) {
      pt a = poly[i % N], b = poly[(i+1) % N], c = poly[(i+2) % N];
      if(angle(b-a,c-b) <= PI+EPS) point.push_back(incircle_point(a,b,c));
      else {
          pt d = -1.0*(((a-b)+(c-b))/2.0)/abs(((a-b)+(c-b))/2.0);
          point.push_back(b+MAX_DIST*d);
      }
  }
  
  vector<pt> res;
  for(int i = 0; i < point.size(); ++i) {
    pt p = point[i]; bool valid = true;
    for(int j = 0; j < N; ++j) {
      double dist = distToSegment(poly[j],poly[(j+1) % N], p);
      if(dist < MAX_DIST-EPS) valid = false;
    }
    if(valid) res.push_back(p);
  }
  int i = 0, j = 1;
  for(; i < res.size(); ++i) {
    bool found = false;
    for(j = i+1; j < res.size(); ++j) {
      if(abs(res[i]-res[j]) > 2*MAX_DIST-EPS) {
        found = true; break;
      }
    }
    if(found) break;
  }
  if(res.size() >= 2 && i != point.size()) {
    cout << fixed << setprecision(6);
    cout << real(res[j]) << " " << imag(res[j]) << endl;
    cout << real(res[i]) << " " << imag(res[i]) << endl;
  }
  else {
    cout << "impossible" << endl;
  }
  
	return 0;
}
