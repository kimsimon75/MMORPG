#include "Caculate.h"
#include <ctype.h>
#include "유닛메니저.h"

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
		return -1; // ')'의 경우 처리되지 않도록
	}
}

// 스택 초기화
void initStack(Stack* s) {
	s->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
	return s->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* s) {
	return s->top == 49;
}

// 스택에 푸시 (문자)
void push_char(Stack* s, char item) {
	if (!isFull(s)) {
		s->items[++(s->top)] = item;
	}
}

// 스택에 푸시 (정수)
void push_double(Stack* s, double item) {
	if (!isFull(s)) {
		s->double_items[++(s->top)] = item;
	}
}

// 스택에서 팝 (문자)
char pop_char(Stack* s) {
	if (!isEmpty(s)) {
		return s->items[(s->top)--];
	}
	return '\0';
}

// 스택에서 팝 (정수)
double pop_double(Stack* s) {
	if (!isEmpty(s)) {
		return s->double_items[(s->top)--];
	}
	return 0;
}

// 스택의 최상위 항목을 반환 (문자)
char peek(Stack* s) {
	if (!isEmpty(s)) {
		return s->items[s->top];
	}
	return '\0';
}

// 중위 표기법을 후위 표기법으로 변환
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
			pop_char(&s); // '(' 제거
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

	postfix[k - 1] = '\0'; // 마지막 공백을 널 문자로 대체
}

// 후위 표기법을 계산
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

	// 입력 문자열을 ch로 복사
	strcpy(ch, string);

	// 괄호가 균형을 이루는지 확인
	for (int i = 0; string[i]; i++)
	{
		if (string[i] == '(')
			count++;
		else if (string[i] == ')')
			count--;
		if (count < 0)
			break;
	}

	// 괄호가 균형을 이루지 않으면 오류 메시지 반환
	if (count != 0)
		return "식이 잘못되었습니다.";
	else
	{
		
		char* ptr = strtok(ch, " ");
		while (ptr != NULL)
		{
			strcat(ch2, ptr);
			ptr = strtok(NULL, " ");
		}

		// 특정 문자열을 해당 정수 값으로 치환
		// 예제 치환: "공격력"을 100으로 치환
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
