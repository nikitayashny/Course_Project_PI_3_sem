#include "stdafx.h"
#include "IT.h"
#include "Error.h"
#include<iomanip>

using namespace std;

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* tabl = new IdTable;

		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(160);
		}

		tabl->maxsize = size;
		tabl->size = 0;
		tabl->table = new Entry[size];
		return*tabl;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size + 1 > idtable.maxsize)
		{
			throw ERROR_THROW(161);
		}

		idtable.table[idtable.size] = entry;
		idtable.size += 1;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}

	void showTable(IdTable& idtable, ofstream* stream)
	{
		int i, j, numberOP = 0;
		*stream << std::setfill('-') << std::setw(87) << '-' << std::endl;
		*stream << "   �" << " | " << "�������������" << " | " << "��� ������" << " | " << "��� ��������������" << " | " << "������ � ��" << " | " << "��������    " << std::endl;
		*stream << std::setw(87) << '-' << std::endl;

		for (i = 0, j = 0; i < idtable.size; i++, j++)
		{
			if (idtable.table[i].idtype == OP)
			{
				numberOP++;
				j--;
				continue;
			}

			*stream << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			*stream << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype)
			{
			case SHINT: *stream << std::setw(10) << std::left;
				if (idtable.table[i].idtype == OP) *stream << "-" << " | ";
				else *stream << "shint" << " | "; break;
			case STR: *stream << std::setw(10) << std::left;
				if (idtable.table[i].idtype == OP) *stream << "-" << " | ";
				if (idtable.table[i].idtype == SFL) *stream << "void" << " | ";
				else *stream << "line" << " | "; break;
			default: *stream << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: *stream << std::setw(18) << std::left << "����������" << " | "; break;
			case F: *stream << std::setw(18) << std::left << "�������" << " | "; break;
			case P: *stream << std::setw(18) << std::left << "��������" << " | "; break;
			case L: *stream << std::setw(18) << std::left << "�������" << " | "; break;
			case SF:  *stream << std::setw(18) << std::left << "����������� �������" << " | "; break;
			case SFL:  *stream << std::setw(18) << std::left << "����������� �������" << " | "; break;
			case OP: *stream << std::setw(18) << std::left << "��������" << " | ";
				numberOP++;
				break;
			default: *stream << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			*stream << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == SHINT && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				*stream << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				*stream << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else
				*stream << "-";
			*stream << std::endl;
		}
		*stream << std::setfill('-') << std::setw(87) << '-' << std::endl;
		*stream << "���������� ���������������: " << i - numberOP << std::endl;
		*stream << std::setw(87) << '-' << std::endl;
	}
};