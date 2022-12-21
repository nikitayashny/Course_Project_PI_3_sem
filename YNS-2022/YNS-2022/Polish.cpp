#include "stdafx.h"
#include "LexAn.h"
#include <stack>
#include <queue>

using namespace std;

bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;		// ���� ��� ��������
	queue<LT::Entry> queue;		// ������� ��� ���������
	LT::Entry temp;				// ����������� �������
	temp.idxTI = -1;
	temp.lexema = ' ';
	temp.sn = -1;
	LT::Entry func;
	func.lexema = '^';
	LT::Entry num;
	num.lexema = ' ';
	int countLex = 0;			// ���������� ��������������� ������
	int posLex = i;				// ���������� ����� ������� ����� ���������������
	bool findFunc = false;
	int buf = 0;

	for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lex.lextable.table[i].lexema)
		{
		case LEX_ID:	// ���� �������������
		{
			queue.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:		// ���� �������
		{
			queue.push(lex.lextable.table[i]);	//� �������
			continue;
		}
		case LEX_COMMA:
		{
			if (findFunc)
				stack.push(lex.lextable.table[i]);
		}
		case LEX_LEFTTHESIS:		// ���� (
		{
			if (lex.lextable.table[i - 1].lexema == LEX_ID)
			{
				if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::F || lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::SF || lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::SFL) {
					findFunc = true;
					num.lexema = (char)lex.idtable.table[lex.lextable.table[i - 1].idxTI].countOfPar + '0';
				}
			}
			if (findFunc)
				queue.push(lex.lextable.table[i]);
			else
				stack.push(lex.lextable.table[i]); //� ����

			continue;
		}
		case LEX_RIGHTTHESIS:	// ���� )
		{
			if (findFunc)
				queue.push(lex.lextable.table[i]);
			else {
				while (stack.top().lexema != LEX_LEFTTHESIS)	// ���� �� �������� (
				{
					queue.push(stack.top());	//�� ����� � �������
					stack.pop();
					if (stack.empty())
						return false;
				}
				stack.pop();	// ���������� (
			}
			continue;
		}
		case LEX_PLUS: case LEX_MINUS: case LEX_STAR: case LEX_DIRSLASH: case LEX_MOD:	// ���� ���� ���������
		{
			while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// ���� ��������� �������� ��������� 																					//������ ��� ����� ���������� ��������� � ������� �����
			{
				queue.push(stack.top());	// ����������� �� ����� � �������� ������
				stack.pop();
			}
			stack.push(lex.lextable.table[i]);
			continue;
		}
		}
	}
	while (!stack.empty())	// ���� ���� �� ������
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());	// ����������� ��� � �������
		stack.pop();
	}
	while (countLex != 0)		// ������ �������� ��������� � ������� ������ �� ��������� � �����
	{
		if (!queue.empty()) {
			lex.lextable.table[posLex++] = queue.front();
			queue.pop();
		}
		else
		{
			lex.lextable.table[posLex++] = temp;
		}
		countLex--;
	}

	for (int i = 0; i < posLex; i++)		// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
	{
		if (lex.lextable.table[i].lexema == LEX_PLUS || lex.lextable.table[i].lexema == LEX_MINUS || lex.lextable.table[i].lexema == LEX_STAR || lex.lextable.table[i].lexema == LEX_DIRSLASH || lex.lextable.table[i].lexema == LEX_LITERAL)
			lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}
void PolishStart(Lex::LEX lex)
{
	for (int i = 0; i < lex.lextable.size; i++)
	{
		if (lex.lextable.table[i].lexema == '=')
		{
			PolishNotation(i + 1, lex);
		}
	}
}