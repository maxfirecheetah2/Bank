#include "common.h"


//for authentification
const char* SELECT_PASSWORD_BY_NAME = "SELECT password, role FROM bank_personal WHERE login=?;";

enum roleInSystem { ROLE_UNKNOWN, ROLE_ADMIN, ROLE_OPERATOR };
enum roleInSystem role_in_system [] = { ROLE_UNKNOWN, ROLE_ADMIN, ROLE_OPERATOR };

//theoratically for logging
struct currentUser
{
	int id;
	char username[128];
	char password[128];
	enum roleInSystem roleIdentified;
};

struct currentUser cur_user;

void login()
{
	int rc;
	//char* username = (char*)malloc(sizeof(char) * 128);
	//char* password = (char*)malloc(sizeof(char) * 128);
	struct currentUser cu;

	//login and password from db
	char* db_password = (char*)malloc(sizeof(char) * 128);
	int db_role = -1;

	fprintf(stdout, "\nPlease, sign in\n");
	for(;;)
	{
		fprintf(stdout, "\nlogin : ");
		fscanf(stdin,"%s", cu.username);
		fprintf(stdout, "password : ");
		fscanf(stdin, "%s", cu.password);

		if((rc=sqlite3_prepare(conn, SELECT_PASSWORD_BY_NAME, strlen(SELECT_PASSWORD_BY_NAME), &stmt, NULL)) == SQLITE_OK) 
		{
			if(sqlite3_bind_text(stmt, 1, cu.username, -1, 0) == SQLITE_OK) 
			{
				if(sqlite3_step(stmt) == SQLITE_ROW)
				{
					db_password = (char*)sqlite3_column_text(stmt, 0);
					db_role = sqlite3_column_int(stmt, 1);
					cu.roleIdentified = role_in_system[db_role];
					if(cu.roleIdentified == ROLE_ADMIN)
					{
						fprintf(stdout, "!Role : %d\n", db_role);
					}
					fprintf(stdout, "%s %d\n", db_password, db_role);
				}
			}
		}

		if(strcmp(cu.password, db_password) == 0)
		{
			break;
		}
		else
		{
			fprintf(stdout, "Incorrect login or password! Try again.\n");
		}
	}
}

void logout()
{
	cur_user.roleIdentified = ROLE_UNKNOWN;
}

void admin_actions(){

	int isExit = 0;
	admin_action_menu();
	while(!isExit)
	{
		int current_action = -1;
		fscanf(stdin, "%d", &current_action);
		fprintf(stdout, "%d\n", current_action);
		if(current_action >= 1 && current_action <= NUMBER_OF_ADMIN_ACTIONS)
		{
			adminActions = admin_acts[current_action - 1];
		}
		switch(adminActions)
		{
			case ADMIN_CREATE_CLIENT:
				create_client();
				break;
			case ADMIN_DELETE_CLIENT:
				delete_client();
				break;
			case ADMIN_ADD_ACCOUNT:
				//add_account();
				break;
			case ADMIN_EXIT:
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


int main()
{
	cur_user.roleIdentified = ROLE_ADMIN;
	connection();
	for(;;)
	{	
		//login();
		switch(cur_user.roleIdentified)
		{
			case(ROLE_ADMIN):
				admin_actions();
				break;
			case(ROLE_OPERATOR):
				//operator_actions();
				break;
			case(ROLE_UNKNOWN):
				fprintf(stdout, "Authentification failed! Try again.");
				break;
		}
	}
	sqlite3_close(conn);
	system("pause");
	return EXIT_SUCCESS;

}
