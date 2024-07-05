#include "Caculate.h"
#include <ctype.h>
#include "���ָ޴���.h"

int precedence(char ch) {
	if (ch == '+' || ch == '-') {
		return 1;
	}
	else if (ch == '*' || ch == '/') {
		return 2;
	}
	else if (ch == '(') {
		return 0;
	}
	else {
		return -1; // ')'�� ��� ó������ �ʵ���
	}
}

// ���� �ʱ�ȭ
void initStack(Stack* s) {
	s->top = -1;
}

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* s) {
	return s->top == -1;
}

// ������ ���� á���� Ȯ��
int isFull(Stack* s) {
	return s->top == 49;
}

// ���ÿ� Ǫ�� (����)
void push_char(Stack* s, char item) {
	if (!isFull(s)) {
		s->items[++(s->top)] = item;
	}
}

// ���ÿ� Ǫ�� (����)
void push_double(Stack* s, double item) {
	if (!isFull(s)) {
		s->double_items[++(s->top)] = item;
	}
}

// ���ÿ��� �� (����)
char pop_char(Stack* s) {
	if (!isEmpty(s)) {
		return s->items[(s->top)--];
	}
	return '\0';
}

// ���ÿ��� �� (����)
double pop_double(Stack* s) {
	if (!isEmpty(s)) {
		return s->double_items[(s->top)--];
	}
	return 0;
}

// ������ �ֻ��� �׸��� ��ȯ (����)
char peek(Stack* s) {
	if (!isEmpty(s)) {
		return s->items[s->top];
	}
	return '\0';
}

// ���� ǥ����� ���� ǥ������� ��ȯ
void infixToPostfix(char* infix, char* postfix) {
	Stack s;
	initStack(&s);
	int k = 0;
	char ch;

	for (int i = 0; infix[i] != '\0'; i++) {
		ch = infix[i];

		if (isspace(ch)) continue;

		if (isdigit(ch)) {
			while (isdigit(infix[i])) {
				postfix[k++] = infix[i++];
			}
			postfix[k++] = ' ';
			i--;
		}
		else if (ch == '(') {
			push_char(&s, ch);
		}
		else if (ch == ')') {
			while (!isEmpty(&s) && peek(&s) != '(') {
				postfix[k++] = pop_char(&s);
				postfix[k++] = ' ';
			}
			pop_char(&s); // '(' ����
		}
		else {
			while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
				postfix[k++] = pop_char(&s);
				postfix[k++] = ' ';
			}
			push_char(&s, ch);
		}
	}

	while (!isEmpty(&s)) {
		postfix[k++] = pop_char(&s);
		postfix[k++] = ' ';
	}

	postfix[k - 1] = '\0'; // ������ ������ �� ���ڷ� ��ü
}

// ���� ǥ����� ���
int calculate(char* postfix) {
	Stack s;
	initStack(&s);
	char* token = strtok(postfix, " ");

	while (token != NULL) {
		if (isdigit(token[0])) {
			push_double(&s, atoi(token));
		}
		else {
			double b = pop_double(&s);
			double a = pop_double(&s);

			switch (token[0]) {
			case '+': push_double(&s, a + b); break;
			case '-': push_double(&s, a - b); break;
			case '*': push_double(&s, a * b); break;
			case '/': push_double(&s, a / b); break;
			}
		}
		token = strtok(NULL, " ");
	}

	return pop_double(&s);
}

void replaceString(char* source, const char* target, int value) {
	char buffer[150] = {};
	char* insert_point = &buffer[0];
	const char* tmp = source;
	size_t target_len = strlen(target);
	size_t buffer_len = 0;

	while (1) {
		const char* p = strstr(tmp, target);

		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		// Copy the part before the target
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		// Add the value
		insert_point += sprintf(insert_point, "%d", value);

		tmp = p + target_len;
	}

	strcpy(source, buffer);
}

const char* Calculate(const char* string)
{
	int count = 0;
	char ch[150] = {};
	char ch2[150] = {};
	char s1[150] = {};

	// �Է� ���ڿ��� ch�� ����
	strcpy(ch, string);

	// ��ȣ�� ������ �̷���� Ȯ��
	for (int i = 0; string[i]; i++)
	{
		if (string[i] == '(')
			count++;
		else if (string[i] == ')')
			count--;
		if (count < 0)
			break;
	}

	// ��ȣ�� ������ �̷��� ������ ���� �޽��� ��ȯ
	if (count != 0)
		return "���� �߸��Ǿ����ϴ�.";
	else
	{
		
		char* ptr = strtok(ch, " ");
		while (ptr != NULL)
		{
			strcat(ch2, ptr);
			ptr = strtok(NULL, " ");
		}

		// Ư�� ���ڿ��� �ش� ���� ������ ġȯ
		// ���� ġȯ: "���ݷ�"�� 100���� ġȯ
		for (int i = 0; i < 7; i++)
		{
			std::pair<const char*, int> p = UnitManager::Get()->returnPlayer().GetElement(i);
			replaceString(ch2, p.first, p.second);
		}

		char postfix[150];
		infixToPostfix(ch2, postfix);
		int a = calculate(postfix);
		sprintf(ch2, "%d", a);
		return ch2;
	}
}
