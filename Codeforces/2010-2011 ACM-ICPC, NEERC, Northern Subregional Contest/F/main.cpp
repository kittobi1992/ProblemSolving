#include <bits/stdc++.h>

using namespace std;

ifstream fin("frames.in");
ofstream fout("frames.out");

typedef long long ll;

struct pt {
    ll x, y;
    
    pt() {}
    pt(ll x, ll y) : x(x), y(y) {}
};

struct rect {
    pt bl;
    pt tr;
    
    rect() {}
    rect(pt bl, pt tr) : bl(bl), tr(tr) {}
};

struct frame {
    pt obl;
    pt otr;
    pt ibl;
    pt itr;
    vector<pt> points;
    vector<rect> rects;
    
    frame() {}
    frame(pt obl, pt otr, pt ibl, pt itr) : obl(obl), otr(otr), ibl(ibl), itr(itr) {
        points.push_back(obl);
        points.push_back(otr);
        points.push_back(ibl);
        points.push_back(itr);
        points.push_back(pt(obl.x, otr.y));
        points.push_back(pt(ibl.x, itr.y));
        points.push_back(pt(itr.x, ibl.y));
        points.push_back(pt(otr.x, obl.y));
        
        rects.push_back(rect(pt(obl.x, obl.y), pt(otr.x, ibl.y)));
        rects.push_back(rect(pt(obl.x, ibl.y), pt(ibl.x, itr.y)));
        rects.push_back(rect(pt(itr.x, ibl.y), pt(otr.x, itr.y)));
        rects.push_back(rect(pt(obl.x, itr.y), pt(otr.x, otr.y)));
    }
};

bool operator<(const pt &a, const pt &b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

pt operator-(const pt &a, const pt &b) {
    return pt(a.x - b.x, a.y - b.y);
}

pt operator+(const pt &a, const pt &b) {
    return pt(a.x + b.x, a.y + b.y);
}

frame translate(frame &f, pt &t) {
    return frame(
        f.obl + t,
        f.otr + t,
        f.ibl + t,
        f.itr + t
    );
}

ll rectIntersect(rect &r1, rect &r2) {
    ll xmin = max(r1.bl.x, r2.bl.x);
    ll xmax = min(r1.tr.x, r2.tr.x);
    if (xmax <= xmin) return 0;
    
    ll ymin = max(r1.bl.y, r2.bl.y);
    ll ymax = min(r1.tr.y, r2.tr.y);
    if (ymax <= ymin) return 0;
    return (xmax - xmin) * (ymax - ymin);
}

ll intersect(frame &f1, frame &f2) {
    ll intersection = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            intersection += rectIntersect(f1.rects[i], f2.rects[j]);
        }
    }
    return intersection;
}

int main() {
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    frame f1(
        pt(min(x1, x2), min(y1, y2)),
        pt(max(x1, x2), max(y1, y2)),
        pt(min(x3, x4), min(y3, y4)),
        pt(max(x3, x4), max(y3, y4))
    );
    
    fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    frame f2(
        pt(min(x1, x2), min(y1, y2)),
        pt(max(x1, x2), max(y1, y2)),
        pt(min(x3, x4), min(y3, y4)),
        pt(max(x3, x4), max(y3, y4))
    );
	
	vector<ll> xDiff, yDiff;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pt translation = f1.points[i] - f2.points[j];
			xDiff.push_back(translation.x);
			yDiff.push_back(translation.y);
		}
	}
    
    ll bestIntersection = intersect(f1, f2);
    pt bestTranslation(0, 0);
    for (int i = 0; i < (int)xDiff.size(); i++) {
        for (int j = 0; j < (int)yDiff.size(); j++) {
            pt translation = pt(xDiff[i], yDiff[j]);
            frame translated  = translate(f2, translation);
            ll intersection = intersect(f1, translated);
            if (intersection > bestIntersection) {
                bestIntersection = intersection;
                bestTranslation = translation;
            }
            
            translation = pt(-translation.x, -translation.y);
            translated  = translate(f2, translation);
            intersection = intersect(f1, translated);
            if (intersection > bestIntersection) {
                bestIntersection = intersection;
                bestTranslation = translation;
            }
        }
    }
    fout << bestIntersection << endl;
    fout << bestTranslation.x << " " << bestTranslation.y << endl;
    return 0;
}
