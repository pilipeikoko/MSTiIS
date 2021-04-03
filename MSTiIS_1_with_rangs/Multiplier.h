/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР
	Пилипейко Валентином Игоревичем
	Файл является заголовочным файлом абстрактного класса Multiplier
	28.03.2021 Добавлено авторство
	28.03.2021 Добавлено отображение промежточного результата умножения в 16 битном формате
	Б.Н. Ковригин "Алгоритмы умножения "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	Алгоритм умножения с младших разрядов множителя и сдвигом множимого влево
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/

#pragma once
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Multiplier {
protected:
	int current_rank;
	bool task_switcher = 0;

	vector<int> first_number;
	vector<int> second_number;

	vector<int> result;
	vector<int> stage_result;

	void print_input_numbers() const;
	void print_result() const;
	void converter_to_binary(int number, vector<int>& result) const;
	void print_vector(vector<int> first_number) const;
	int converter_to_decimal(vector<int> number, unsigned int i = 0) const;

	void calculate();
	virtual void multiply() = 0;

public:
	int stage;
	int finish_time;

	Multiplier() { current_rank = 7; result.resize(16, 0); stage = 0; }

	void print_first_number() const;
	void print_second_number() const;
	int get_decimal_result() const;

	void set_info(vector<int>first_number, vector<int>second_number, int stage);
	void complete_stages_task();
	
	virtual int get_operation_number() const = 0;
	virtual int total_amount_of_stages(int amount_of_numbers, int amount_of_numbers_that_may_run_parallelty) = 0;
	virtual int starting_round(int i, int amount_of_tasks_that_run_paralelly) = 0;
};