namespace FFT {

	struct Complex {
		double a, b;
		Complex(): a(0.0), b(0.0) {
		}
		Complex(double a, double b): a(a), b(b) {
		}
	};

	int n, id, *A, *B, *s, len;
	Complex tmp[MAXLEN], pa[MAXLEN], pb[MAXLEN], *p;

	void Fill(int m, int d) {
		if (m == n) {
			if (id < len)
				p[d] = Complex(s[id++], 0.0);
			else
				p[d] = Complex();
		}
		else {
			Fill(m << 1, d);
			Fill(m << 1, d + m);
		}
	}

	void Fill2(int m, int d) {
		if (m == n) {
			p[d] = tmp[id++];
		}
		else {
			Fill2(m << 1, d);
			Fill2(m << 1, d + m);
		}
	}

	void FFT(int oper) {
		for (int d = 0; (1 << d) < n; ++d) {
			int m = 1 << d;
			double p0 = PI / m * oper;
			double sinp0 = sin(p0);
			double cosp0 = cos(p0);
			for (int i = 0; i < n; i += m << 1) {
				double sinp = 0, cosp = 1;
				for (int j = 0; j < m; ++j) {
					double ta = cosp * p[i + j + m].a - sinp * p[i + j + m].b;
					double tb = cosp * p[i + j + m].b + sinp * p[i + j + m].a;
					p[i + j + m].a = p[i + j].a - ta;
					p[i + j + m].b = p[i + j].b - tb;
					p[i + j].a += ta;
					p[i + j].b += tb;
					double tsinp = sinp;
					sinp =  tsinp * cosp0 + cosp * sinp0;
					cosp = -tsinp * sinp0 + cosp * cosp0;
				}
			}
		}
	}

	void doFFT(int a[], int la, int b[], int lb, int C[]) {
		A = a; B = b;
		for (n = la + lb; n != Lowbit(n); n += Lowbit(n));

		id = 0; s = A; p = pa; len = la; Fill(1, 0); FFT(1);
		id = 0; s = B; p = pb; len = lb; Fill(1, 0); FFT(1); 
		for (int i = 0; i < n; ++i) {
			tmp[i].a = pa[i].a * pb[i].a - pa[i].b * pb[i].b;
			tmp[i].b = pa[i].b * pb[i].a + pa[i].a * pb[i].b;
		}

		id = 0; p = pa; Fill2(1, 0); FFT(-1);
		for (int i = 0; i < n; ++i) {
			double t = p[i].a / (double)(n);
			C[i] = int(t + 0.5);
		}
	}
}

