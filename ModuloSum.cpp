#include <iostream>
using namespace std;

bool subsequence_exist(int* A, int n, int m) {
	bool** D = new bool* [n+1];
	if (n >= m + 1) {
		return true;
	}
	for (int i = 0; i <= n; i++) {
		D[i] = new bool[m];
	}

	for (int j = 0; j < m; j++) {
		D[0][j] = false;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			int prev_rest = j - A[i - 1];
			if (prev_rest < 0) {
				int tmp = prev_rest / m;
				tmp *= -1;
				tmp++;
				prev_rest = prev_rest + (tmp * m);
			}
			prev_rest = prev_rest % m;
			D[i][j] = (D[i - 1][j] || D[i - 1][prev_rest]);
		}
		D[i][A[i - 1] % m] = true;
		if (D[i][0]) {
			return true;
		}
	}
	return D[n][0];
}

int main_sdnkchs() {
	int n, m;
	cin >> n;
	cin >> m;
	int* tab = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> tab[i];
	}
	bool result = subsequence_exist(tab, n, m);
	if (result) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	return 0;
}