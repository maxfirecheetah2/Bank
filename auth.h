

//for authentification
extern QUERY SELECT_PASSWORD_BY_NAME;

enum roleInSystem { ROLE_UNKNOWN, ROLE_ADMIN, ROLE_OPERATOR };
extern enum roleInSystem role_in_system [];

//theoratically for logging
struct currentUser
{
	int id;
	char username[128];
	char password[128];
	enum roleInSystem roleIdentified;
};

extern struct currentUser cu;

void login();
void logout();