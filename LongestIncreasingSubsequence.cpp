#include <iostream>
using namespace std;

int lowerbound(int l, int r, long long val, long long* tab) {
	while (l != r) {
		int m = (l + r) / 2;
		if (tab[m] < val) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

int lis(long long* tab, int n) {
	int l, r;
	l = 0;
	r = 1;
	long long* tmp = new long long[n];
	for (int i = 0; i < n; i++) {
		tmp[i] = LLONG_MAX;
	}
	for (int i = 0; i < n; i++) {
		int ind = lowerbound(l, r, tab[i], tmp);
		tmp[ind] = tab[i];
		if (ind == r) {
			r++;
		}
	}
	return r;
}

int main_ndskjvcio() {
	int n;
	cin >> n;
	long long* tab = new long long[n];
	for (int i = 0; i < n; i++) {
		long long x;
		cin >> x;
		tab[i] = x;
	}
	int result = lis(tab, n);
	cout << result;
	return 0;
}