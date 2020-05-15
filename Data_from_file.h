#ifndef DATA_FROM_FILE
#define DATA_FROM_FILE

#include <iostream>
#include <string>

using std::string; using std::cout;

class Data_from_file
{
private:
	string date_; // !!!это должен быть или формат даты или самописная структура
	string time_; // !!!это должен быть или формат времени или самописная структура
	double opening_price_;
	double maximum_price_;
	double minimum_price_;
	double closing_price_;
public:
	Data_from_file(const string& s1, const string& s2, const double price1, const double price2, const double price3, const double price4) :
		date_(s1), time_(s2), opening_price_(price1), maximum_price_(price2), minimum_price_(price3), closing_price_(price4)
	{}
	friend std::ostream& operator<<(std::ostream& out, const Data_from_file& one_line)
	{
		out << one_line.date_ << " " << one_line.time_ << " " << one_line.opening_price_ << " " << one_line.maximum_price_ << " " << one_line.minimum_price_ << " " << one_line.closing_price_ << '\n';
		return out;
	}
	void print_date_and_time()
	{
		cout << date_ << " " << time_ << " ";
	}
	double get_opening_price()
	{
		return opening_price_;
	}
	double get_maximum_price()
	{
		return maximum_price_;
	}
	double get_minimum_price()
	{
		return minimum_price_;
	}
	double get_closing_price()
	{
		return closing_price_;
	}
};

#endif