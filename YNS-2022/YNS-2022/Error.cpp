#include "Error.h"

namespace Error
{
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),		// ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[Lex]# �������� ����������� ������ ������� ������"),
		ERROR_ENTRY(121, "[Lex]# ������� ������ �����������"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160, "[Lex]# �������� ����������� ������ ������� ���������������"),
		ERROR_ENTRY(161, "[Lex]# ������� ��������������� �����������"),
		ERROR_ENTRY(162, "[Lex]# ���������� ��������� ������� ��������"),
		ERROR_ENTRY(163, ""),ERROR_ENTRY(164, ""),ERROR_ENTRY(165, ""),ERROR_ENTRY(166, ""),ERROR_ENTRY(167, ""),
		ERROR_ENTRY(168, ""),ERROR_ENTRY(169, ""),ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), 
		ERROR_ENTRY_NODEF10(190),ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY(300, "[Sem]# ������������� �������������"),
		ERROR_ENTRY(301, "[Sem]# ����������� ����� ����� main"),
		ERROR_ENTRY(302, "[Sem]# ���������� ��������� ����� ����� main"),
		ERROR_ENTRY(303, "[Sem]# � ���������� �� ������ ��� ��������������"),
		ERROR_ENTRY(304, "[Sem]# � ���������� ����������� �������� ����� new"),
		ERROR_ENTRY(305, "[Sem]# ������� ��������������� ��������������"),
		ERROR_ENTRY(306, ""),
		ERROR_ENTRY(307, ""),
		ERROR_ENTRY(308, "[Sem]# ���-�� ���������� �������� � ������������ ���������� �� ���������"),
		ERROR_ENTRY(309, "[Sem]# ������������ ����� ������������ ����������"),
		ERROR_ENTRY(310, "[Sem]# ������������� ������� ���������� �������� �����������"),
		ERROR_ENTRY(311, "[Sem]# ��������� ������ \'. ��������, �� ������ ��������� �������"),
		ERROR_ENTRY(312, "[Sem]# �������� ������ ���������� ��������"),
		ERROR_ENTRY(313, "[Sem]# ������������ ������������� �������"),
		ERROR_ENTRY(314, "[Sem]# ���� ������ � ��������� �� ���������"),
		ERROR_ENTRY(315, "[Sem]# ��� ������� � ������������� �������� �� ���������"),
		ERROR_ENTRY(316, ""),
		ERROR_ENTRY(317, "[Sem]# �������� �������� ���������"),
		ERROR_ENTRY(318, "[Sem]# ������� �� ����"),
		ERROR_ENTRY(319, ""),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[Syn]# �������� ��������� ���������"),
		ERROR_ENTRY(601, "[Syn]# �� ������ ������ ���������� �������"),
		ERROR_ENTRY(602, "[Syn]# ������ � ���� �������"),
		ERROR_ENTRY(603, "[Syn]# ������ � ���� ���������"),
		ERROR_ENTRY(604, "[Syn]# ������ � ������ ���������� �������"),
		ERROR_ENTRY(605, "[Syn]# ������ � ������ �������/���������"),
		ERROR_ENTRY(606, "[Syn]# ������ � ������ ����������� ���������� �������"),
		ERROR_ENTRY(607, "[Syn]# ������ ��� �������������� �����"),
		ERROR_ENTRY(608, "[Syn]# ������ � ���� �����"),
		ERROR_ENTRY(609, "[Syn]# ������ � ������� �����"),
		ERROR_ENTRY(610, "[Syn]# �������� �������� ��������"),
		ERROR_ENTRY(611, "[Syn]# �������� �������������� ��������"),
		ERROR_ENTRY(612, "[Syn]# �������� ���������. ��������� ������ ��������������/��������"),
		ERROR_ENTRY(613, "[Syn]# ������ � �������������� ���������"),
		ERROR_ENTRY(614, "[Syn]# ������������ �������������� �����������"),
		ERROR_ENTRY(615, "[Syn]# ������������ �������������� ����������� � ���� �����"),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY(682, ""), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		ERROR e;

		if (id < 0 || id > ERROR_MAX_ENTRY)
		{
			e = error[0];
		}
		else
		{
			e = error[id];
		}		
		return e;
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;

		if (id < 0 || id > ERROR_MAX_ENTRY)
		{
			e = error[0];
		}			
		else
		{
			e = error[id];
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
};