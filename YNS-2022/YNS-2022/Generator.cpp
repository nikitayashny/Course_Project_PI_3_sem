#include "Generator.h"
#include "Parm.h"
#include "LexAn.h"
#include "IT.h"
#include "LT.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>

using namespace std;

static int statenum = 0;

string itoS(int x) 
{ 
	stringstream r; 
	r << x; 
	return r.str(); 
}

string genCallFunctionCode(Lex::LEX& tables, int i)
{
	string str;

	IT::Entry e = ITENTRY(i);		// ������������� ���������� �������
	stack <IT::Entry> temp;
	bool stnd = (e.idtype == IT::IDTYPE::SF || e.idtype == IT::IDTYPE::SFL);

	for (int j = i + 1; LEXEMA(j) != (LEX_RIGHTTHESIS); j++)
	{
		if (LEXEMA(j) == LEX_ID || LEXEMA(j) == LEX_LITERAL)
		{
			temp.push(ITENTRY(j));	// ��������� ���� � ������ �������	
		}
	}

	str += "\n";

	while (!temp.empty())			// ������������ ����		
	{
		if (temp.top().idtype == IT::IDTYPE::L && temp.top().iddatatype == IT::IDDATATYPE::STR)
		{
			str = str + "push offset " + temp.top().id + "\n";
		}
		else
		{
			str = str + "push " + temp.top().id + "\n";
		}
		temp.pop();
	}

	str = str + "call  " + string(e.id) + IN_CODE_ENDL;
	return str;
}

string genStateCode(Lex::LEX& tables, int i, string& cyclecode)
{
	string str;
	statenum++;
	cyclecode.clear();
	IT::Entry lft = ITENTRY(i + 1); // ����� �������
	IT::Entry rgt = ITENTRY(i + 3); // ������ �������
	bool w = false, r = false, c = false;
	string wstr, rstr;

	for (int j = i + 5; LEXEMA(j) != LEX_LOGSEP; j++) // ���������� ����������� �������
	{
		if (LEXEMA(j) == LEX_PERFORM)
		{
			c = true;
		}
	}

	str = str + "mov edx, " + lft.id + "\ncmp edx, " + rgt.id + "\n";
	switch (LEXEMA(i + 2))
	{
	case LEX_MORE:  rstr = "jg";  wstr = "jl";  break;
	case LEX_LESS:   rstr = "jl";  wstr = "jg";  break;
	case LEX_NOT:   rstr = "jnz";  wstr = "jz";  break;
	}

	if (!c && r)
	{
		str = str + "\n" + rstr + " right" + itoS(statenum);
	}
	if (!c && w)
	{
		str = str + "\n" + wstr + " wrong" + itoS(statenum);
	}
	if (c)
	{
		str = str + "\n" + rstr + " repeat" + itoS(statenum);
		cyclecode = str;
		str = str + "\njmp repeatnext" + itoS(statenum);
	}
	else if (!r || !w)
	{
		str = str + "\njmp next" + itoS(statenum);
	}
	return str;
}

vector <string> startFillVector(Lex::LEX& tables)
{
	vector<string> v;
	v.push_back(BEGIN);
	string str = __FILE__;
	string str2 = str.erase(str.length() - 22, 22);
	string str3 = "Generation\\Debug\\GenLib.lib";
	str2.append(str3);
	string str4 = "includelib \"" + str2;
	v.push_back(str4);
	v.push_back(EXTERN);

	vector<string> vlt; vlt.push_back(CONST);
	vector<string> vid; vid.push_back(DATA);

	for (int i = 0; i < tables.idtable.size; i++)				//���������� ��������� 
	{
		IT::Entry e = tables.idtable.table[i];
		string str = "\t\t" + string(e.id);

		if (tables.idtable.table[i].idtype == IT::IDTYPE::L)
		{
			switch (e.iddatatype)
			{
			case IT::IDDATATYPE::SHINT:  str = str + " sdword " + itoS(e.value.vint);  break;
			case IT::IDDATATYPE::STR:  str = str + " byte '" + string(e.value.vstr.str) + "', 0";  break;
			}
			vlt.push_back(str);
		}
		else if (tables.idtable.table[i].idtype == IT::IDTYPE::V)
		{
			switch (e.iddatatype)
			{
			case IT::IDDATATYPE::SHINT: str = str + " sdword 0";  break;				//���� ��������
			case IT::IDDATATYPE::STR: str = str + " dword ?";  break;				//���� ������
			}
			vid.push_back(str);
		}
	}
	v.insert(v.end(), vlt.begin(), vlt.end());
	v.insert(v.end(), vid.begin(), vid.end());
	v.push_back(CODE);
	return v;
}
string genFunctionCode(Lex::LEX& tables, int i, string funcname, int pcount)
{
	string str;
	IT::Entry e = ITENTRY(i + 1);
	IT::IDDATATYPE type = e.iddatatype;

	str = SEPSTR(funcname) + string(e.id) + string(" PROC,\n\t");
	//������ ���������
	int j = i + 3; // ������ - �� ��� ����� ����� ����������� ������
	while (LEXEMA(j) != LEX_RIGHTTHESIS) // ���� ��������� �� ��������
	{
		if (LEXEMA(j) == LEX_ID) // ��������
		{
			str = str + string(ITENTRY(j).id) + (ITENTRY(j).iddatatype == IT::IDDATATYPE::SHINT ? " : sdword, " : " : dword, ");
		}
		j++;
	}
	int f = str.rfind(',');
	if (f > 0)
	{
		str[f] = IN_CODE_SPACE;
	}

	str += "\npush ebx\npush edx\n";

	return str;
}

string genExitCode(Lex::LEX& tables, int i, string funcname, int pcount)		//��������� ���� ������
{
	string str = "\npop edx\npop ebx\n";
	if (LEXEMA(i + 1) != LEX_SEMICOLON)	// ����� �� ������� (������� ��������)
	{
		str = str + "mov eax, " + string(ITENTRY(i + 1).id) + "\n";
	}
	str += "ret\n";
	str += funcname + " ENDP" + SEPSTREMP;
	return str;
}

string genEqualCode(Lex::LEX& tables, int i)
{
	string str;
	IT::Entry e1 = ITENTRY(i - 1); // ����� �������

	switch (e1.iddatatype)
	{
	case IT::IDDATATYPE::SHINT:
	{
		bool first = true;
		for (int j = i + 1; LEXEMA(j) != LEX_SEMICOLON; j++)
		{
			switch (LEXEMA(j))
			{
			case LEX_LITERAL:
			case LEX_ID:
			{
				if (ITENTRY(j).idtype == IT::IDTYPE::F || ITENTRY(j).idtype == IT::IDTYPE::SF) // ���� � ��������� ����� �������
				{
					str = str + genCallFunctionCode(tables, j); // ������� ���������� ��������� � eax
					str = str + "push eax\n";					// ��������� ��������� � ���� ��� ����������� ���������� ���������
					while (LEXEMA(j) != LEX_RIGHTTHESIS) j++;
					break;
				}
				else  str = str + "push " + ITENTRY(j).id + "\n";
				break;
			}
			case LEX_PLUS:
				str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\n"; break;
			case LEX_MINUS:
				str = str + "pop ebx\npop eax\nsub eax, ebx\npush eax\n"; break;
			case LEX_STAR:
				str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\n"; break;
			case LEX_DIRSLASH:
				str = str + "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"; break;
			case LEX_MOD:
				str = str + "pop ebx \npop eax\ncdq\nidiv ebx\npush edx\n"; break;
			}
		} // ���� ����������

		str = str + "\npop ebx\nmov " + e1.id + ", ebx\n";			// ����������� ��������� � ebx 
		break;
	}
	case IT::IDDATATYPE::STR:// ��������� ����������� ������� ������ ������, �������� � ������ �������
	{
		char lex = LEXEMA(i + 1);
		IT::Entry e2 = ITENTRY(i + 1);
		if (lex == LEX_ID && e2.idtype == IT::IDTYPE::F || e2.idtype == IT::IDTYPE::SFL) // ����� �������
		{
			str += genCallFunctionCode(tables, i + 1);
			str = str + "mov " + e1.id + ", eax";
		}
		else if (lex == LEX_LITERAL) // �������
		{
			str = str + "mov " + e1.id + ", offset " + e2.id;
		}
		else // ��(����������) - ����� �������
		{
			str = str + "mov ecx, " + e2.id + "\nmov " + e1.id + ", ecx";
		}
	}
	}

	return str;
}
namespace Gen
{
	void CodeGeneration(Lex::LEX& tables)
	{
		vector<string> v = startFillVector(tables);
		ofstream ofile("C:\\Users\\User\\Desktop\\������\\YNS-2022\\Generation\\Generation\\Gen.asm");
		string funcname;	// ��� ������� �������
		string cyclecode;	// ������ �����: cmp + j
		int pcount;			// ���������� ���������� ������� �������
		int pos, parcol;
		string str;
		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (LEXEMA(i))
			{
			case LEX_MAIN:
			{
				str = str + SEPSTR("MAIN") + "main PROC";
				break;
			}
			case LEX_FUNCTION:
			{
				funcname = ITENTRY(i + 1).id;
				pcount = ITENTRY(i + 1).countOfPar;
				str = genFunctionCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_RETURN:
			{
				str = genExitCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_EQUAL: // ������������ (���������� ���������)
			{
				str = genEqualCode(tables, i);
				while (LEXEMA(++i) != LEX_SEMICOLON);	// ���������� ���������
				break;
			}
			case LEX_FOR: // �������
			{
				str = genStateCode(tables, i, cyclecode);
				break;
			}
			case LEX_LOGSEP:		// ����� � ����� ������ ��� ����� 
			{
				if (LEXEMA(i - 1) == LEX_BRACELET) //   ]#
				{
					bool c = false;
					for (int j = i; j > 0 && LEXEMA(j) != LEX_FOR; j--)
						if (LEXEMA(j) == LEX_PERFORM)
							c = true;
					if (c)
						str = cyclecode + "\nrepeatnext" + itoS(statenum) + ":";
					else  str += "next" + itoS(statenum) + ':';
				}
				break;
			}
			case LEX_NEWLINE:
			{
				str = str + "push offset printline\ncall outstr\n";
				break;
			}
			case LEX_OUT: // �����
			{
				IT::Entry e = ITENTRY(i + 1);
				switch (e.iddatatype)
				{
				case IT::IDDATATYPE::SHINT:
					str = str + "\npush " + e.id + "\ncall outnum\n";
					break;
				case IT::IDDATATYPE::STR:
					if (e.idtype == IT::IDTYPE::L)  str = str + "\npush offset " + e.id + "\ncall outstr\n";
					else  str = str + "\npush " + e.id + "\ncall outstr\n";
					break;
				}
				str = str + "\n";
				break;
			}
			case LEX_PERFORM: // ���� � �������� (�����)
			{
				str = str + "repeat" + itoS(statenum) + ":";
				break;
			}
			case LEX_ID:
			{
				if (LEXEMA(i + 1) == LEX_LEFTTHESIS && LEXEMA(i - 1) != LEX_FUNCTION) // �� ����������, � �����
					str = genCallFunctionCode(tables, i);
				break;
			}
			}
			if (!str.empty())
				v.push_back(str);
			str.clear();
		}
		v.push_back(END);
		for (auto x : v)
		{
			ofile << x << endl;
		}
	}
}

