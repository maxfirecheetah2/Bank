#include "common.h"


enum AdminActions admin_acts[] = 
{
	ADMIN_CREATE_CLIENT,
	ADMIN_DELETE_CLIENT,
	ADMIN_ADD_ACCOUNT,
	ADMIN_DELETE_ACCOUNT,
	ADMIN_LIST_CLIENTS,
	ADMIN_EXIT
};
enum AdminActions adminActions;

const char* ADD_CLIENT = "INSERT INTO client (CLIENT_ID,FIRST_NAME,LAST_NAME) VALUES (?, ?, ?);";
const char* SELECT_CLIENT_BY_ID = "SELECT * FROM client WHERE client_id=?;";
const char* SELECT_ALL_CLIENTS = "SELECT * FROM client;";
const char* DELETE_CLIENT_BY_ID = "DELETE FROM client WHERE client_id=?;";

//add a client to database
void create_client()
{  
	//fprintf(stdout, "create client started...");//debug
	int rc;
	char* first_name = (char*)malloc(sizeof(char) * 128);
	char* last_name = (char*)malloc(sizeof(char) * 128);

	fprintf(stdout, "\Please input first name of client\nadmin->");
	fscanf(stdin, "%s", first_name);
	fprintf(stdout, "Please input last name of client\nadmin->");
	fscanf(stdin,"%s", last_name);
	
	if(sqlite3_prepare(conn, ADD_CLIENT, strlen(ADD_CLIENT), &stmt, NULL) == SQLITE_OK) 
	{
		if(sqlite3_bind_text(stmt, 2, first_name, -1, 0) == SQLITE_OK &&
			sqlite3_bind_text(stmt, 3, last_name, -1, 0) == SQLITE_OK) 
		{
			rc = sqlite3_step(stmt);
			fprintf(stdout, "Client has been created\n\n");
		}
		else
		{
			fprintf(stdout, "Client has NOT been created, try again!\n\n");
		}
	}
	else
	{
		fprintf(stdout, "Client has NOT been created, try again!\n\n");
	}
	free(first_name);
	free(last_name);
	sqlite3_reset(stmt);
	
}
void delete_client() 
{
	int rc;
	char* client_id = (char*)malloc(sizeof(char) * 16);
	fprintf(stdout, "Please input client id!\nadmin->");
	fscanf(stdin, "%s", client_id);

	if((rc=sqlite3_prepare(conn, DELETE_CLIENT_BY_ID, strlen(DELETE_CLIENT_BY_ID), &stmt, NULL)) == SQLITE_OK) 
	{
		if(sqlite3_bind_text(stmt, 1, client_id, -1, 0) == SQLITE_OK) 
		{
			if(sqlite3_step(stmt) == SQLITE_DONE)
			{
				fprintf(stdout, "Client deleted!\n\n");
			}
		}
	}
			
	free(client_id);
	sqlite3_reset(stmt);
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


void admin_action_menu()
{
	fprintf(stdout, "\nOperation list:");
	fprintf(stdout, "\n1 : create client");
	fprintf(stdout, "\n2 : delete client");
	fprintf(stdout, "\n3 : add account");
	fprintf(stdout, "\n4 : delete account");
	fprintf(stdout, "\n5 : list clients");
	fprintf(stdout, "\n6 : exit");
	fprintf(stdout, "\nPlease, enter an operation number\n");
}