/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР
	Пилипейко Валентином Игоревичем
	Файл является заголовочным файлом класса Multiplier_by_8_steps
	28.03.2021 Добавлено авторство
	28.03.2021 Добавлена логика класса
	28.03.2021 Добавлено отображение промежточного результата умножения в 16 битном формате
	Б.Н. Ковригин "Алгоритмы умножения "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	Алгоритм умножения с младших разрядов множителя и сдвигом множимого влево
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/

#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include "Multiplier.h"

class Multiplier_by_8_steps: public Multiplier {
protected:

	void sum_of_temp_stages_result(vector<int>,vector<int>);
	virtual void multiply() override;

public:

	Multiplier_by_8_steps() :Multiplier() { }

	int get_operation_number()const override;
	int total_amount_of_stages(int amount_of_numbers, int amount_of_numbers_that_may_run_parallelty) override;
	int starting_round(int i, int amount_of_tasks_that_run_paralelly) override;
};