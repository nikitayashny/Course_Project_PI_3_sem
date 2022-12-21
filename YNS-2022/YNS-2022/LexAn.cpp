#include "stdafx.h"
#include "LexAn.h"
#include "Div.h"
#include "FST.h"
#include "Graphs.h"

#define DIV '|'
#define SPACE ' '
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'
#define EQUAL '='

using namespace std;

int DecimalTrnsl(char* word)
{
	char* pEnd = 0;
	char buf[15];
	int i, j;

	for (i = 1, j = 0; i < strlen(word); i++, j++)
	{
		buf[j] = word[i];
	}


	buf[j + 1] = '\0';
	return strtol(buf, &pEnd, 16);
}

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		char** word = new char* [max_world];

		for (int i = 0; i < max_world; i++)
		{
			word[i] = new char[size_world] {NULL};
		}

		do 
		{
			word = divideText(in.text, in.size);
		} while (word == NULL);

		int indxLex = 0;
		int indexID = 0;
		int clit = 1;
		int line = 1;
		int position = 0;

		bool findMain = false;
		int countMain = 0;
		bool findDec = false;
		bool findType = false;
		int bufPos = 0;

		char emptystr[] = "";
		char* prefix = new char[10]{ "" };
		char* bufprefix = new char[10]{ "" };
		char* oldprefix = new char[10]{ "" };
		char* L = new char[2]{ "L" };
		char* bufL = new char[TI_STR_MAXSIZE];
		char* nameLiteral = new char[10]{ "" };
		char* charclit = new char[10]{ "" };

		bool findFunc = false;
		bool findParm = false;

		IT::Entry entryIT;

		for (int i = 0; word[i] != NULL; i++, indxLex++)
		{
			bool findSameID = false;

			FST::FST fstCopyLine(word[i], FST_COPYLINE);
			FST::FST fstLineLen(word[i], FST_LINELEN);

			if (FST::execute(fstLineLen))	
			{
				findFunc = true;
				if (findFunc)
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}

					strcpy(bufprefix, prefix);
					word[i] = strcat(bufprefix, word[i]);
					idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
				}

				LT::Entry entryLT = writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);

				findDec = false;
				entryIT.idtype = IT::SF;
				entryIT.idxfirstLE = indxLex;
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				findFunc = false;
				findType = false;
				continue;
			}

			if (FST::execute(fstCopyLine))	
			{
				findFunc = true;
				if (findFunc)
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}

					strcpy(bufprefix, prefix);
					word[i] = strcat(bufprefix, word[i]);
					idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
				}

				LT::Entry entryLT = writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);

				findDec = false;
				entryIT.idtype = IT::SFL;
				entryIT.idxfirstLE = indxLex;
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				findFunc = false;
				findType = false;
				continue;
			}





			FST::FST fstDeclare(word[i], FST_NEW);
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NEW, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDec = true;
				continue;
			}

			FST::FST fstCycle(word[i], FST_PERFORM);
			if (FST::execute(fstCycle))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_PERFORM, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstCondition(word[i], FST_FOR);
			if (FST::execute(fstCondition))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_FOR, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLogSep(word[i], FST_LOGSEP);
			if (FST::execute(fstLogSep))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LOGSEP, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstTypeInteger(word[i], FST_SHINT);
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_SHINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::SHINT;
				continue;
			}

			FST::FST fstTypeString(word[i], FST_LINE);
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LINE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::STR;
				strcpy(entryIT.value.vstr.str, emptystr);
				continue;
			}

			FST::FST fstFunction(word[i], FST_FUNCTION);
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::F;
				findFunc = true;
				continue;
			}

			FST::FST fstReturn(word[i], FST_RETURN);
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstPrint(word[i], FST_PRINT);
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_OUT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstPrintline(word[i], FST_NEWLINE);
			if (FST::execute(fstPrintline))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NEWLINE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstMain(word[i], FST_MAIN);
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				strcpy(oldprefix, prefix);
				strcpy(prefix, word[i]);
				strcpy(entryIT.visibility, emptystr);
				findMain = true;
				countMain++;
				continue;
			}

			FST::FST fstIdentif(word[i], FST_ID);
			if (FST::execute(fstIdentif))
			{

				if (findFunc)
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						if (!strcmp(word[i - 1], "function"))
						{
							throw ERROR_THROW_IN(305, line, position);
						}

						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsId(idtable, word[i]);

					if (idx == TI_NULLIDX && findDec == true && findType == false)
					{
						throw ERROR_THROW_IN(303, line, position);
					}
					if (idx != TI_NULLIDX)
					{
						if (findDec == true)
						{
							throw ERROR_THROW_IN(305, line, position);
						}
							
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}

					strcpy(bufprefix, prefix);
					word[i] = strcat(bufprefix, word[i]);
					idx = IT::IsId(idtable, word[i]);

					if (idx != TI_NULLIDX)
					{
						if (findDec == true)
						{
							throw ERROR_THROW_IN(305, line, position);
						}

						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
				}

				LT::Entry entryLT = writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);
				findDec = false;

				if (findParm) 
				{
					entryIT.idtype = IT::P;
					idtable.table[bufPos].countOfPar++;
					strcpy(entryIT.visibility, prefix);
				}
				else if (!findFunc) 
				{
					entryIT.idtype = IT::V;
					strcpy(entryIT.visibility, prefix);
					if (entryIT.iddatatype == IT::SHINT)
					{
						entryIT.value.vint = TI_SHINT_DEFAULT;
					}
					if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}
				else 
				{
					strcpy(oldprefix, prefix);
					strcpy(prefix, word[i]);
					strcpy(entryIT.visibility, emptystr);
				}

				entryIT.idxfirstLE = indxLex;
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				findFunc = false;
				findType = false;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_SHINTLIT);
			if (FST::execute(fstLiteralInt))
			{
				float test = atof((char*)word[i]);

				if (test > INT_MAX || test < INT_MIN)
				{
					throw ERROR_THROW_IN(313, line, position);
				}
					
				int value = atoi((char*)word[i]);

				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)
				{
					continue;
				}
				
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::SHINT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indxLex;

				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, (char*)charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstLiterals(word[i], FST_SLIT);
			if (FST::execute(fstLiterals))
			{
				int value = DecimalTrnsl(word[i]);

				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)
				{
					continue;
				}
				
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::SHINT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indxLex;

				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, (char*)charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstLiteralString(word[i], FST_LINELIT);
			if (FST::execute(fstLiteralString))
			{
				int length = strlen(word[i]);

				if (length > 255)
				{
					throw ERROR_THROW_IN(312, lextable.table[i].sn, -1);
				}		
				for (int k = 0; k < length; k++)
				{
					word[i][k] = word[i][k + 1];
				}
					
				word[i][length - 2] = 0;

				for (int k = 0; k < idtable.size; k++)
				{
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i])))
					{
						findSameID = true;
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						break;
					}
				}
				if (findSameID)
				{
					continue;
				}
				
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.value.vstr.str, word[i]);
				entryIT.value.vstr.len = length - 2;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxfirstLE = indxLex;
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				nameLiteral = strcat(bufL, (char*)charclit);
				strcpy(entryIT.id, nameLiteral);
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstPlus(word[i], FST_PLUS);
			if (FST::execute(fstPlus))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_PLUS, indexID++, line);
				entryLT.priority = 2;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstMinus(word[i], FST_MINUS);
			if (FST::execute(fstMinus))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MINUS, indexID++, line);
				entryLT.priority = 2;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstStar(word[i], FST_STAR);
			if (FST::execute(fstStar))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_STAR, indexID++, line);
				entryLT.priority = 3;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstDir(word[i], FST_DIRSLASH);
			if (FST::execute(fstDir))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_DIRSLASH, indexID++, line);
				entryLT.priority = 3;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstProc(word[i], FST_PROC);
			if (FST::execute(fstProc))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MOD, indexID++, line);
				entryLT.priority = 3;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstMore(word[i], FST_MORE);
			if (FST::execute(fstMore))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_MORE, indexID++, line);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstLess(word[i], FST_LESS);
			if (FST::execute(fstLess))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LESS, indexID++, line);
				entryLT.priority = 4;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				entryIT.iddatatype = IT::UNDEF;
				continue;
			}

			FST::FST fstNotEqual(word[i], FST_NOT);
			if (FST::execute(fstNotEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NOT, indexID++, line);
				entryLT.priority = 5;
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}

			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				entryLT.priority = 1;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);

				if (idtable.table[indexID - 1].idtype == IT::F) 
				{
					findParm = true;
					bufPos = indexID - 1;
				}
				continue;
			}

			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE)
				{
					strcpy(prefix, oldprefix);
				}
					
				findParm = false;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}

			position += strlen(word[i]);

			if (word[i][0] == DIV) 
			{
				line++;
				position = 0;
				indxLex--;
				continue;
			}

			int countSk = 0;

			if (word[i][0] == '\'') 
			{
				for (int j = 0; j < strlen(word[i]); j++)
				{
					if (word[i][j] == '\'')
					{
						countSk++;
					}
					if (countSk % 2 == 1)
					{
						throw ERROR_THROW_IN(311, line, position);
					}
					break;
				}
			}
			else 
			{
				throw ERROR_THROW_IN(162, line, position);
			}
		}
		for (int j = 0; j < idtable.size; j++)
		{
			if (idtable.table[j].idtype == IT::SF)
			{
				idtable.table[j].iddatatype = IT::SHINT;
				idtable.table[j].countOfPar = 1;
				idtable.table[j].types = new IT::IDDATATYPE[2];
				idtable.table[j].types[0] = IT::STR;
			}
		}
		for (int j = 0; j < idtable.size; j++)
		{
			if (idtable.table[j].idtype == IT::SFL)
			{
				idtable.table[j].iddatatype = IT::STR;
				idtable.table[j].countOfPar = 2;
				idtable.table[j].types = new IT::IDDATATYPE[2];
				idtable.table[j].types[0] = IT::STR;
				idtable.table[j].types[1] = IT::STR;
			}
		}
		for (int j = 0; j < idtable.size; j++)
		{
			if (idtable.table[j].idtype == IT::F)
			{
				int count = idtable.table[j].countOfPar;
				idtable.table[j].types = new IT::IDDATATYPE[count];

				for (int i = 0; i < count; i++)
				{
					idtable.table[j].types[i] = idtable.table[i].iddatatype;
				}
			}
		}
		for (int j = 0; j < idtable.size; j++)
		{
			if (idtable.table[j].iddatatype == IT::UNDEF && (idtable.table[j].idtype == IT::V || idtable.table[j].idtype == IT::P || idtable.table[j].idtype == IT::F))
			{
				throw ERROR_THROW_IN(300, lextable.table[idtable.table[j].idxfirstLE].sn, -1);
			}
		}
		if (!findMain)
		{
			throw ERROR_THROW(301);
		}
		if (countMain > 1)
		{
			throw ERROR_THROW_IN(302, line, -1);
		}

		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}