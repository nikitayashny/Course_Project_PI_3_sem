#include<iostream>

extern "C"
{
	int __stdcall outnum(int value)
	{
		std::cout << value;
		return 0;
	}

	int __stdcall outstr(char* ptr)
	{
		setlocale(LC_ALL, "RUSSIAN");
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
		{
			std::cout << ptr[i];
		}
		return 0;
	}

	int _stdcall LineLen(char* ptr)
	{
		int len = 0;
		if (ptr == nullptr)
		{
			return 0;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
		{
			len += 1;
		}
		return len;
	}

	void _stdcall CopyLine(char* str1, char* str2)
	{	
		outstr(str1); outstr(str2);
	}
}