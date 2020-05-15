#ifndef STATISTICS
#define STATISTICS

#include <vector>
#include <memory>  // ��� ������ � ������ �����������
#include "Data_from_file.h"

using std::vector;

// �����-��������� ����� ���������� �� ������-������ �� �����
class Statistics
{
private:
	vector <std::unique_ptr<Data_from_file>> data_list;
	unsigned lines_number;
public:
	// ����������� ������ �� ���������
	Statistics() : data_list{}, lines_number(0)
	{}

	// ���������� ������ � ������
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
		return (lines_number-1); // ��� ��� ��������� ������ - ������ ������-��
	}

	// ����� �� ����� ������ �� ������
	void print_line_number(const unsigned i)
	{
		cout << get_data_number(i);
	}
};

#endif
