#include <iostream>
#define MAX_BRACKET_SIZE 300001
using namespace std;

struct Node {
	char value;
	Node* next=nullptr;
	Node* prev = nullptr;
	Node(char val) {
		value = val;
	}
};

struct Stack {
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;

	~Stack() {
		while (!empty()) {
			pop();
		}
	}
	void push_front(char val) {
		Node* new_node = new Node(val);
		size++;
		if (head == nullptr) {
			head = new_node;
			tail = new_node;
			return;
		}
		head->prev = new_node;
		new_node->next = head;
		head = new_node;
	}

	void push(char val) {
		Node* new_node = new Node(val);
		size++;
		if (head == nullptr) {
			head = new_node;
			tail = new_node;
			return;
		}
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}

	char pop() {
		// Assumption - stack is not empty
		Node* node = tail;
		char result = tail->value;
		size--;
		tail = tail->prev;
		delete node;
		if (tail == nullptr) {
			head = nullptr;
		}
		else {
			tail->next = nullptr;
		}
		return result;
	}

	bool empty() {
		return tail == nullptr;
	}

	char top() {
		//Assumption - stack is not empty
		return tail->value;
	}
	char bottom() {
		//Assumption - stack is not empty
		return head->value;
	}

	void copy(Stack* new_stack) {
		if (!empty()) {
			char cur_val = pop();
			new_stack->push_front(cur_val);
			copy(new_stack);
			push(cur_val);
		}
	}

};

void push_bracket(Stack* stack, char bracket) {
	if (!stack->empty()) {
		char stack_bracket = stack->top();
		if (stack_bracket == '(' && bracket == ')') {
			stack->pop();
			return;
		}
	}
	stack->push(bracket);
}

Stack* create_stack(char* brackets) {
	Stack* stack = new Stack();
	int bracket_dif = 0;
	int i = 0;
	while (brackets[i] != '\0') {
		push_bracket(stack, brackets[i]);
		i++;
	}
	return stack;
}
int count_bracket_diff(Stack* stack){
	int bracket_diff = 0;
	char bracket;
	while (!stack->empty()) {
		bracket = stack->pop();
		if (bracket == '(') {
			if (bracket_diff < 0) {
				return INT_MIN;
			}
			bracket_diff++;
		}
		else {
			if (bracket_diff > 0) {
				return INT_MIN;
			}
			bracket_diff--;
		}
	}
	return bracket_diff;
}


int main_sdcndj() {
	int brackets_no;
	cin >> brackets_no;
	long long* front_brackets = (long long*)calloc(MAX_BRACKET_SIZE, sizeof(long long));
	long long* end_brackets = (long long*)calloc(MAX_BRACKET_SIZE, sizeof(long long));
	int result;
	int max_brackets_front = 0;
	int max_brackets_end = 0;
	for (int i = 0; i < brackets_no; i++) {
		char* cur_bracket = new char[MAX_BRACKET_SIZE];
		cin >> cur_bracket;
		Stack* stack = create_stack(cur_bracket);
		if (stack->empty()) {
			front_brackets[0]++;
			end_brackets[0]++;
		}
		else {
			if (stack->bottom() == '(') {
				result = count_bracket_diff(stack);
				if (result != INT_MIN) {
					front_brackets[result]++;
					if (result > max_brackets_front) {
						max_brackets_front = result;
					}
				}
			}
			else {
				if (stack->bottom() == ')') {
					result = count_bracket_diff(stack);
					if (result != INT_MIN) {
						result *= -1;
						end_brackets[result]++;
						if (result > max_brackets_end) {
							max_brackets_end = result;
						}
					}
				}
			}
		}
		delete cur_bracket;
		delete stack;
	}

	long long correct_pairs = 0;
	long long first, second;
	int max_brackets;
	if (max_brackets_front < max_brackets_end) {
		max_brackets = max_brackets_front;
	}
	else {
		max_brackets = max_brackets_end;
	}
	for (int i = 0; i <= max_brackets; i++) {
		first = front_brackets[i];
		second = end_brackets[i];
		if (first == 0 || second == 0) {
			continue;
		}
		correct_pairs += first * second;
	}
	cout << correct_pairs;
	return 0;
}