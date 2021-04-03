/* ������������ ������ 1 �� ���������� ������
	��������� ��������� ������ 921701 �����
	��������� ���������� ����������
	���� �������� ������������ ������ ������ Multiplier_by_16_steps
	28.03.2021 ��������� ���������
	28.03.2021 ��������� ������ ������
	28.03.2021 ��������� ����������� ������������� ���������� ��������� � 16 ������ �������
	�.�. �������� "��������� ��������� "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	�������� ��������� � ������� �������� ��������� � ������� ��������� �����
	����������� ���������� ���������� � ��������� ����������� ����������� ��� ��������� ��������� ��������� ��� �������� �����
*/
#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Multiplier.h"

using namespace std;

class Multiplier_by_16_steps: public Multiplier{
protected:

	void multiply() override;

public:

	Multiplier_by_16_steps():Multiplier() { }

	int get_operation_number()const override;
	int total_amount_of_stages(int amount_of_numbers, int amount_of_numbers_that_may_run_parallelty)override;
	int starting_round(int i, int amount_of_tasks_that_run_paralelly) override;
};