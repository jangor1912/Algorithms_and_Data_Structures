#include <iostream>
using namespace std;

long long max1(long long val1, long long val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

long long sum_boost(long long* A, int l, int r) {
	long long result = 0;
	for (int i = l; i <= r; i++) {
		result = result + A[i];
	}
	return result;
}

long long countMaxLectures(long long* A, int* T, int n, int k) {
	long long* D = new long long[n];
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			D[i] = A[i] * T[i];
			continue;
		}
		D[i] = A[i] * T[i] + D[i - 1];
	}
	long long result = D[n - 1];
	for (int frame_start = 0; frame_start <= n - k; frame_start++) {
		int frame_end = frame_start + k-1;
		long long before, after;
		if (frame_start == 0) {
			before = 0;
		}
		else {
			before = D[frame_start - 1];
		}
		if (frame_end == n - 1) {
			after = 0;
		}
		else {
			after = D[n-1] - D[frame_end];
		}
		long long cur = before + sum_boost(A, frame_start, frame_end) + after;
		result = max1(result, cur);
	}
	return result;
}

int main_sbdhc() {
	int n, k;
	cin >> n;
	cin >> k;
	long long* A = new long long[n];
	int* T = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> T[i];
	}
	cout << countMaxLectures(A, T,n, k);
	return 0;
}