#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

struct Rectangle {
    vector<int> a;
    int idx1;
    int idx2;
    Rectangle() : a(3,0) { idx1 = -1; idx2 = -1; }
    
    int radius() {
        return min(a[0],min(a[1],a[2]));
    }
    
};

int N;
vector<Rectangle> rect;
Rectangle maxRec;
map<ii,ii> m;

void mapRectangle(Rectangle& rect) {
    ii p1 = make_pair(rect.a[0],rect.a[1]);
    ii p2 = make_pair(rect.a[0],rect.a[2]);
    ii p3 = make_pair(rect.a[1],rect.a[2]);
    auto m1 = m.find(p1);
    auto m2 = m.find(p2);
    auto m3 = m.find(p3);
    if(m1 != m.end() && m1->second.first != rect.idx1) {
        Rectangle rec;
        rec.a[0] = rect.a[0]; rec.a[1] = rect.a[1];
        rec.a[2] = rect.a[2] + m1->second.second;
        rec.idx1 = m1->second.first;
        rec.idx2 = rect.idx1;
        if(rec.radius() > maxRec.radius()) maxRec = rec;
        if(rect.a[2] > m1->second.second) m[p1] = make_pair(rect.idx1,rect.a[2]);
    } else {
        m.insert(make_pair(p1,make_pair(rect.idx1,rect.a[2])));
        if(rect.radius() > maxRec.radius()) maxRec = rect;
    }
    
    if(m2 != m.end() && m2->second.first != rect.idx1) {
        Rectangle rec;
        rec.a[0] = rect.a[0]; rec.a[2] = rect.a[2];
        rec.a[1] = rect.a[1] + m2->second.second;
        rec.idx1 = m2->second.first;
        rec.idx2 = rect.idx1;
        if(rec.radius() > maxRec.radius()) maxRec = rec;
        if(rect.a[1] > m2->second.second) m[p2] = make_pair(rect.idx1,rect.a[1]);
    } else {
        m.insert(make_pair(p2,make_pair(rect.idx1,rect.a[1])));
        if(rect.radius() > maxRec.radius()) maxRec = rect;
    }
    
    if(m3 != m.end() && m3->second.first != rect.idx1) {
        Rectangle rec;
        rec.a[1] = rect.a[1]; rec.a[2] = rect.a[2];
        rec.a[0] = rect.a[0] + m3->second.second;
        rec.idx1 = m3->second.first;
        rec.idx2 = rect.idx1;
        if(rec.radius() > maxRec.radius()) maxRec = rec;
        if(rect.a[0] > m3->second.second) m[p3] = make_pair(rect.idx1,rect.a[0]);
    } else {
        m.insert(make_pair(p3,make_pair(rect.idx1,rect.a[0])));
        if(rect.radius() > maxRec.radius()) maxRec = rect;
    }
    
}

int main() {
    
    cin >> N;
    rect.assign(N,Rectangle());
    
    for(int i = 0; i < N; ++i) { 
        cin >> rect[i].a[0] >> rect[i].a[1] >> rect[i].a[2]; 
        sort(rect[i].a.begin(),rect[i].a.end());
        rect[i].idx1 = i+1;
        mapRectangle(rect[i]);
    }
    
    if(maxRec.idx2 == -1) {
        cout << "1" << endl;
        cout << maxRec.idx1 << endl;
    }
    else {
        cout << "2" << endl;
        cout << maxRec.idx1 << " " << maxRec.idx2 << endl;
    }
    
    return 0;
}