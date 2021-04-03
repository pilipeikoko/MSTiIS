/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР
	Пилипейко Валентином Игоревичем
	Файл описывает логику класса Multiplier_by_8_steps
	28.03.2021 Добавлено авторство
	28.03.2021 Добавлена логика класса
	28.03.2021 Добавлено отображение промежточного результата умножения в 16 битном формате
	Б.Н. Ковригин "Алгоритмы умножения "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	Алгоритм умножения с младших разрядов множителя и сдвигом множимого влево
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/

#include "Multiplier_by_8_steps.h"


void Multiplier_by_8_steps::sum_of_temp_stages_result(vector<int> first_vector, vector<int> second_vector)
{
	this->stage_result.clear();
	int to_remind = 0;
	for (int i = 15; i >= 0; --i) {
		int current_sum = to_remind + first_vector[i] + second_vector[i];
		stage_result.insert(stage_result.begin(), current_sum % 2);
		to_remind = current_sum / 2;
	}
}

void Multiplier_by_8_steps::multiply()
{

	vector<int> first_temp_stages_result(16,0);
	vector<int> second_temp_stage_result(16, 0);

	if (second_number[current_rank] == 1) {
		for (int i = this->current_rank + 1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			first_temp_stages_result[i] = first_number[j];
		}
	}
	else {
		for (int i = this->current_rank + 1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			first_temp_stages_result[i] = 0;
		}
	}
	--current_rank;
	if (second_number[current_rank] == 1) {
		for (int i = this->current_rank + 1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			second_temp_stage_result[i] = first_number[j];
		}
	}
	else {
		for (int i = this->current_rank + 1, j = 0; i <= this->current_rank + 8; ++i, ++j) {
			second_temp_stage_result[i] = 0;
		}
	}
	sum_of_temp_stages_result(first_temp_stages_result,second_temp_stage_result);

}

int Multiplier_by_8_steps::get_operation_number() const
{
	int num = current_rank;
	return 8 - num;
}

int Multiplier_by_8_steps::total_amount_of_stages(int amount_of_numbers, int amount_of_numbers_that_may_run_parallely)
{
	if (amount_of_numbers_that_may_run_parallely == amount_of_numbers)
		return 7 + amount_of_numbers_that_may_run_parallely;
	else
		return  (((amount_of_numbers - 1) / amount_of_numbers_that_may_run_parallely) + 1) * 8 + (amount_of_numbers - 1) % amount_of_numbers_that_may_run_parallely;

}

int Multiplier_by_8_steps::starting_round(int i, int amount_of_tasks_that_run_paralelly)
{
	return (i / amount_of_tasks_that_run_paralelly) * (8 - amount_of_tasks_that_run_paralelly);
}

