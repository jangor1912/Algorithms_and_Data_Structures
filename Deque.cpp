#include <iostream>
#define MAX_WORD_LENGTH 12
using namespace std;

struct Node {
	char* value;
	Node* next=nullptr;
	Node* prev=nullptr;
	Node(char* string) {
		value = string;
	}
};

struct Deque {
	Node* begin = nullptr;
	Node* end = nullptr;
	int size = 0;

	void pushFront(char* string) {
		Node* new_node = new Node(string);
		size++;
		if (begin == nullptr) {
			begin = new_node;
			end = new_node;
			return;
		}
		new_node->next = begin;
		begin->prev = new_node;
		begin = new_node;
	}

	char* popFront() {
		// Assumption - list is not empty
		Node* node = begin;
		size--;
		char* result = node->value;
		begin = begin->next;
		delete node;
		if (begin == nullptr) {
			end = nullptr;
		}
		else {
			begin->prev = nullptr;
		}
		return result;
	}

	void pushBack(char* string) {
		Node* new_node = new Node(string);
		size++;
		if (begin == nullptr) {
			begin = new_node;
			end = new_node;
			return;
		}
		new_node->prev = end;
		end->next = new_node;
		end = new_node;
	}

	char* popBack() {
		// Assumption - list is not empty
		Node* node = end;
		size--;
		char* result = node->value;
		end = end->prev;
		delete node;
		if (end == nullptr) {
			begin = nullptr;
		}
		else {
			end->next = nullptr;
		}
		return result;
	}

	char* front() {
		// Assumption - list is not empty
		return begin->value;
	}

	char* back() {
		// Assumption - list is not empty
		return end->value;
	}

	int getSize() {
		return size;
	}

	bool empty() {
		return begin == nullptr;
	}
};

bool str_equal(char* str1, const char* str2) {
	int i = 0;
	while (true) {
		if (str1[i] != str2[i]) {
			return false;
		}
		if (str1[i] == '\0') {
			return true;
		}
		i++;
	}
	return false;
}

void test_push_and_pop() {
	cout << "STARTING TEST: test_push_and_pop\n";
	Deque* list = new Deque();
	char string[MAX_WORD_LENGTH] = "lol";
	char* result;
	list->pushFront(string);
	result = list->popFront();
	if (str_equal(result, string)) {
		cout << "Success\n";
	}
	else {
		cout << "Failure!\n";
		cout << "\tResult should be: " << string << "\n";
		cout << "\tResult is: " << result << "\n";
	}
}

void test_push_push_and_pop_pop() {
	cout << "STARTING TEST: test_push_push_and_pop_pop\n";
	Deque* list = new Deque();
	char string[MAX_WORD_LENGTH] = "lol";
	char* result;
	list->pushFront(string);
	char new_string [MAX_WORD_LENGTH] = "lel";
	list->pushFront(new_string);
	list->popFront();
	result = list->popFront();
	if (str_equal(result, string)) {
		cout << "Success\n";
	}
	else {
		cout << "Failure!\n";
		cout << "\tResult should be: " << string << "\n";
		cout << "\tResult is: " << result << "\n";
	}
}

void test_stdin_stdout() {
	cout << "STARTING TEST: test_push_back_pop_back\n";
	
}

void test_skjdnjdsnh() {
	cout << "STARTING TEST: test_push_back_pop_back\n";
	Deque* list = new Deque();
	char string[MAX_WORD_LENGTH] = "lol";
	char* result;
	list->pushFront(string);
	char new_string[MAX_WORD_LENGTH] = "lel";
	list->pushBack(new_string);
	result = list->popBack();
	if (str_equal(result, new_string)) {
		cout << "Success\n";
	}
	else {
		cout << "Failure!\n";
		cout << "\tResult should be: " << new_string << "\n";
		cout << "\tResult is: " << result << "\n";
	}
}

void test_all4() {
	test_push_and_pop();
	test_push_push_and_pop_pop();
	//test_push_back_pop_back();
	test_stdin_stdout();
}

int main_dsjvgcyu() {
	test_all4();
	return 0;
}


int main_dbvjn() {
	int queries_no;
	cin >> queries_no;
	Deque* list = new Deque();
	for (int i = 0; i < queries_no; i++) {
		char* query = new char[MAX_WORD_LENGTH];
		char* string = new char[MAX_WORD_LENGTH];
		char* result = nullptr;
		cin >> query;
		if (str_equal(query, "PUSH_FRONT")) {
			cin >> string;
			list->pushFront(string);
		}
		else if (str_equal(query, "PUSH_BACK")) {
			cin >> string;
			list->pushBack(string);
		}
		else if (str_equal(query, "POLL_FRONT")) {
			result = list->popFront();
		}
		else if (str_equal(query, "POLL_BACK")) {
			result = list->popBack();
		}
		else if (str_equal(query, "FRONT")) {
			result = list->front();
		}
		else if (str_equal(query, "BACK")) {
			result = list->back();
		}
		else if (str_equal(query, "SIZE")) {
			int size = list->getSize();
			cout << "SIZE " << size <<"\n";
		}
		else if (str_equal(query, "EMPTY")) {
			if (list->empty()) {
				cout << "EMPTY true\n";
			}
			else {
				cout << "EMPTY false\n";
			}
		}
		if (result != nullptr) {
			cout << query << " " << result << "\n";
		}
	}
	return 0;
}