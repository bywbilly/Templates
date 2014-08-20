/*
	test on bzoj 2626 :: find the Kth max distance point
	input n points
	for each query px, py, kth, output the Kth maxdistance point id;
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
 
typedef long long LL;

struct Point {
	int x, y, id;
};

inline LL sqr(int x) {
	return (LL)x * x;
}

inline LL dist(const Point &a, const Point &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

struct Rectangle {
	int lx , rx , ly , ry;
	void set(const Point &p) {
		lx = rx = p.x;
		ly = ry = p.y;
	}
	
	void merge(const Rectangle &o) {
		lx = min(lx , o.lx);
		rx = max(rx , o.rx);
		ly = min(ly , o.ly);
		ry = max(ry , o.ry);
	}
	// four vertex
	LL dist(const Point &p) {
		LL res = 0;
		res += max(sqr(rx - p.x), sqr(lx - p.x));
		res += max(sqr(ry - p.y), sqr(ly - p.y));
		return res;
	}
};

struct Node {
	Point p;
	Rectangle rect;
};

const int MAX_N = 111111;
const LL INF = 1LL << 60;
int n, m;
Point a[MAX_N], b[MAX_N ];
Node tree[MAX_N * 3];
Point p; // p is the query point
pair<LL, int> result[22];

bool cmpX(const Point &a, const Point &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool cmpY(const Point &a, const Point &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

void build(int k, int s, int t, bool d) {
	int mid = (s + t) >> 1;
	nth_element(a + s, a + mid , a + t, d ? cmpX : cmpY);
	tree[k].p = a[mid];
	tree[k].rect.set(a[mid]);
	if (s < mid) {
		build(k << 1, s, mid , d ^ 1);
		tree[k].rect.merge(tree[k << 1]. rect);
	}
	if (mid + 1 < t) {
		build(k << 1 | 1, mid + 1, t, d ^ 1);
		tree[k].rect.merge(tree[k << 1 | 1]. rect);
	}
}

void query(int k, int s, int t, bool d, int kth) {
	if (tree[k].rect.dist(p) < result[kth].first)
		return;
	pair<LL, int> tmp;
	tmp = make_pair(dist(tree[k].p, p), -tree[k].p.id);
	for(int i = 1; i <= kth; i++) {
		if (tmp > result[i]) {
			for(int j = kth + 1; j > i; j--)
				result[j] = result[j - 1];
			result[i] = tmp;
			break;
		}
	}
	// far first
	int mid = (s + t) >> 1;
	if ((d && cmpX(p, tree[k].p)) || (!d && cmpY(p, tree[k].p))) {
		if (mid + 1 < t)
			query(k << 1 | 1, mid + 1, t, d ^ 1, kth);
		if (s < mid)
			query(k << 1, s, mid , d ^ 1, kth);
	} else {
		if (s < mid)
			query(k << 1, s, mid , d ^ 1, kth);
		if (mid + 1 < t)
			query(k << 1 | 1, mid + 1, t, d ^ 1, kth);
	}
}

int main() {
	int tests;
	for (tests = 1; tests --; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a[i].x, &a[i].y);
			a[i].id = i;
		}
		build(1, 0, n, 0);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			int px, py, k;
			scanf("%d %d %d", &px, &py, &k);
			p.x = px; p.y = py;
			for(int j = 1; j <= k; j++)
				result[j].first = -1;
			query(1, 0, n, 0, k);
			printf("%d\n", -result[k].second + 1);
		}
	}
}