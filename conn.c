#include "common.h"

//establish connection
void connection() 
{	
    char *zErrMsg = 0;
    int rc; 
    rc = sqlite3_open("12.db", &conn);
    if(rc)
	{
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(conn));
    }
	else
	{ 
      fprintf(stderr, "Database has been loaded successfully...\n");
    }   
}
