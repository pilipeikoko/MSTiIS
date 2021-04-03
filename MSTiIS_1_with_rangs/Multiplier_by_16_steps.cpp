/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР
	Пилипейко Валентином Игоревичем
	Файл описывает логику класса Multiplier_by_16_steps
	28.03.2021 Добавлено авторство
	28.03.2021 Добавлена логика класса
	28.03.2021 Добавлено отображение промежточного результата умножения в 16 битном формате
	Б.Н. Ковригин "Алгоритмы умножения "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	Алгоритм умножения с младших разрядов множителя и сдвигом множимого влево
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/
#include "Multiplier_by_16_steps.h"


void Multiplier_by_16_steps::multiply()
{
	this->stage_result.clear();
	this->stage_result.resize(16, 0);
	if (second_number[current_rank] == 1) {
		for (int i = this->current_rank+1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			stage_result[i] = first_number[j];
		}
	}
	else {
		for (int i = this->current_rank + 1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			stage_result[i] = 0;
		}
	}

}

int Multiplier_by_16_steps::get_operation_number() const
{
	int flag = task_switcher ? 0 : 1;
	int num = current_rank;
	return 18 - (num + 1) * 2 - flag;

}

int Multiplier_by_16_steps::total_amount_of_stages(int amount_of_numbers, int amount_of_numbers_that_may_run_parallelty)
{
	if (amount_of_numbers_that_may_run_parallelty == amount_of_numbers)
		return 15 + amount_of_numbers_that_may_run_parallelty;
	else
		return  (((amount_of_numbers - 1) / amount_of_numbers_that_may_run_parallelty) + 1) * 16 + (amount_of_numbers - 1) % amount_of_numbers_that_may_run_parallelty;

}

int Multiplier_by_16_steps::starting_round(int i, int amount_of_tasks_that_run_paralelly)
{
	return (i / amount_of_tasks_that_run_paralelly) * (16 - amount_of_tasks_that_run_paralelly);
}

