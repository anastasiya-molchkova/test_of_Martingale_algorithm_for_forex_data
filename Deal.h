#ifndef DEAL
#define DEAL

#include "Constants.h"
#include <iostream>

using std::cout;

// класс Сделка
class Deal
{
private:
	Constants::deal_type type_;
	bool status_;               // истина = если открыта, ложь - если закрыта
	double lot_in_deal_;
	double opening_price_;
	double take_profit_price_;
	double stop_loss_price_;
	double take_profit_gale_;
	double stop_loss_gale_;
public:
	// конструктор по умолчанию использовать не даём:
	Deal() = delete;
	// конструктор
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
		// !!! так как стоп лосс больше тэйк профита на 1 коридор, то и потенциальные потери будут выше потенциальной прибыли, увы!
	}

	void print()
	{
		if (type_ == Constants::buy) cout << "покупка ";
		else cout << "продажа ";
		cout << "лот " << lot_in_deal_ << " ";
		cout << "цена открытия " << opening_price_ << std::endl;
		cout << "цена take profit: " << take_profit_price_ << ", ";
		cout << "цена stop loss: " << stop_loss_price_ << ", ";
		cout << "прибыль при take profit " << take_profit_gale_ << "$, ";
		cout << "потери при stop loss " << stop_loss_gale_ << "$" << std::endl;
	}

	// ГЕТТЕРЫ:

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

	// закрытие сделки
	void close_the_deal()
	{
		status_ = false;
	}
};

#endif