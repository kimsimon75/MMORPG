
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <math.h>

int precedence(char ch);

// ���� ����ü ����
typedef struct {
	int top;
	char items[50];
	double double_items[50];
} Stack;

// ���� �ʱ�ȭ
void initStack(Stack* s);

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* s);

// ������ ���� á���� Ȯ��
int isFull(Stack* s);

// ���ÿ� Ǫ�� (����)
void push_char(Stack* s, char item);

// ���ÿ� Ǫ�� (����)
void push_double(Stack* s, double item);

// ���ÿ��� �� (����)
char pop_char(Stack* s);

// ���ÿ��� �� (����)
double pop_double(Stack* s);

// ������ �ֻ��� �׸��� ��ȯ (����)
char peek(Stack* s);

// ���� ǥ����� ���� ǥ������� ��ȯ
void infixToPostfix(char* infix, char* postfix);

// ���� ǥ����� ���
int calculate(char* postfix);

const char* Calculate(const char* string);

