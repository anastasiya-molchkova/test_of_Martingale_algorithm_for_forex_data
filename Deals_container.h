#ifndef DEALS_CONTAINER
#define DEALS_CONTAINER

#include <vector>
#include <memory>  // для работы с умными указателями
#include "Deal.h"

using std::vector;

// класс-контейнер умных указателей на сделки
class  Deals_container
{
private:
	vector <std::unique_ptr<Deal>> all_deals;
	unsigned deals_number;
public:
	// конструктор класса по умолчанию
	Deals_container() : all_deals{}, deals_number(0)
	{}

	// добавление данных в вектор
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

	// вывод на экран сделки по номеру
	void print_deal_number(const unsigned i)
	{
		get_deal_number(i).print();
	}
	
	double minimum(const double a, const double b)
	{
		if (a <= b) return a;
		else return b;
	}

	// этот метод не тупо складывает все убытки по всем сделкам, он считает убытки в две стороны и берёт минимум
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
					loss_for_upper_level += get_deal_number(i).get_take_profit_gale(); // по верхней границе все сделки на покупку с плюсом
					loss_for_lower_level += get_deal_number(i).get_stop_loss_gale();   // по нижней границе все сделки на покупку с минусом 
				}
				else
				{
					loss_for_upper_level += get_deal_number(i).get_stop_loss_gale();  // по верхней границе все сделки на продажу с минусом
					loss_for_lower_level += get_deal_number(i).get_take_profit_gale();  // по нижней границе все сделки на продажу с плюсом 
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
		cout << "закрыли все сделки! ";
	}

};

#endif