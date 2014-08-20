#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const double error = 1e-12;
const double infi = 1e+12;

double a[10], x[10];
int n;

int sign(double x) {
	return (x < -error) ? (-1) : (x > error);
}

double f(double a[], int n, double x) {
	double tmp = 1, sum = 0;
	for (int i = 0; i <= n; i++) {
		sum = sum + a[i] * tmp;
		tmp = tmp * x;
	}
	return sum;
}

double binary(double l, double r, double a[], int n) {
	int sl = sign(f(a, n, l)), sr = sign(f(a, n, r));
	if (sl == 0) return l;
	if (sr == 0) return r;
	if (sl * sr > 0) return infi;
	while (r - l > error) {
		double mid = (l + r) / 2;
		int ss = sign(f(a, n, mid));
		if (ss == 0) return mid;
		if (ss * sl > 0) l = mid;
		else r = mid;
	}
	return l;
}

void solve(int n, double a[], double x[], int &nx) {
	if (n == 1) {
		x[1] = -a[0] / a[1];
		nx = 1;
		return;
	}
	double da[10], dx[10];
	int ndx;
	for (int i = n; i >= 1; i--) da[i - 1] = a[i] * i;
	solve(n - 1, da, dx, ndx);

	nx = 0;
	if (ndx == 0) {
		double tmp = binary(-infi, infi, a, n);
		if (tmp < infi)
			x[++nx] = tmp;
		return;
	}

	double tmp;
	tmp = binary(-infi, dx[1], a, n);
	if (tmp < infi)
		x[++nx] = tmp;
	for (int i = 1; i <= ndx - 1; i++) {
		tmp = binary(dx[i], dx[i + 1], a, n);
		if (tmp < infi)
			x[++nx] = tmp;
	}
	tmp = binary(dx[ndx], infi, a, n);
	if (tmp < infi)
		x[++nx] = tmp;
}

int main() {
	scanf("%d", &n);
	for (int i = n; i >= 0; i--)
		scanf("%lf", &a[i]);
	int nx;
	solve(n, a, x, nx);
	for (int i = 1; i <= nx; i++)
		printf("%0.6f\n", x[i]);
	return 0;
}
