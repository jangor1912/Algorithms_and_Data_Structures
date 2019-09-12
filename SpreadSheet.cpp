#include <iostream>
using namespace std;

int max6(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

void count_sorted(int** A, int n, int m, int** sorted, int* super_sorted) {
	for (int j = 0; j < m; j++) {
		sorted[n - 1][j] = n - 1;
		for (int i = n - 2; i >= 0; i--) {
			if (A[i + 1][j] < A[i][j]) {
				sorted[i][j] = i;
			}
			else {
				sorted[i][j] = sorted[i + 1][j];
			}
		}
	}
	
	for (int i = 0; i < n-1; i++) {
		int max_i = i;
		for (int j = 0; j < m; j++) {
			max_i = max6(max_i, sorted[i][j]);
		}
		super_sorted[i] = max_i;
	}
	super_sorted[n - 1] = n - 1;

}

int main() {
	int n, m;
	cin >> n;
	cin >> m;
	int** sheet = new int* [n];
	int** sorted = new int* [n];
	int* super_sorted = new int[n];
	for (int i = 0; i < n; i++) {
		sheet[i] = new int[m];
		sorted[i] = new int[m];
		super_sorted[i] = i;
		for (int j = 0; j < m; j++) {
			cin >> sheet[i][j];
		}
	}
	count_sorted(sheet, n, m, sorted, super_sorted);
	int queries;
	cin >> queries;
	for (int q = 0; q < queries; q++) {
		int l, r;
		cin >> l;
		cin >> r;
		l = l - 1;
		r = r - 1;
		bool exists = false;
		if (super_sorted[l] >= r) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}

	return 0;
}