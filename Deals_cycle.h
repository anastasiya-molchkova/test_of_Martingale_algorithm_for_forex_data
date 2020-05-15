#ifndef Deals_cycle
#define Deals_cycle

#include "Deals_container.h"
#include <utility> // ��� std::move ��� ������ � ������ �����������

// ������� ���������� ������ � ���������� ������� � ����� ��������� �� ������
std::unique_ptr<Deal> create_pointer(const Constants::deal_type buy_or_sell, const double opening_price, const double lot)
{
	return std::make_unique<Deal>(buy_or_sell, opening_price, lot);
}

Constants::cycle_return cycle(unsigned starting_index, Statistics& data)
{
	Deals_container Deals_list;
	unsigned current_index{ starting_index };
	const double starting_price{ data.get_data_number(starting_index).get_opening_price() };
	// �����-������ � ������ �����:
	data.get_data_number(current_index).print_date_and_time();
	cout << "���� �������� �����, ���� �������� �����: " << starting_price << std::endl;

	const double half_corridor = (Constants::corridor / 2 )* Constants::one_point_as_price;
	const double buy_price = starting_price + half_corridor;
	const double sell_price = starting_price - half_corridor;
	const double upper_level = buy_price + (Constants::take_profit_level * Constants::one_point_as_price);
	// !!! ��������� ������! �������� �� ���� ������� take profit, � �� stop loss
	const double lower_level = sell_price - (Constants::take_profit_level * Constants::one_point_as_price);
	double potential_budget = Constants::total_budget;
	double total_gale{ 0 };
	double total_potential_loss{ 0 };
	double lot = Constants::minimal_lot;

	bool first_deal_is_created = false;
	// ��������� ������ ������
	while ((current_index < (data.get_length() - 1)) && (first_deal_is_created == false))
	{
		// !!! ���������� ���������� ���� � ������������ �����
		if (data.get_data_number(current_index).get_maximum_price() >= buy_price)
		{
			auto deal_ptr = create_pointer(Constants::buy, buy_price, lot);
			Deals_list.add_new_deal(std::move(deal_ptr));
			lot = lot * 2;
			data.get_data_number(current_index).print_date_and_time();
			cout << "c������ ������! ";
			Deals_list.print_deal_number(Deals_list.get_length() - 1);
			first_deal_is_created = true;
			break;  // ������� �� ����� while
		}
		// !!! ���������� ���������� ���� � ����������� �����
		if (data.get_data_number(current_index).get_minimum_price() <= sell_price)
		{
			auto deal_ptr = create_pointer(Constants::sell, sell_price, lot);
			Deals_list.add_new_deal(std::move(deal_ptr));
			lot = lot * 2;
			data.get_data_number(current_index).print_date_and_time();
			cout << "c������ ������! ";
			Deals_list.print_deal_number(Deals_list.get_length() - 1);
			first_deal_is_created = true;
			break; // ������� �� ����� while
		}
		// !!! �� ���� ��������������, ������ �����������, ������ ���� �� ���� ����������� �� ���� ������� ������ (��, ��� ���!)
		current_index++;
	}
	// ����, ������ �������� � ���� ������ ������. ��������� ������.
	bool all_closed_condition = false;
	const double safe_budget = Constants::total_budget * (100 - Constants::percent_of_risk) / 100;
	potential_budget = Constants::total_budget + Deals_list.get_total_potential_loss(); // ����������, �.�. ������������� ������ �� ������ �����
	while ((current_index < (data.get_length() - 1)) && (potential_budget >= safe_budget) && (all_closed_condition == false))
	{
		// ���� ��������� ������ ���� �� �������
		if (Deals_list.get_deal_number(Deals_list.get_length()-1).get_type() == Constants::buy)
		{
			// ������� ���������, �� �������� �� ���������� ��������
			if (data.get_data_number(current_index).get_minimum_price() <= sell_price)
			{
				// ������ ������ �� �������
				auto deal_ptr = create_pointer(Constants::sell, sell_price, lot);
				Deals_list.add_new_deal(std::move(deal_ptr));
				lot = lot * 2;
				data.get_data_number(current_index).print_date_and_time();
				cout << "c������ ������! ";
				Deals_list.print_deal_number(Deals_list.get_length() - 1);
				// ��������� ������������� ������ � ������ ���� ������
				total_potential_loss = Deals_list.get_total_potential_loss();
				potential_budget = Constants::total_budget + total_potential_loss;  // ����������, �.�. ������������� ������ �� ������ �����
			}
			// ������ ���������, �� �������� �� ������ ������� ������
			if (data.get_data_number(current_index).get_minimum_price() <= lower_level)
			{
				total_gale = Deals_list.get_total_gale(lower_level);
				if (total_gale > 0) all_closed_condition = true;
				data.get_data_number(current_index).print_date_and_time();
				Deals_list.close_all_deals();
				break;  
				// !!! ���� � ����� ����������� �������� � �������, � ������ �������, �� � �� �� ����, ��� ������, ������� ������ ��� �� �������
			}
			// � ���������, �� �������� �� ������ �������� ������
			if (data.get_data_number(current_index).get_maximum_price() >= upper_level)
			{
				total_gale = Deals_list.get_total_gale(upper_level);
				if (total_gale > 0) all_closed_condition = true;
				data.get_data_number(current_index).print_date_and_time();
				Deals_list.close_all_deals();
				break;
			}
		}
		// ���� ��������� ������ ���� �� �������
		if (Deals_list.get_deal_number(Deals_list.get_length() - 1).get_type() == Constants::sell)
		{
			// ������� ���������, �� �������� �� ����������� ��������
			if (data.get_data_number(current_index).get_maximum_price() >= buy_price)
			{
				// ������ ������ �� �������
				auto deal_ptr = create_pointer(Constants::buy, buy_price, lot);
				Deals_list.add_new_deal(std::move(deal_ptr));
				lot = lot * 2;
				data.get_data_number(current_index).print_date_and_time();
				cout << "c������ ������! ";
				Deals_list.print_deal_number(Deals_list.get_length() - 1);
				// ��������� ������������� ������ � ������ ���� ������
				total_potential_loss = Deals_list.get_total_potential_loss();
				potential_budget = Constants::total_budget + total_potential_loss;  // ����������, �.�. ������������� ������ �� ������ �����
			}
			// ������ ���������, �� �������� �� ������ �������� ������
			if (data.get_data_number(current_index).get_maximum_price() >= upper_level)
			{
				total_gale = Deals_list.get_total_gale(upper_level);
				if (total_gale > 0) all_closed_condition = true;
				data.get_data_number(current_index).print_date_and_time();
				Deals_list.close_all_deals();
				break;
				// !!! ���� � ����� ����������� �������� � �������, � ������ �������, �� � �� �� ����, ��� ������, ������� ������ ��� �� �������
			}
			// � ���������, �� �������� �� ������ ������� ������
			if (data.get_data_number(current_index).get_minimum_price() <= lower_level)
			{
				total_gale = Deals_list.get_total_gale(lower_level);
				if (total_gale > 0) all_closed_condition = true;
				data.get_data_number(current_index).print_date_and_time();
				Deals_list.close_all_deals();
				break;
			}		
		}
		current_index++;
	}
	

	if (all_closed_condition == true)
	{
		cout << " ����� �������/������ �� �����: " << total_gale << "$" << std::endl << std::endl;
		if (total_gale >= 0) 
			return Constants::cycle_return::profit;
		else 
			return Constants::cycle_return::no_profit;
	}
	if (potential_budget <= safe_budget)
	{
		cout << " ������������� ������ �� �����: " << total_potential_loss << "$" << std::endl << std::endl;
		return Constants::cycle_return::budget_finished;
	}	
	if (current_index >= (data.get_length() - 1)) 
		return Constants::cycle_return::file_finished;
}

#endif Deals_cycle
