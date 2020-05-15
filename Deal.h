#ifndef DEAL
#define DEAL

#include "Constants.h"
#include <iostream>

using std::cout;

// ����� ������
class Deal
{
private:
	Constants::deal_type type_;
	bool status_;               // ������ = ���� �������, ���� - ���� �������
	double lot_in_deal_;
	double opening_price_;
	double take_profit_price_;
	double stop_loss_price_;
	double take_profit_gale_;
	double stop_loss_gale_;
public:
	// ����������� �� ��������� ������������ �� ���:
	Deal() = delete;
	// �����������
	Deal(Constants::deal_type sell_or_buy, double price, double lot) : type_(sell_or_buy), status_(true), opening_price_(price), lot_in_deal_(lot)
	{
		if (type_ == Constants::buy)
		{
			take_profit_price_ = opening_price_ + (Constants::one_point_as_price * Constants::take_profit_level);
			stop_loss_price_ = opening_price_ - (Constants::one_point_as_price * Constants::stop_loss_level);
		}
		if (type_ == Constants::sell)
		{
			take_profit_price_ = opening_price_ - (Constants::one_point_as_price * Constants::take_profit_level);
			stop_loss_price_ = opening_price_ + (Constants::one_point_as_price * Constants::stop_loss_level);
		}
		take_profit_gale_ = lot * Constants::take_profit_level;
		stop_loss_gale_ = - lot * Constants::stop_loss_level;
		// !!! ��� ��� ���� ���� ������ ���� ������� �� 1 �������, �� � ������������� ������ ����� ���� ������������� �������, ���!
	}

	void print()
	{
		if (type_ == Constants::buy) cout << "������� ";
		else cout << "������� ";
		cout << "��� " << lot_in_deal_ << " ";
		cout << "���� �������� " << opening_price_ << std::endl;
		cout << "���� take profit: " << take_profit_price_ << ", ";
		cout << "���� stop loss: " << stop_loss_price_ << ", ";
		cout << "������� ��� take profit " << take_profit_gale_ << "$, ";
		cout << "������ ��� stop loss " << stop_loss_gale_ << "$" << std::endl;
	}

	// �������:

	bool get_status()
	{
		return status_;
	}

	Constants::deal_type get_type()
	{
		return type_;
	}
	
	double get_stop_loss_price()
	{
		return stop_loss_price_;
	}

	double get_take_profit_price()
	{
		return take_profit_price_;
	}

	double get_stop_loss_gale()
	{
		return stop_loss_gale_;
	}

	double get_take_profit_gale()
	{
		return take_profit_gale_;
	}

	// �������� ������
	void close_the_deal()
	{
		status_ = false;
	}
};

#endif