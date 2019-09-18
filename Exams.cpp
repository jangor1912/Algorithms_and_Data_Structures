#include <iostream>
using namespace std;

int max9(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

int main_nsjdbvhj() {
	int n;
	cin >> n;
	int** exams = new int*[n];
	int last_exam = 0;
	for (int i = 0; i < n; i++) {
		exams[i] = new int[2];
		int first_term, second_term;
		cin >> first_term;
		cin >> second_term;
		exams[i][0] = first_term-1;
		exams[i][1] = second_term-1;
		last_exam = max9(last_exam, second_term-1);
	}
	int** days = new int* [last_exam + 1];
	return 0;
}