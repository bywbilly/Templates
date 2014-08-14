#pragma comment(linker, "/STACK:10240000")

#define UseBuffer

#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <stack>
#include <set>
#include <utility>
#include <vector>

#define Lowbit(x) ((x) & (-(x)))
#define Pow2(x) (1 << (x))
#define Pow2LL(x) (1LL << (x))
#define Contain(a, x) (((a) >> (x)) & 1)

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)

#define Debug(x) (cerr << #x << " = " << (x) << endl)
#define Debug2(x, y) (cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl)

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int INF = 1000000000;

template <class T> inline bool cMin(T &a, const T &b) {
	return a > b ? (a = b, true) : false;
}

template <class T> inline bool cMax(T &a, const T &b) {
	return a < b ? (a = b, true) : false;
}

#ifdef UseBuffer
#define MaxBuffer 5

namespace BufferedReader {

	char buff[MaxBuffer + 5], *buf = buff;
	char c;
	bool flag;

	inline bool nextChar(char &c) {
		if ( (c = *buf++) == 0 ) {
			int tmp = fread(buff, 1, MaxBuffer, stdin);
			buff[tmp] = 0;
			if (tmp == 0)
				return false;
			buf = buff;			
			c = *buf++;
		}
		return true;
	}

	inline bool nextUnsignedInt(unsigned int &x) {
		for ( ; ; ) {
			if ( !nextChar(c) )
				return false;
			if ('0' <= c && c <= '9') break;
		}
		x = c - '0';
		for ( ; ; ) {
			if ( !nextChar(c) )
				break;
			if (c < '0' || c > '9') break;
			x = x * 10 + c - '0';
		}
		return true;
	}

	inline bool nextInt(int &x) {
		for ( ; ; ) {
			if ( !nextChar(c) )
				return false;
			if (c == '-' || ('0' <= c && c <= '9'))
				break;
		}
		if (c == '-') {
			x = 0;
			flag = true;
		}
		else {
			x = c - '0';
			flag = false;
		}
		for ( ; ; ) {
			if ( !nextChar(c) )
				break;
			if (c < '0' || c > '9') break;
			x = x * 10 + c - '0';
		}
		if (flag) x = -x;
		return true;
	}

};
#endif

int main() {
	int x;
	while (BufferedReader::nextInt(x))
		printf("%d\n", x);
	return 0;
}
