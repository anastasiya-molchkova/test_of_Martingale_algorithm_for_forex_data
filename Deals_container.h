#ifndef DEALS_CONTAINER
#define DEALS_CONTAINER

#include <vector>
#include <memory>  // ��� ������ � ������ �����������
#include "Deal.h"

using std::vector;

// �����-��������� ����� ���������� �� ������
class  Deals_container
{
private:
	vector <std::unique_ptr<Deal>> all_deals;
	unsigned deals_number;
public:
	// ����������� ������ �� ���������
	Deals_container() : all_deals{}, deals_number(0)
	{}

	// ���������� ������ � ������
	void add_new_deal(std::unique_ptr<Deal> deal_ptr)
	{
		all_deals.push_back(std::move(deal_ptr));
		deals_number = all_deals.size();
	}
	
	Deal get_deal_number(const unsigned index)
	{
		return *all_deals[index];
	}

	unsigned get_length()
	{
		return deals_number;
	}

	// ����� �� ����� ������ �� ������
	void print_deal_number(const unsigned i)
	{
		get_deal_number(i).print();
	}
	
	double minimum(const double a, const double b)
	{
		if (a <= b) return a;
		else return b;
	}

	// ���� ����� �� ���� ���������� ��� ������ �� ���� �������, �� ������� ������ � ��� ������� � ���� �������
	double get_total_potential_loss()
	{
		double loss_for_upper_level{ 0 };
		double loss_for_lower_level{ 0 };

		for (unsigned i = 0; i < deals_number; i++)
		{
			if (get_deal_number(i).get_status() == true)
			{
				if ((get_deal_number(i).get_type() == Constants::buy))
				{
					loss_for_upper_level += get_deal_number(i).get_take_profit_gale(); // �� ������� ������� ��� ������ �� ������� � ������
					loss_for_lower_level += get_deal_number(i).get_stop_loss_gale();   // �� ������ ������� ��� ������ �� ������� � ������� 
				}
				else
				{
					loss_for_upper_level += get_deal_number(i).get_stop_loss_gale();  // �� ������� ������� ��� ������ �� ������� � �������
					loss_for_lower_level += get_deal_number(i).get_take_profit_gale();  // �� ������ ������� ��� ������ �� ������� � ������ 
				}
			}
		}
		return minimum(loss_for_lower_level, loss_for_upper_level);
	}

	double module(const double value)
	{
		if (value >= 0) return value;
		else return -value;
	}

	double get_total_gale(const double price)
	{
		double total_gale{ 0 };
		for (unsigned i = 0; i < deals_number; i++)
		{
			if (get_deal_number(i).get_status() == true)
			{
				if (module(get_deal_number(i).get_take_profit_price() - price) <= Constants::small_value)
					total_gale += get_deal_number(i).get_take_profit_gale();
				if (module(get_deal_number(i).get_stop_loss_price() - price) <= Constants::small_value)
					total_gale += get_deal_number(i).get_stop_loss_gale();
			}
		}
		return total_gale;
	}

	void close_all_deals()
	{
		for (unsigned i = 0; i < deals_number; i++)
			if (get_deal_number(i).get_status() == true)
				get_deal_number(i).close_the_deal();
		cout << "������� ��� ������! ";
	}

};

#endif