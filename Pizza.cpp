#include <iostream>
#define MAX_PIECES 2000
using namespace std;

int max5(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

int count_eaten(int* pizza, int n, int all_olives) {
	int** D = new int* [n];
	for (int i = 0; i < n; i++) {
		D[i] = new int[n];
		for (int j = 0; j < n; j++) {
			D[i][j] = INT_MIN;
		}
		D[i][i] = pizza[i];
	}
	for(int range = 1;range < n;range++){
		int i = 0;
		int j = range;
		while(i < n){
			// take slice from start
			int new_start = i + 1;
			if (new_start == n) {
				new_start = 0;
			}
			int take_start = pizza[i] - D[new_start][j];
			// take slice from end
			int new_end = j - 1;
			if (new_end < 0) {
				new_end = n - 1;
			}
			int take_end = pizza[j] - D[i][new_end];
			D[i][j] = max5(take_start, take_end);
			i++;
			j++;
			j = j % n;
		}
	}
	int result = INT_MIN;
	for (int i = 0; i < n; i++) {
		int end = i - 1;
		if (end < 0) {
			end = end + n;
		}
		end = end % n;
		result = max5(result, D[i][end]);
	}
	return (all_olives + result)/2;
}

int main_sbdjcb() {
	int queries;
	cin >> queries;
	for (int q = 0; q < queries; q++) {
		int n;
		cin >> n;
		int* pizza = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> pizza[i];
		}
		int all_olives = 0;
		for (int i = 0; i < n; i++) {
			all_olives += pizza[i];
		}
		int bob = count_eaten(pizza, n, all_olives);
		cout << bob << " " << all_olives - bob << "\n";
		delete[] pizza;
	}
	return 0;
}