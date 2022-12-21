#pragma once
#define ID_MAXSIZE		10			// ������������ ���������� �������� � ��������������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_SHINT_DEFAULT 0x00000000	// �������� �� ��������� ��� ���� shint
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff	// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255			// 

namespace IT						// ������� ���������������
{
	enum IDDATATYPE { SHINT = 1, STR = 2, UNDEF = 4 };			// ���� ������ ���������������: shint, line
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5, SF = 6, SFL = 7 };// ���� ���������������: ����������, �������, ��������, �������, ��������, ����������� ������� 

	struct Entry						// ������ ������� ���������������
	{
		int			idxfirstLE;			// ������ ������ ������ � ������� ������
		char		visibility[ID_MAXSIZE];
		char		id[ID_MAXSIZE];		// �������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;			// ��� ������
		IDTYPE		idtype;				// ��� ��������������
		int			countOfPar = 0;
		IDDATATYPE* types;
		union
		{
			int vint;					// �������� shint
			bool vbool;
			struct
			{
				int len;						// ���������� �������� � line
				char str[TI_STR_MAXSIZE - 1];	// ������� line
			} vstr;								// �������� line
		} value;								// �������� ��������������
	};

	struct IdTable					// ��������� ������� ���������������
	{
		int maxsize;				// ������� ������� ��������������� < TI_MAXSIZE
		int size;					// ������� ������ ������� ��������������� < maxsize
		Entry* table;				// ������ ����� ������� ���������������
	};

	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		Entry entry			// ������ ������� ���������������
	);

	Entry GetEntry(			// �������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n				// ����� ���������� ������
	);

	int IsId(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
		IdTable& idtable,	// ��������� ������� ���������������
		char id[ID_MAXSIZE]	// �������������
	);

	void Delete(IdTable& idtable);	// ������� ������� ������ (���������� ������)
	void showTable(IdTable& idtable, std::ofstream* stream);
};