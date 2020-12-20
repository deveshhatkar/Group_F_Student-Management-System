#include "db.h"

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w+",stdout);
	freopen("error.txt","w+",stderr);
	int ret_code = app_start("../config/configuration_file.txt");
	return ret_code;
}