
#define MAXN 1033
struct Polygon { // stored in [0, n)
	int n;
	point list[MAXN];

	Polygon cut(const point &a, const point &b) {
		static Polygon res;
		static point o;
		res.n = 0;
		for (int i = 0; i < n; ++i) {
			int s1 = sign(det(list[i] - a, b - a));
			int s2 = sign(det(list[(i + 1) % n] - a, b - a));
			if (s1 <= 0) res.list[res.n++] = list[i];
			if (s1 * s2 < 0) {
				lineIntersect(a, b, list[i], list[(i + 1) % n], o);
				res.list[res.n++] = o;
			}
		}
		return res;
	}

	bool contain(const point &p) const { // 1 if on border or inner, 0 if outter
		static point A, B;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			A = list[i];
			B = list[(i + 1) % n];
			if (p.onSeg(A, B)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		}
		return res & 1;
	}
};
