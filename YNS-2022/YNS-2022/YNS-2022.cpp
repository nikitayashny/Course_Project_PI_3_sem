#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "LexAn.h"
#include "Polish.h"
#include "MFST.h"
#include "Greibach.h"
#include "Polish.h"
#include "SemAn.h"
#include "Generator.h"

#define EXP1 16

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;

	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm);
		Log:WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		LT::showTable(lex.lextable, log.stream);
		std::cout << "Лексический анализ завершен успешно" << std::endl;
		MFST_TRACE_START(log)
		unsigned int start_time = clock();
		MFST::Mfst mfst(lex.lextable, GRB::getGreibach());
		bool syntax_ok = mfst.start(log);
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		
		mfst.savededucation();
		mfst.printrules(log);

		if (!syntax_ok)
		{
			std::cout << "Ошибка в ходе синтаксического анализа. Подробную информацию можно увидеть в протоколе работы" << std::endl;
			return 0;
		}

		std::cout << "Синтаксический анализ прошел успешно" << std::endl;
		bool sem_ok = Semantic::semanticsCheck(lex, log);

		if (!sem_ok)
		{
			std::cout << "Ошибка семантического анализа" << std::endl;
		}

		std::cout << "Семантический анализ прошел успешно" << std::endl;
		IT::showTable(lex.idtable, log.stream);
		PolishStart(lex);
		std::cout << "Польская запись построена" << std::endl;
		LT::showTable(lex.lextable, log.stream);
		Gen::CodeGeneration(lex);
		std::cout << "Генерация кода закончена" << std::endl;
		Log::Close(log);
		/*system("start C:\\Users\\User\\Desktop\\курсач\\compile.bat");*/
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		std::cout << "\nОшибка " << e.id
				  << ": " << e.message
				  << "\nСтрока " << e.inext.line
				  << " позиция " << e.inext.col << std::endl;
	}
	return 0;
}