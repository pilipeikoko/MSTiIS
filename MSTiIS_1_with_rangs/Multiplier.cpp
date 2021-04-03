/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР
	Пилипейко Валентином Игоревичем
	Файл описывает абстрактного класса Multiplier
	28.03.2021 Добавлено авторство
	28.03.2021 Добавлено отображение промежточного результата умножения в 16 битном формате
	Б.Н. Ковригин "Алгоритмы умножения "http://www.dut.edu.ua/ua/uploads/l_1176_25351518.pdf"
	Алгоритм умножения с младших разрядов множителя и сдвигом множимого влево
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/

#include "Multiplier.h"

void Multiplier::converter_to_binary(int number, vector<int>& result) const
{
	int rec_number;
	if (number != 0) {
		rec_number = number % 2;
		number = number / 2;
		converter_to_binary(number, result);
		result.push_back(rec_number);
	}
}

int Multiplier::converter_to_decimal(vector<int> number, unsigned int i) const
{
	int total = 0;
	if (i < number.size())
	{
		if (number[i] == 1)
			total = pow(2, i);
		return total + converter_to_decimal(number, ++i);
	}
	return total;
}

void Multiplier::calculate()
{
	vector<int> extended_stages_result = stage_result;
	//extended_stages_result.resize(16, 0);


	vector<int> result_copy = result;

	result.clear();

	int to_remind = 0;
	for (int i = 15; i >= 0; --i) {
		int current_sum = to_remind + result_copy[i] + extended_stages_result[i];
		result.insert(result.begin(), current_sum % 2);
		to_remind = current_sum / 2;
	}
	--current_rank;
}

void Multiplier::print_vector(vector<int> first_number) const
{
	for (int i = 0; i < first_number.size(); i++) {
		if (i % 4 == 0) {
			cout << " ";
		}
		cout << first_number[i];
	}
}

void Multiplier::print_first_number() const
{
	vector<int>temp_vector = first_number;
	reverse(temp_vector.begin(), temp_vector.end());

	print_vector(first_number);
	cout << " - " << converter_to_decimal(temp_vector);
	cout << endl;
}

void Multiplier::print_second_number() const
{
	vector<int>temp_vector = second_number;
	reverse(temp_vector.begin(), temp_vector.end());

	print_vector(second_number);
	cout << " - " << converter_to_decimal(temp_vector);
	cout << endl;
}

void Multiplier::print_result() const
{
	vector<int>temp_vector = result;
	print_vector(temp_vector);
}

void Multiplier::print_input_numbers() const
{
	cout << "        ";
	print_vector(first_number);
	cout << endl;
	cout << "        ";
	print_vector(second_number);
	cout << endl << "_________________\n";
}


void Multiplier::set_info(vector<int> first_number, vector<int> second_number, int stage)
{
	this->stage = stage;
	this->first_number = first_number;
	this->second_number = second_number;
	this->finish_time = 15 + stage;
}

void Multiplier::complete_stages_task()
{
	cout << "    ______________________________________\n";
	stage++;
	if (!task_switcher) {
		task_switcher = true;
		cout << "    Multiplication \n";
		multiply();
		cout << "    Result: ";
		print_vector(stage_result);
	}
	else {
		task_switcher = false;
		cout << "    Sum \n";
		calculate();
		cout << "    Result: ";
		print_result();
	}
	if (current_rank == -1) {
		// Multiplication done, returning to stage 0
		cout << "    END" << endl;
		stage = 0;
		return;
	}
	cout << endl << endl;
}



int Multiplier::get_decimal_result() const
{
	vector<int> reversed_result = result;
	reverse(reversed_result.begin(), reversed_result.end());
	return converter_to_decimal(reversed_result);
}
