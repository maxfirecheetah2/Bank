#include "common.h"

int main()
{
	connection(); 
	for(;;)
	{	
		login();
		switch(cu.roleIdentified)
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
