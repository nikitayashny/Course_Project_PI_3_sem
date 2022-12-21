#include "Div.h"
#include "Error.h"

char** divideText(char source[], int size)		// ������������ ������� �����, ���������� �� ������
{
	char** word = new char* [max_world];

	for (int i = 0; i < max_world; i++)
	{
		word[i] = new char[size_world] {NULL};
	}
		
	bool findSP, findLit = false;
	int j = 0;
	char SP[] = { " ,;(){}=+-*/|[]" };

	for (int i = 0, k = 0; i < size - 1; i++, k++)
	{
		findSP = false;

		if (source[i] == '\'')
		{
			findLit = !findLit;
		}
		if (source[i] == '0' && source[i - 1] == '-')
		{
			throw ERROR_THROW(300);
		}
		for (int t = 0; t < sizeof(SP) - 1; t++)
		{
			if (source[i] == '-' && source[i - 1] == '=')
			{
				break;
			}
			if (source[i] == SP[t] && !findLit)
			{
				findSP = true;

				if (word[j][0] != NULL) 
				{
					word[j++][k] = '\0';
					k = 0;
				}
				if (SP[t] == ' ') 
				{
					k = -1;
					break;
				}

				word[j][k++] = SP[t];
				word[j++][k] = '\0';
				k = -1;
				break;
			}
		}
		if (!findSP)
		{
			word[j][k] = source[i];
		}	
	}

	word[j] = NULL;

	for (int i = 0; i < j; i++)
	{
		if (!strcmp((char*)word[i], ""))
		{
			return NULL;
		}
	}		
	return word;
}