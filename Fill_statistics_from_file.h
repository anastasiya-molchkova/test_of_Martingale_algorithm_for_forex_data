#ifndef FILL_STATISTICS_FROM_FILE
#define FILL_STATISTICS_FROM_FILE

#include "Statistics.h"
#include <utility> // ��� std::move ��� ������ � ������ �����������
#include <fstream> // ��� ������ � ������
#include <cstdlib> // ��� exit ��� ������ � ������
#include <sstream> // ��� ������ �� ��������� �������, ����� ���������� ������ �� ������ � ������ ������ ������� ����

// ������� ���������� ������ � ���������� ������� � ����� ��������� �� ����� � ������� � ��������
std::unique_ptr<Data_from_file> convert_string_to_smart_pointer(const string& correct_string)
{
	// ������ ��������� ���������� ��� ������
	std::stringstream string_from_file;
	string_from_file << correct_string;

	string date, time;
	string_from_file >> date;
	string_from_file >> time;

	float price1(0), price2(0), price3(0), price4(0);
	string_from_file >> price1;
	string_from_file >> price2;
	string_from_file >> price3;
	string_from_file >> price4;

	return std::make_unique<Data_from_file>(date, time, price1, price2, price3, price4);
}

// ������� ������ ������ �� ����� � ������
void reading_data_from_file(Statistics& our_vector)
{
	// ������ �������� ����������:
	std::ifstream file_with_data("5min.txt");
	if (!file_with_data)
	{
		std::cerr << "���� �� ������ ��� �� ����� ���� ������! \n";
		exit(1);
	}
	while (file_with_data)
	{
		string string_from_file;
		getline(file_with_data, string_from_file);
		auto smart_ptr = convert_string_to_smart_pointer(string_from_file);
		our_vector.add_one_more_line(std::move(smart_ptr));
	}
}

#endif

