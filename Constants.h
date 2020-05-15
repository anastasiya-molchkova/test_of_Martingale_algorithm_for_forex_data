#ifndef CONSTANTS
#define CONSTANTS
namespace Constants
{
	enum deal_type {sell = 0, buy};                                // ���� ������ - ������� � �������
	// �������� ���������� ������:
	enum cycle_return { profit = 1, no_profit, budget_finished, file_finished};
	const double small_value = 0.000001;                           // ��� ��������� ���
	const unsigned total_budget = 1000;                            // �������
	const unsigned short percent_of_risk = 10;                     // �������
	const double minimal_lot = 0.01;                               // ����, ���
	const unsigned corridor = 100;                                 // ������
	const unsigned take_profit_level = 2*corridor;               // ������
	// !!! ��� ��� ���� ���� ������ ���� ������� �� 1 �������, �� � ������������� ������ ����� ���� ������������� �������, ���!
	const unsigned stop_loss_level = take_profit_level + corridor; // ������
	const double one_point_with_one_lot = 1;                       // �������
	const double one_point_as_price = 0.00001;                     // �����
	const unsigned number_of_blocked_data = 100;                   // ���������� ������ � ����� �����, � ������� ��������� ��������� ����
	const unsigned tries_number = 100;                             // ���������� ������� ��� ������� ����������
}
#endif
