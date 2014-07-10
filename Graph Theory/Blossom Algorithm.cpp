
int n, match[MAXN];
int Q[MAXN], head, tail;
int pred[MAXN], label[MAXN];
int inq[MAXN], inb[MAXN];
int S, T, lca;
vector<int> link[MAXN];

void init(int _n) {
	n = _n;
	for (int i = 0; i < n; ++i)
		link[i].clear();
}

inline void push(int x) {
	Q[tail++] = x;
	inq[x] = true;
}

int findCommonAncestor(int x, int y) {
	static bool inPath[MAXN];
	for (int i = 0; i < n; ++i)
		inPath[i] = 0;
	for ( ; ; x = pred[ match[x] ]) {
		x = label[x];
		inPath[x] = true;
		if (x == S) break;
	}
	for ( ; ; y = pred[ match[y] ]) {
		y = label[y];
		if (inPath[y]) break;
	}
	return y;
}

void resetTrace(int x, int lca) {
	while (label[x] != lca) {
		int y = match[x];
		inb[ label[x] ] = inb[ label[y] ] = true;
		x = pred[y];
		if (label[x] != lca) pred[x] = y;
	}
}

void blossomContract(int x, int y) {
	lca = findCommonAncestor(x, y);
	for (int i = 0; i < n; ++i)
		inb[i] = 0;
	resetTrace(x, lca);
	resetTrace(y, lca);
	if (label[x] != lca) pred[x] = y;
	if (label[y] != lca) pred[y] = x;
	for (int i = 0; i < n; ++i)
		if (inb[ label[i] ]) {
			label[i] = lca;
			if (!inq[i]) push(i);
		}
}

bool findAugmentingPath() {
	for (int i = 0; i < n; ++i) pred[i] = -1;
	for (int i = 0; i < n; ++i) label[i] = i;
	for (int i = 0; i < n; ++i) inq[i] = 0;

	int x, y, z;
	head = tail = 0;
	for (push(S); head < tail; ) {
		x = Q[head++];
		for (int i = (int)link[x].size() - 1; i >= 0; --i) {
			y = link[x][i];
			if (label[x] == label[y] || x == match[y]) continue;
			if (y == S || (match[y] >= 0 && pred[ match[y] ] >= 0))
				blossomContract(x, y);
			else if (pred[y] == -1) {
				pred[y] = x;
				if (match[y] >= 0)
					push(match[y]);
				else { // augment
					for (x = y; x >= 0; x = z) {
						y = pred[x];
						z = match[y];
						match[x] = y;
						match[y] = x;
					}
					return true;
				}
			}
		}
	}
	return false;
}

int findMaxMatching() {
	int ans = 0;
	for (int i = 0; i < n; ++i) match[i] = -1;
	for (S = 0; S < n; ++S)
		if (match[S] == -1)
			if (findAugmentingPath())
				++ans;
	return ans;
}