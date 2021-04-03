/* Лабораторная работа 1 по дисциплине МРЗвИС
	Выполнена студентом группы 921701 БГУИР Пилипейко Валентином Игоревичем
	Файл демонстрирует работу работу класса Multiplier и его наследников.
	25.03.2021 Добавлено авторство
	28.03.2021 Добавлены ранки задачи
	28.03.2021 Добавлено отображение промежуточного результата умножения в 16 битном формате
	29.03.2021 Добавлена проверка не некорректные входные данные
	Разработано консольное приложение с имитацией конвейерной архитектуры для умножения заданного множества пар двоичных чисел
*/
#include <iostream>
#include <vector>
#include <ctime>
#include "Multiplier_by_16_steps.h"
#include "Multiplier_by_8_steps.h"
#include "Multiplier_by_4_steps.h"
#include "Multiplier_by_2_steps.h"
using namespace std;


void print_tabs(int amount) {
	for (int i = 0; i < amount; ++i) cout << "  ";
}

int main()
{
	int amount_of_numbers;
	int amount_of_tasks_that_run_paralelly;
	int rang;
	
	bool wrong_info = true;
	
	// Считка исходной информации
	while(wrong_info){
		cout << "How many pairs of numbers do you want to multiply?\n";
		cin >> amount_of_numbers;

		if (cin.fail()) {
			cout << "Incorrect number\n";
			cin.clear();
			cin.ignore();
			continue;
		}

		cout << "Enter rang: 16 8 4 2\n";
		cin >> rang;

		if (cin.fail()) {
			cout << "Incorrect number\n";
			cin.clear();
			cin.ignore();
			continue;
		}
		else if (rang != 16 && rang != 8 && rang!=4 && rang!=2) {
			cout << "Wrong number\n";
			cin.clear();
			cin.ignore();
			continue;
		}

		cout << "How many tasks can run parallelly?\n";
		cin >> amount_of_tasks_that_run_paralelly;

		if (amount_of_tasks_that_run_paralelly <= 0 || amount_of_numbers<=0 || cin.fail()) {
			cout << "Incorrect number\n";
			cin.clear();
			cin.ignore();
		}
		else
			wrong_info = false;
	}
	
	clock_t begin = clock();

	if (amount_of_tasks_that_run_paralelly > amount_of_numbers)
		amount_of_tasks_that_run_paralelly = amount_of_numbers;


	Multiplier* multiplier;
	if (rang == 2) {
		multiplier = new Multiplier_by_2_steps[amount_of_numbers];
	}
	else if (rang == 4) {
		multiplier = new Multiplier_by_4_steps[amount_of_numbers];
	}
	else if (rang == 8) {
		multiplier = new Multiplier_by_8_steps[amount_of_numbers];
	}
	else {
		multiplier = new Multiplier_by_16_steps[amount_of_numbers];
	}

	vector <int> first_number;
	vector <int> second_number;

	//srand(time(0));

	// Псевдослучайное заполнение векторов
	for (int i = 0; i < amount_of_numbers; ++i) {

		int number;
		for (int j = 0; j < 8; j++) {
			number = rand();
			first_number.push_back(number % 2 == 0 ? 1 : 0);
		}
		for (int j = 0; j < 8; j++) {
			number = rand();
			second_number.push_back(number % 2 == 0 ? 1 : 0);
		}
		int round = 0;
		if (amount_of_tasks_that_run_paralelly <= i) {
			round = multiplier->starting_round(i, amount_of_tasks_that_run_paralelly);
		}
		//count round for bits as well
		multiplier[i].set_info(first_number, second_number, i + round);

		first_number.clear();
		second_number.clear();
	}

	cout << "First vector: \n";

	for (int i = 0; i < amount_of_numbers; ++i) {
		cout << i+1 << " ";
		multiplier[i].print_first_number();
	}

	cout << "Second vector: \n";
	for (int i = 0; i < amount_of_numbers; ++i) {
		cout << i+1 << " ";
		multiplier[i].print_second_number();
	}
	cout << endl;

	for (int i = 0; i < amount_of_numbers; ++i) {
		cout << "Pair " << i+1 << endl;
		multiplier[i].print_first_number();
		multiplier[i].print_second_number();
	}
	cout << endl;

	int current_stage = 0;
	int amount_of_stages = multiplier->total_amount_of_stages(amount_of_numbers,amount_of_tasks_that_run_paralelly);

	// diffirent for rangs

	int enters_counter = 0;
	
	for (int i = 0; ; ++i) {
		cout << "Time = " << i+1 << "\n";
		for (int j = 0; j < amount_of_numbers; ++j) {
			if (current_stage == multiplier[j].stage) {
				++enters_counter;
				print_tabs(i + 1);
				cout << "Pair " << j+1 << " Stage " << multiplier[j].get_operation_number() << endl;
				multiplier[j].complete_stages_task();
			}
		}
		if (enters_counter == 0) {
			cout << "Finished\n";
			break;
		}
		enters_counter = 0;

		++current_stage;
	}

	cout << endl;
	for (int i = 0; i < amount_of_numbers; ++i) {
		cout << "Pair " << i+1 << endl;
		multiplier[i].print_first_number();
		multiplier[i].print_second_number();
		cout << "Result: " << multiplier[i].get_decimal_result() <<" Finished on time: "<<multiplier[i].finish_time+1<< endl;
	}
	clock_t end = clock();
	cout<<(end - begin) ;

}