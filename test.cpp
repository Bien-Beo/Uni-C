struct customer
{
	char name[25];
	int id;
	char address[50];
	int point = 0;
	int sale = 0;
};

struct employee
{
    int employee_id;
    char employee_name[NAME_LENGTH];
    int employee_age;
    char employee_gender[10];
    char employee_address[NAME_LENGTH];
    char employee_phoneNumber[10] = {0};
    int num_products_made;
};

