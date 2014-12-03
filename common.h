#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifndef QUERY
#define QUERY const char*
#endif

#include "sqlite3.h"
#include "conn.h"
#include "admin.h"
#include "auth.h"
#include "operator.h"

