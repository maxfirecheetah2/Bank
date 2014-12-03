#include "common.h"



//for authentification
QUERY SELECT_PASSWORD_BY_NAME = "SELECT password, role FROM bank_personal WHERE login=?;";

enum roleInSystem role_in_system [] = { ROLE_UNKNOWN, ROLE_ADMIN, ROLE_OPERATOR };
struct currentUser cu;


void login()
{
	int rc;
	//char* username = (char*)malloc(sizeof(char) * 128);
	//char* password = (char*)malloc(sizeof(char) * 128);
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
					//fprintf(stdout, "%s %d\n", db_password, db_role);
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
	cu.roleIdentified = ROLE_UNKNOWN;
}


