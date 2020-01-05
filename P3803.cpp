#include <complex>
#include <math.h>
#include <iostream>
using namespace std;
const double PI = 3.1415926535898;
const int N = 2e6 + 5;
double x;
complex< double > omega(int n, int k) {
	return complex< double >(cos(2 * PI * k / n), sin(2 * PI * k / n));
}
void FFT(complex< double > *a, int n, bool inv) {
	if(n == 1) return;
	static complex< double > buf[N];
	int m = n / 2;
	for(int i = 0; i < m; i++) {
		buf[i] = a[2 * i];
		buf[i + m] = a[2 * i + 1];
	}
	for(int i = 0; i < n; i++) a[i] = buf[i];
	FFT(a, m, inv);
	FFT(a + m, m, inv);
	for(int i = 0; i < m; i++) {
		complex< double > x = omega(n, i);
		if(inv) x = conj(x);
		buf[i] = a[i] + x * a[i + m];
		buf[i + m] = a[i] - x * a[i + m];
	}
	for(int i = 0; i < n; i++) a[i] = buf[i];
	return;
}
complex< double > A[N], B[N];
int main() {
	int n, m, nm = 1;
	cin >> n >> m;
	for(int i = 0; i <= n; i++) {
		cin >> x;
		A[i].real(x);
	}
	for(int i = 0; i <= m; i++) {
		cin >> x;
		B[i].real(x);
	}
	while(nm <= n + m) nm <<= 1;
	FFT(A, nm, 1);
	FFT(B, nm, 1);
	for(int i = 0; i <= nm; i++) {
		A[i] = A[i] * B[i];
	}
	FFT(A, nm, 0);
	for(int i = 0; i <= n + m; i++) cout << (int)(A[i].real() / nm + 0.5) << ' ';
	cout << endl;
	return 0;
}