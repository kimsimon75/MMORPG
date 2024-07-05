
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <math.h>

int precedence(char ch);

// 스택 구조체 정의
typedef struct {
	int top;
	char items[50];
	double double_items[50];
} Stack;

// 스택 초기화
void initStack(Stack* s);

// 스택이 비어있는지 확인
int isEmpty(Stack* s);

// 스택이 가득 찼는지 확인
int isFull(Stack* s);

// 스택에 푸시 (문자)
void push_char(Stack* s, char item);

// 스택에 푸시 (정수)
void push_double(Stack* s, double item);

// 스택에서 팝 (문자)
char pop_char(Stack* s);

// 스택에서 팝 (정수)
double pop_double(Stack* s);

// 스택의 최상위 항목을 반환 (문자)
char peek(Stack* s);

// 중위 표기법을 후위 표기법으로 변환
void infixToPostfix(char* infix, char* postfix);

// 후위 표기법을 계산
int calculate(char* postfix);

const char* Calculate(const char* string);

