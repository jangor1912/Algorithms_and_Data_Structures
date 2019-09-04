#include <iostream>
using namespace std;

long long vasya_eats(long long& candies, long long k) {
	if (candies < k) {
		long long eaten = candies;
		candies = 0;
		return eaten;
	}
	candies = candies - k;
	return k;
}

long long petya_eats(long long& candies) {
	long long tmp = candies / 10;
	candies = candies - tmp;
	return tmp;
}

long long count_eaten_by_vasya(long long candies, long long k) {
	long long candies_eaten = 0;
	while (candies != 0) {
		candies_eaten += vasya_eats(candies, k);
		petya_eats(candies);
	}
	return candies_eaten;
}

long long lowerbound(long long l, long long r, long long candies) {
	long long k, result;
	long long half_candies = (candies+1) / 2;
	while (l != r) {
		k = (l + r) / 2;
		result = count_eaten_by_vasya(candies, k);
		if (result < half_candies) {
			l = k + 1;
		}
		else {
			r = k;
		}
	}
	return l;
}

long long count_minimal_k(long long candies) {
	long long min_k = 1;
	long long max_k = candies / 2;
	if (candies < 2) {
		max_k = 1;
	}
	return lowerbound(min_k, max_k, candies);
}

void test4() {
	long long input, expected_output, output;
	input = 68;
	expected_output = 3;
	output = count_minimal_k(input);
	if (expected_output != output) {
		cout << "Error!\n";
		return;
	}
	cout << "Success!\n";
}

void test1() {
	long long input, expected_output, output;
	input = 43;
	expected_output = 2;
	output = count_minimal_k(input);
	if (expected_output != output) {
		cout << "Error!\n";
		return;
	}
	cout << "Success!\n";
}

void test2() {
	long long input, expected_output, output;
	input = 756;
	expected_output = 29;
	output = count_minimal_k(input);
	if (expected_output != output) {
		cout << "Error!\nOutput = " << output << ", Expected="<< expected_output <<"\n";
		return;
	}
	cout << "Success!\n";
}

void test3() {
	long long input, expected_output, output;
	input = 1000000000000000000ll;
	expected_output = 29965969;
	output = count_minimal_k(input);
	if (expected_output != output) {
		cout << "Error!\nOutput = " << output << ", Expected=" << expected_output << "\n";
		return;
	}
	cout << "Success!\n";
}

void test() {
	test1();
	test2();
	test3();
	test4();
}

int not_main3() {
	long long candies, result;
	//cin >> candies;
	//result = count_minimal_k(candies);
	//cout << result;
	test();
	return 0;
}


