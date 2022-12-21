#pragma once
#include "Error.h"
#include "Parm.h"
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов
#define LEX_SHINT		't'			
#define LEX_LINE		't'			
#define LEX_TYPE		't'
#define LEX_ID			'i'			
#define LEX_LITERAL		'l'			
#define LEX_FUNCTION	'f'			
#define LEX_NEW			'n'			
#define LEX_RETURN		'r'			
#define LEX_OUT			'p'			
#define LEX_MAIN		'm'			
#define LEX_SEMICOLON	';'			
#define LEX_COMMA		','			
#define LEX_LEFTBRACE	'['			
#define LEX_BRACELET	']'			
#define LEX_LEFTTHESIS	'('			
#define LEX_RIGHTTHESIS	')'			
#define LEX_PLUS		'+'					
#define LEX_MINUS		'-'			
#define LEX_STAR		'*'			
#define LEX_DIRSLASH	'/'			
#define LEX_MOD			'%'
#define LEX_OPERATOR	'v'			
#define LEX_EQUAL		'='
#define LEX_PERFORM		'c'
#define LEX_FOR			'?'
#define LEX_LOGSEP		'#'
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_NOT			'!'
#define LEX_NEWLINE		'^'

namespace LT {
	struct Entry {
		char lexema;                                          
		int sn;
		int idxTI;
		int priority;	//индекс в ТИ
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	Entry writeEntry(Entry& entry, char lexema, int indx, int line);
	void showTable(LexTable lextable, /*Parm::PARM parm*/ std::ofstream* stream);
}