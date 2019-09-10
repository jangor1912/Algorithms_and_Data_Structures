#include <iostream>
#define MAX_LENGTH 5003
using namespace std;

int max(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

int lcs(char* string1, char* string2) {
	int i, j;
	int** tab = new int* [MAX_LENGTH];
	for (i = -1; string1[i] != '\0'; i++) {
		tab[i] = new int[MAX_LENGTH];
		for (j = -1; string2[j] != '\0'; j++) {
			if (i == -1 || j == -1) {
				tab[i][j] = 0;
				continue;
			}
			int length = tab[i - 1][j];
			length = max(length, tab[i][j - 1]);
			if (string1[i] == string2[j]) {
				length = max(length, tab[i - 1][j - 1] + 1);
			}
			tab[i][j] = length;
		}
	}
	return tab[i-1][j-1];
}

int main_jdsbcbsd() {
	char* string1 = new char[MAX_LENGTH];
	char* string2 = new char[MAX_LENGTH];
	cin >> string1;
	cin >> string2;
	int length = lcs(string1, string2);
	cout << length;
	return 0;
}