#include <iostream>
#define MAX_VAL 100003
using namespace std;

int main_shdhhsdbcuyh() {
	int n, m;
	cin >> n;
	cin >> m;
	int* A = new int[n];
	int* cache = new int[n];
	bool* tmp = new bool[MAX_VAL];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < MAX_VAL; i++) {
		tmp[i] = false;
	}

	cache[n - 1] = 1;
	tmp[A[n - 1]] = true;
	for (int i = n - 2; i >= 0; i--) {
		if (tmp[A[i]]) {
			cache[i] = cache[i + 1];
		}
		else {
			cache[i] = cache[i + 1] + 1;
			tmp[A[i]] = true;
		}
	}

	for (int i = 0; i < m; i++) {
		int cur_index;
		cin >> cur_index;
		cur_index--;
		int result = cache[cur_index];
		cout <<result << "\n";
	}
	return 0;
}