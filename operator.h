#define NUMBER_OF_OPERATOR_ACTIONS 3

enum OperatorActions
{
	OPERATOR_ADD_MONEY,
	OPERATOR_SUB_MONEY,
	OPERATOR_EXIT
};

extern enum OperatorActions  operator_acts[];
extern enum OperatorActions operatorActions;

extern QUERY SELECT_ACCOUNT_BY_ID;
extern QUERY ADD_MONEY;
extern QUERY SUB_MONEY;

void operator_action_menu();
void operator_actions();

void show_account();
void add_money();
void sub_money();