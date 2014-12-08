#include "common.h"

enum OperatorActions  operator_acts[] = 
{
	OPERATOR_ADD_MONEY,
	OPERATOR_SUB_MONEY,
	OPERATOR_EXIT
};

enum OperatorActions operatorActions;

QUERY SELECT_ACCOUNT_BY_ID = "SELECT * FROM account a INNER JOIN client c ON a.client_id=c.client_id WHERE a.account_id = ?";
QUERY ADD_MONEY = "UPDATE account SET balance = balance + ? WHERE account_id = ?";
QUERY SUB_MONEY = "UPDATE account SET balance = balance - ? WHERE account_id = ?";

void show_account(int account_id)
{
	int rc;

	char* first_name = (char*)malloc(sizeof(char) * 128);
	char* last_name = (char*)malloc(sizeof(char) * 128);
	char* transactions = (char*)malloc(sizeof(char) * 128);
	char* balance = (char*)malloc(sizeof(char) * 128);

	if((rc=sqlite3_prepare(conn, SELECT_ACCOUNT_BY_ID, strlen(SELECT_ACCOUNT_BY_ID), &stmt, NULL)) == SQLITE_OK) 
	{
		if(sqlite3_bind_int(stmt, 1, account_id) == SQLITE_OK) 
		{
			sqlite3_step(stmt);
			balance = (char*)sqlite3_column_text(stmt, 2);
			transactions = (char*)sqlite3_column_text(stmt, 3);
			first_name = (char*)sqlite3_column_text(stmt, 5);
			last_name = (char*)sqlite3_column_text(stmt, 6);
			fprintf(stdout, "Id: %d, balance: %s, current transactions: %s \n\t", account_id,  balance, transactions);
			fprintf(stdout, "Client name: %s, client surname: %s\n", first_name, last_name);			
		}
	}
	/*free(first_name);
	free(last_name);
	free(transactions);	
	free(balance);*/
	sqlite3_reset(stmt);

}
void add_money()
{
	int account_id;
	int increase;
	int rc;

	show_account_list();	
	fprintf(stdout, "Please input an account id!\noperator->");
	fscanf(stdin, "%d", &account_id);
	show_account(account_id);
	
	fprintf(stdout, "\nPlease input an amount!\noperator->");
	fscanf(stdin, "%d", &increase);
	
	if((rc=sqlite3_prepare(conn, ADD_MONEY, strlen(ADD_MONEY), &stmt, NULL)) == SQLITE_OK) 
	{
		if(sqlite3_bind_int(stmt, 1, increase) == SQLITE_OK && sqlite3_bind_int(stmt, 2, account_id) == SQLITE_OK) 
		{
			if(sqlite3_step(stmt) == SQLITE_DONE)
			{
				fprintf(stdout, "\nAccount updated!\n\n");
			}
		}
	}
	show_account(account_id);

	sqlite3_reset(stmt);
}

void sub_money()
{
	int account_id;
	int decrease;
	int rc;

	show_account_list();	
	fprintf(stdout, "Please input an account id!\noperator->");
	fscanf(stdin, "%d", &account_id);
	show_account(account_id);

	
	fprintf(stdout, "\nPlease input an amount!\noperator->");
	fscanf(stdin, "%d", &decrease);
	
	if((rc=sqlite3_prepare(conn, SUB_MONEY, strlen(SUB_MONEY), &stmt, NULL)) == SQLITE_OK) 
	{
		if(sqlite3_bind_int(stmt, 1, decrease) == SQLITE_OK && sqlite3_bind_int(stmt, 2, account_id) == SQLITE_OK) 
		{
			if(sqlite3_step(stmt) == SQLITE_DONE)
			{
				fprintf(stdout, "\nAccount updated!\n\n");
			}
		}
	}
	show_account(account_id);
			
	sqlite3_reset(stmt);
}

void operator_actions(){

	int isExit = 0;
	while(!isExit)
	{
		int current_action = -1;
		operator_action_menu();
		fscanf(stdin, "%d", &current_action);
		if(current_action >= 1 && current_action <= NUMBER_OF_OPERATOR_ACTIONS)
		{
			operatorActions = operator_acts[current_action - 1];
		}
		switch(operatorActions)
		{
			case OPERATOR_ADD_MONEY:
				add_money();
				break;
			case OPERATOR_SUB_MONEY:
				sub_money();
				break;
			case OPERATOR_EXIT:
				fprintf(stdout, "Session was ended...");
				logout();
				isExit = 1;
				break;
			default:
				fprintf(stdout, "Unknown operation.Try again.");
				break;
		}
	}
}


void operator_action_menu()
{
	fprintf(stdout, "\nSelect operation:");
	fprintf(stdout, "\n1 : add money");
	fprintf(stdout, "\n2 : subtract money");
	fprintf(stdout, "\n3 : exit");
	fprintf(stdout, "\nPlease, enter an operation number\n");
}