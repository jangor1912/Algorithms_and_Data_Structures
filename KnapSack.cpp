#include <iostream>
using namespace std;

struct Tuple {
	long long income;
	long long choosen_items_no;
	long long* choosen_items;
	Tuple(long long in, long long k, long long* tab) {
		income = in;
		choosen_items_no = k;
		choosen_items = tab;
	}
};

struct Feature {
	long long hours;
	long long price;
	Feature(long long h, long long c) {
		hours = h;
		price = c;
	}
};

long long max4(long long val1, long long val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

Tuple* knapsack(Feature** tab, int n, int time_left) {
	long long** D = new long long* [n+1];
	for (int i = 0; i < n+1; i++) {
		D[i] = new long long[time_left+1];
	}
	for (int i = 0; i < time_left+1; i++) {
		D[0][i] = 0;
	}
	for (int i = 1; i < n+1; i++) {
		for (int j = 0; j < time_left+1; j++) {
			long long dont_take = D[i - 1][j];
			long long take = -1;
			if (j >= tab[i-1]->hours) {
				take = D[i - 1][j - tab[i-1]->hours] + tab[i-1]->price;
			}
			D[i][j] = max4(take, dont_take);
		}
	}
	long long income = D[n][time_left];

	//get taken features
	int i = n;
	int j = time_left;
	int ind = 0;
	long long* Ans = new long long[n];
	while (i > 0 && j >= 0) {
		if (D[i][j] == D[i - 1][j]) { i--; }
		else {
			Ans[ind] = i;
			ind++;
			j = j - tab[i-1]->hours;
			i--;
		}
	}
	return new Tuple(income, ind, Ans);
}

int main_kjsdbvjhcjh() {
	int queries;
	cin >> queries;
	for (int i = 0; i < queries; i++) {
		int n;
		cin >> n;
		int time_left;
		cin >> time_left;
		Feature** tab = new Feature * [n];
		for (int j = 0; j < n; j++) {
			long long hours, price;
			cin >> hours;
			cin >> price;
			tab[j] = new Feature(hours, price);
		}
		Tuple* t = knapsack(tab, n, time_left);
		cout << "Testcase#" << i << ": " << t->income << "\n";
		cout << t->choosen_items_no << " ";
		for (int j = 0; j < t->choosen_items_no; j++) {
			cout << t->choosen_items[j] << " ";
		}
		delete tab;
	}
	return 0;
}