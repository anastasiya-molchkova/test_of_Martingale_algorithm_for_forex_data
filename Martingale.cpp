// Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "Fill_statistics_from_file.h"
#include "Deals_cycle.h"
#include <cstdlib>   // для функций выбора случайного числа srand() и rand()
#include <ctime>     // чтобы в randomize опираться на время запуска программы

//функция выбора случайного числа между двумя заданными значениями
static unsigned short getRandomNumber(unsigned short min, unsigned short max)
{
	static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
	return static_cast<unsigned short>(rand() * fraction * (max - min + 1) + min);
}

int main()
{
	//аналог randomize с привязкой ко времени запуска:
	srand(static_cast<unsigned int>(time(0)));
	rand();

	setlocale(LC_CTYPE, "rus"); // для вывода на кириллице

	Statistics Data_from_5min_file;
	reading_data_from_file(Data_from_5min_file);

	unsigned number_of_profits{ 0 };
	unsigned number_of_not_profits{ 0 };
	unsigned number_of_finish_by_budget_limit{ 0 };
	unsigned number_of_finish_by_data_limit{ 0 };

	for (unsigned i = 1; i <= Constants::tries_number; i++)
	{
		unsigned random_point = getRandomNumber(0, (Data_from_5min_file.get_length() - Constants::number_of_blocked_data));
		unsigned starting_index{random_point}; // точка, с которой запускаем алгоритм
		Constants::cycle_return cycle_result = cycle(starting_index, Data_from_5min_file);
		if (cycle_result == Constants::cycle_return::profit) 
			number_of_profits++;
		if (cycle_result == Constants::cycle_return::no_profit) 
			number_of_not_profits++;
		if (cycle_result == Constants::cycle_return::budget_finished) 
			number_of_finish_by_budget_limit++;
		if (cycle_result == Constants::cycle_return::no_profit) 
			number_of_finish_by_data_limit++;
	}

	cout << "ТЕСТ ОКОНЧЕН!" << std::endl;
	cout << "циклы с прибылью: " << (static_cast<double>(number_of_profits) / Constants::tries_number) * 100 << "%" << std::endl;
	cout << "циклы с убытком: " << (static_cast<double>(number_of_not_profits) / Constants::tries_number) * 100 << "%" << std::endl;
	cout << "циклы завершённые по окончанию выделенного бюджета: " << (static_cast<double>(number_of_finish_by_budget_limit) / Constants::tries_number) * 100 << "%" << std::endl;
	cout << "циклы завершённые по окончанию тестовых данных: " << (static_cast<double>(number_of_finish_by_data_limit) / Constants::tries_number) * 100 << "%" << std::endl;
	
	return 0;
}
