//To add an action we must add it to both enum AdminActions
//and array admin_acts !!IN THE SAME ORDER!!.
//We  must also increment predefined value NUMBER_OF_ADMIN_ACTIONS
#define NUMBER_OF_ADMIN_ACTIONS 6

enum AdminActions
{
	ADMIN_CREATE_CLIENT,
	ADMIN_DELETE_CLIENT,
	ADMIN_ADD_ACCOUNT,
	ADMIN_DELETE_ACCOUNT,
	ADMIN_LIST_CLIENTS,
	ADMIN_EXIT
};

extern enum AdminActions  admin_acts[];
extern enum AdminActions adminActions;

extern const char* ADD_CLIENT;
extern const char* SELECT_CLIENT_BY_ID;
extern const char* SELECT_ALL_CLIENTS;
extern const char* DELETE_CLIENT_BY_ID;

void admin_action_menu();
void admin_actions();

void create_client();
void delete_client();