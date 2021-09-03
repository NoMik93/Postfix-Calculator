#include <iostream>
#include <stack>
#include <string>

using namespace std;

void input();
void toPostfix(string& x);
void postfixCalculate(string& x);

int main() {
	while (1)
		input();
}

void input() {
	string *x = new string [1], *tmp, buf;
	int num = 0;

	while (1) {
		getline(cin, buf);
		if (buf == "0")
			break;
		else if (num == 0) {
			x[num] = buf;
			num++;
		}
		else if (num != 0) {
			tmp = new string[num];
			for (int i = 0; i < num; i++)
				tmp[i] = x[i];
			delete[] x;
			x = new string[++num];
			for (int i = 0; i < num - 1; i++)
				x[i] = tmp[i];
			delete[] tmp;
			x[num - 1] = buf;
		}
		
	}
	if(num != 0)
		for (int i = 0; i < num; i++) {
			toPostfix(x[i]);
		}
}

void toPostfix(string& x) {
	stack <char> oper;
	string result;

	for (int i = 0; i < x.length(); i++) {
		if (isdigit(x[i])) {
			result = result + x[i];
			if (!isdigit(x[i + 1]))
				result = result + '.';
		}
		else if (x[i] == '(')
			oper.push(x[i]);
		else if (x[i] == '+' || x[i] == '-') {
				while (!oper.empty()) {
					if (oper.top() != '^' && oper.top() != '*' && oper.top() != '/' && oper.top() != '%' && oper.top() != '+' && oper.top() != '-')
						break;
					result = result + oper.top();
					oper.pop();
				}
			oper.push(x[i]);
		}
		else if (x[i] == '*' || x[i] == '/' || x[i] == '%') {
				while (!oper.empty()) {
					if (oper.top() != '^' && oper.top() != '*' && oper.top() != '/' && oper.top() != '%')
						break;
					result = result + oper.top();
					oper.pop();
				}
			oper.push(x[i]);
		}
		else if (x[i] == '^') {
				while (!oper.empty()) {
					if (oper.top() != '^')
						break;
					result = result + oper.top();
					oper.pop();
				}
			oper.push(x[i]);
		}
		else if (x[i] == ')') {
			if (!oper.empty())
				while (oper.top() != '(') {
					result = result + oper.top();
					oper.pop();
				}
			oper.pop();
		}
	}
	while (!oper.empty()) {
		result = result + oper.top();
		oper.pop();
	}
	postfixCalculate(result);
}

void postfixCalculate(string& x) {
	stack<int> integer;
	int i, j, tmp, n1, n2, length;
	char buf[10];
	j = 0;
	length = x.length();
	for (i = 0; i < length; i++) {
		if (isdigit(x[i]))
			buf[j++] = x[i];
		else if (x[i] == '.') {
			if (j != 0) {
				buf[j] = '\n';
				tmp = atoi(buf);
				integer.push(tmp);
				j = 0;
			}
		}
		else if (x[i] == '^' || x[i] == '*' || x[i] == '/' || x[i] == '%' || x[i] == '+' || x[i] == '-') {
			if (!integer.empty()) {
				n2 = integer.top();
				integer.pop();
			}
			if (!integer.empty()) {
				n1 = integer.top();
				integer.pop();
			}
			switch (x[i]) {
			case '^':
				tmp = n1;
				for (int i = 0; i < n2 - 1; i++) {
					n1 = n1 * tmp;
				}
				integer.push(n1);
				break;
			case '*':
				n1 = n1 * n2;
				integer.push(n1);
				break;
			case '/':
				if (n2 == 0) {
					cout << "Error!" << endl;
					return;
				}
				n1 = n1 / n2;
				integer.push(n1);
				break;
			case '%':
				if (n2 == 0) {
					cout << "Error!" << endl;
					return;
				}
				n1 = n1 % n2;
				integer.push(n1);
				break;
			case '+':
				n1 = n1 + n2;
				integer.push(n1);
				break;
			case '-':
				n1 = n1 - n2;
				integer.push(n1);
				break;
			}
		}
	}
	cout << integer.top() << endl;
}