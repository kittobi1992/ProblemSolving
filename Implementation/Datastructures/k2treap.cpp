#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

#define x first
#define y second
#define iter vector<point>::iterator
#define mp(X, Y) make_pair(X, Y)

#define DEBUG true

typedef pair<int, int> pt;
typedef int Weight;

struct point {
  int x, y;
  Weight w;

  point() : x(-1), y(-1), w(INT_MIN) {}

  bool inside(const pt s, const pt e) {
    return (s.x <= x && x <= e.x && s.y <= y && y <= e.y);
  }
};

bool operator<(const point& lhs, const point& rhs) {
    return lhs.w < rhs.w ||
           (lhs.w == rhs.w && lhs.x < rhs.x) ||
           (lhs.w == rhs.w && lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator==(const point& lhs, const point& rhs) {
    return (lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y);
}

struct node {
  pt start, end;
  point max_weight_pt;
  node *child[4];

  ~node() {
    for (int i = 0; i < 4; ++i)
      delete child[i];
  }

  bool intersect(pt s, pt e) {
    return !(end.x < s.x || end.y < s.y || e.x < start.x || e.y < start.y);
  }
};

int N, M, P;
vector<point> points;
node *root;

point INVALID_PT;

/**
 * Build K2Treap data structure.
 * INVARIANT: Points from start to end are inside rectangle
 *            [s.x,s.y] x [e.x,e.y]
 * NOTE: Points from start to end have to be sorted in 
 *       increasing weight order
 */
node* buildK2Treap(iter start, iter end, pt s, pt e) {
  if (start == end) return nullptr;

  node *cur = new node();
  cur->start = s;
  cur->end = e;
  cur->max_weight_pt = *(end - 1);
  if (start + 1 == end) return cur;

  int m_x = (e.x + s.x)/2;
  int m_y = (e.y + s.y)/2;
  auto it_y = stable_partition(start, end, [&](const point& p) { return p.y <= m_y; });
  auto it_x1 = stable_partition(start, it_y, [&](const point& p) { return p.x <= m_x; });
  auto it_x2 = stable_partition(it_y, end, [&](const point& p) { return p.x <= m_x; });

  // K2Treap Child Order:
  // s---+---+
  // | 0 | 1 |
  // +---m---+
  // | 2 | 3 |
  // +---+---e
  cur->child[0] = buildK2Treap(start, it_x1, s, mp(m_x, m_y));
  cur->child[1] = buildK2Treap(it_x1, it_y, mp(m_x + 1, s.y), mp(e.x, m_y));
  cur->child[2] = buildK2Treap(it_y, it_x2, mp(s.x, m_y + 1), mp(m_x, e.y));
  cur->child[3] = buildK2Treap(it_x2, end, mp(m_x + 1, m_y + 1), e);

  return cur;
}

/**
 * Return point with maximum weight in rectangle
 * [s.x,s.y] x [e.x,e.y].
 * NOTE: Call this function with root of K2Treap
 */
point maxWeightPoint(node *cur, pt s, pt e) {
  if (!cur) return INVALID_PT;
  else if (!cur->intersect(s, e)) return INVALID_PT;
  else if (cur->max_weight_pt.inside(s, e)) return cur->max_weight_pt;
  return max(maxWeightPoint(cur->child[0], s, e),
         max(maxWeightPoint(cur->child[1], s, e),
         max(maxWeightPoint(cur->child[2], s, e),
             maxWeightPoint(cur->child[3], s, e))));
}

/**
 * Naive implementation of a 2D-Weighted-Range-Query
 */
point linearScan(pt s, pt e) {
  point max_pt = INVALID_PT;
  for (int i = 0; i < points.size(); ++i) {
    if (points[i].inside(s, e)) {
      max_pt = max(max_pt, points[i]);
    }
  }
  return max_pt;
}

int main() {
  // Read input
  cin >> N >> M >> P;
  points.resize(P);
  for (int i = 0; i < P; ++i) {
    cin >> points[i].x >> points[i].y >> points[i].w;
  }

  // Build K2Treap data structure
  sort(points.begin(), points.end());
  root = buildK2Treap(points.begin(), points.end(), mp(0, 0), mp(N, M));

  // Queries
  int q = 1000;
  for (int i = 1; i <= q; ++i) {
    pt s, e;
    s.x = rand() % (N-1);
    s.y = rand() % (M-1);
    e.x = s.x + (rand() % (N - s.x - 1) + 1);
    e.y = s.y + (rand() % (M - s.y - 1) + 1);
    point max_pt = maxWeightPoint(root, s, e);
    if (DEBUG) {
      point test_max_pt = linearScan(s, e);
      if (!(test_max_pt == max_pt)) {
        cout << "Maximum Weight Point in Rectangle [" << s.x << "," << s.y
             << "] x [" << e.x << "," << e.y << "] is point (" << max_pt.x
             << "," << max_pt.y << ") with weight " << max_pt.w
             << ", but actually is point (" << test_max_pt.x
             << "," << test_max_pt.y << ") with weight " << test_max_pt.w << endl;
        return -1;
      }
    }
  }

  delete root;

  return 0;
}