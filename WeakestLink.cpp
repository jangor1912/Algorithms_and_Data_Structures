#include <iostream>
using namespace std;

long long max3(long long val1, long long val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

long long min3(long long val1, long long val2) {
	if (val1 < val2) {
		return val1;
	}
	return val2;
}

int* count_prev_array(int* A, int n) {
	int* prev = new int[n];
	prev[0] = -1;
	for (int i = 1; i < n; i++) {
		int j = i - 1;
		while (j >= 0 && A[j] >= A[i]) {
			j = prev[j];
		}
		prev[i] = j;
	}
	return prev;
}

int* count_next_array(int* A, int n) {
	int* next = new int[n];
	next[n - 1] = n;
	for (int i = n - 2; i >= 0; i--) {
		int j = i + 1;
		while (j < n && A[j] >= A[i]) {
			j = next[j];
		}
		next[i] = j;
	}
	return next;
}

long long* get_prefix_sum_array(int* A, int n) {
	long long* P = new long long[n+1];
	P[0] = 0;
	for (int i = 1; i < n+1; i++) {
		P[i] = P[i - 1] + A[i-1];
	}
	return P;
}

long long get_strongest(int* A, long long n) {
	long long result = -1;
	int* prev = count_prev_array(A, n);
	int* next = count_next_array(A, n);
	long long* P = get_prefix_sum_array(A, n);
	for (int i = 0; i < n; i++) {
		long long cur_strength = (long long) P[next[i]] - P[prev[i]+1];
		if (cur_strength == 0) {
			cur_strength = (long long) A[i] * A[i];
		}
		else {
			cur_strength = (long long) cur_strength * A[i];
		}

		if (cur_strength > result) {
			result = cur_strength;
		}
	}
	return result;
	/*long long min = A[0];
	long long size = n;
	long long** D = new long long*[n];
	for (long long i = 0; i < n; i++) {
		D[i] = new long long[size];
	}
	D[0][0] = D[0][1] = A[0] * A[0];
	long long result = D[0][0];
	for (long long i = 1; i < n; i++) {
		// don't take the previous
		D[i][0] = A[i] * A[i];
		result = max3(result, D[i][0]);
		//take the best previous
		long long team_min = min3(min, A[i]);
		long long team_strength = ((D[i - 1][1] / min) + A[i]) * team_min;

		long long individual_min = min3(A[i], A[i-1]);
		long long individual_strength = ((D[i - 1][0] / A[i-1]) + A[i]) * individual_min;

		if (team_strength >= individual_strength) {
			D[i][1] = team_strength;
			min = team_min;
		}
		else {
			D[i][1] = individual_strength;
			min = individual_min;
		}
		result = max3(result, D[i][1]);
	}
	for (long long i = 0; i < n; i++) {
		delete D[i];
	}
	delete D;*/
	/*for (int i = 0; i < n; i++) {
		D[i][0] = 0;
		if (i != 0) {
			D[0][i] = A[i]*A[i];
		}
	}
	long long result = D[0][0];
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			long long dont_take = D[i - 1][j];
			if()
		}
	}*/
	
	return result;
}



int main_akjsc() {
	int queries;
	cin >> queries;
	for (int i = 0; i < queries; i++) {
		int n;
		cin >> n;
		int* tab = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> tab[j];
		}
		long long strongest = get_strongest(tab, n);
		cout << "Testcase#" << i << ": " << strongest << "\n";
		delete[] tab;
	}
	return 0;
}