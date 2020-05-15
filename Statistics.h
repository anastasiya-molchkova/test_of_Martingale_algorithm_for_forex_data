#ifndef STATISTICS
#define STATISTICS

#include <vector>
#include <memory>  // для работы с умными указателями
#include "Data_from_file.h"

using std::vector;

// класс-контейнер умных указателей на строки-данные из файла
class Statistics
{
private:
	vector <std::unique_ptr<Data_from_file>> data_list;
	unsigned lines_number;
public:
	// конструктор класса по умолчанию
	Statistics() : data_list{}, lines_number(0)
	{}

	// добавление данных в вектор
	void add_one_more_line(std::unique_ptr<Data_from_file> data_ptr)
	{
		data_list.push_back(std::move(data_ptr));
		lines_number = data_list.size();
	}

	Data_from_file get_data_number(const unsigned index)
	{
		return *data_list[index];
	}

	unsigned get_length()
	{
		return (lines_number-1); // так как последняя строка - пустая почему-то
	}

	// вывод на экран строки по номеру
	void print_line_number(const unsigned i)
	{
		cout << get_data_number(i);
	}
};

#endif
