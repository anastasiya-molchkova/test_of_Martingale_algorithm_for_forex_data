#ifndef CONSTANTS
#define CONSTANTS
namespace Constants
{
	enum deal_type {sell = 0, buy};                                // типы сделок - продажа и покупка
	// варианты завершения торгов:
	enum cycle_return { profit = 1, no_profit, budget_finished, file_finished};
	const double small_value = 0.000001;                           // для сравнения цен
	const unsigned total_budget = 1000;                            // доллары
	const unsigned short percent_of_risk = 10;                     // процент
	const double minimal_lot = 0.01;                               // доля, лот
	const unsigned corridor = 100;                                 // пункты
	const unsigned take_profit_level = 2*corridor;               // пункты
	// !!! так как стоп лосс больше тэйк профита на 1 коридор, то и потенциальные потери будут выше потенциальной прибыли, увы!
	const unsigned stop_loss_level = take_profit_level + corridor; // пункты
	const double one_point_with_one_lot = 1;                       // доллары
	const double one_point_as_price = 0.00001;                     // фунты
	const unsigned number_of_blocked_data = 100;                   // количество данных в конце файла, с которых запрещаем создавать цикл
	const unsigned tries_number = 100;                             // количество попыток для запуска статистики
}
#endif
