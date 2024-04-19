#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT 100
#define INITIALIZED_SIZE 1

struct product_time
{
    int day;
    int month;
    int year;
};

struct employee
{
    int employee_id;
    char employee_name[50];
    int employee_age;
    char employee_gender[10];
    char employee_address[MAX_PRODUCT];
    int employee_phoneNumber[10] = {0};
};

struct product
{
    int product_id;
    char product_name[MAX_PRODUCT];
    double product_price;
    struct product_time product_time;
    struct employee producter;
};

void addEmployeeInformation(employee *employee);
void addNewProduct(product *&productList, int &num_of_product);
void addNewProductList(product *&productList, int &num_of_product);
void displayProductList(const product *productList, int num_of_product);
int readProductListFromFile(const char *filename, struct product *system_product_list, int maxProducts);
void addProductToFile(const char* filename, product *productList, int &num_of_product);
void editProductByName(product *productList, int num_of_product);
void deleteProductByID(product *&productList, int &num_of_product);
void findMostContributingID(product *productList, int num_of_product);
void sortProductsByPrice(product *productList, int num_of_product);
void saveProductList(const product *productList, int num_of_product);
void printMenu();

bool checkTime(const product &product);
int checkPrice(const product &product);
bool checkEmployeeAge(employee &employee);
bool checkEmployeePhoneNumber(employee &employee, int index_number);

int main()
{
    product *productList = (product*)malloc(INITIALIZED_SIZE * sizeof(product));
    int num_of_product = 0;
    int ordinal;

    product system_product_list[MAX_PRODUCT];
    int num_products_system = 0;

    while(1)
    {
        printMenu();
        int choose;
        printf("\nPlease enter your choice: "); scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            addNewProduct(productList, num_of_product);
            break;

        case 2:
            addNewProductList(productList, num_of_product);
            break;

        case 3:
            displayProductList(productList, num_of_product);
            break;

        case 4:
            editProductByName(productList, num_of_product);
            break;

        case 5:
            deleteProductByID(productList, num_of_product);
            break;

        case 6:
            findMostContributingID(productList, num_of_product);
            break;

        case 7:
            sortProductsByPrice(productList, num_of_product);
            break;

        case 8:
            saveProductList(productList, num_of_product);
            break;

        case 9:
            {
                num_products_system = readProductListFromFile("product_list.txt", system_product_list, MAX_PRODUCT);
                displayProductList(system_product_list, num_products_system);
            }
            break;

        case 10:
            addProductToFile("product_list.txt", productList, num_of_product);
            break;

        case 0:
            free(productList);
            return 0;

        default:
            free(productList);
            return 0;
        }
    }
}

void addEmployeeInformation(employee *employee)
{
    printf("\nEnter ID of the Employee: "); 
    scanf("%d", &employee->employee_id); getchar();

    printf("\nEnter the name of the Employee: ");
    fgets(employee->employee_name, sizeof(employee->employee_name) + 1, stdin);

    printf("\nEnter the age of the Employee: ");
    scanf("%d", &employee->employee_age); getchar();

    do
    {
        printf("\nEnter the age of the Employee: ");
        scanf("%d", &employee->employee_age); getchar();
        if(checkEmployeeAge(*employee) == false)
            printf("\nError: Age is not within the working age range !");
    } while (!checkEmployeeAge(*employee));

    printf("\nEnter the gender of the Employee: ");
    fgets(employee->employee_gender, sizeof(employee->employee_gender) + 1, stdin);

    printf("\nEnter the address of the Employee: ");
    fgets(employee->employee_address, sizeof(employee->employee_address) + 1, stdin);

    printf("\nEnter the phone number of the Employee: ");
    for(int i = 1; i < 10; i++)
    {
        do
        {
            scanf("%d", &employee->employee_phoneNumber[i]);
            if(!checkEmployeePhoneNumber(*employee, i))
                printf("\nError: Wrong phone number format !"); 
        } while (!checkEmployeePhoneNumber(*employee, i));
    }
    getchar();
}

void addNewProduct(product *&productList, int &num_of_product)
{
    num_of_product++;
    product *arr_resizable = (product*)malloc(num_of_product * sizeof(product));

    for(int i = 0; i < num_of_product - 1; i++)
        *(arr_resizable + i) = productList[i];

    free(productList);
    productList = arr_resizable;

    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin);

    do
    {
        printf("\nEnter the product's price: ");
        scanf("%lf", &new_product.product_price); getchar();
        if(!checkPrice(new_product))
            printf("\nError: The product's price is a non-negative number !");
    } while (!checkPrice(new_product));

    do
    {
        printf("\nEnter the Product's manuafacturing date: ");
        scanf("%d%d%d", &new_product.product_time.day, &new_product.product_time.month, &new_product.product_time.year);
        if(!checkTime(new_product))
            printf("\nError: Incorrect time format !");
    } while (!checkTime(new_product));

    printf("\nEnter the Producter: ");
    employee new_employee; addEmployeeInformation(&new_employee); new_product.producter = new_employee;

    arr_resizable[num_of_product - 1] = new_product;
}

void addProductToFile(const char* filename, product *productList, int &num_of_product)
{
    FILE* outputFile = fopen(filename, "a");
    if (outputFile == NULL) 
    {
        printf("Không thể mở tệp.\n");
        return;
    }

    addNewProduct(productList, num_of_product);

    fprintf(outputFile, "%d, %s, %d, %d, %d, %d, %s\n", 
        productList->product_id, 
        productList->product_name,
        productList->product_price, 
        productList->product_time.day, 
        productList->product_time.month, 
        productList->product_time.year, 
        productList->producter.employee_name);

    fclose(outputFile);
}

void addNewProductList(product *&productList, int &num_of_product)
{
    unsigned int quantity; scanf("%d", &quantity);
    int newSize = num_of_product + quantity;
    for(int i = num_of_product; i < newSize; i++)
        addNewProduct(productList, num_of_product);
}

void displayProductList(const product *productList, int num_of_product)
{
    for(int i = 0; i < num_of_product; i++)
    {
        printf("%d, %s, %.2lf, %d/%d/%d, %s\n",
            (*(productList + i)).product_id, 
            (*(productList + i)).product_name, 
            (*(productList + i)).product_price, 
            (*(productList + i)).product_time.day, (*(productList + i)).product_time.month, (*(productList + i)).product_time.year, 
            (*(productList + i)).producter.employee_name);
    }
}

int readProductListFromFile(const char *filename, product *system_product_list, int maxProducts)
{
    FILE *inputFile = fopen(filename, "r");

    if (inputFile == NULL) 
    {
        printf("Could not open file.\n");
        return 0;
    }

    int num_products_system = 0;

    while (fscanf(inputFile, "%d, %[^,], %d, %d, %d, %d, %[^,]\n", 
        &system_product_list[num_products_system].product_id, 
        system_product_list[num_products_system].product_name,
        &system_product_list[num_products_system].product_price, 
        &system_product_list[num_products_system].product_time.day, 
        &system_product_list[num_products_system].product_time.month, 
        &system_product_list[num_products_system].product_time.year, 
        system_product_list[num_products_system].producter.employee_name) == 7) 
    {
        num_products_system++;
        if (num_products_system >= maxProducts) break;
    }

    fclose(inputFile);
    return num_products_system;
}

void editProductByName(product *productList, int num_of_product)
{
    bool marker = false;
    int index_alternative_product;
    char alternative_product_name[MAX_PRODUCT];

    printf("\nEnter the name of the alternative Product: "); getchar();
    fgets(alternative_product_name, sizeof(alternative_product_name) + 1, stdin);

    for(int index_product = 0; index_product < num_of_product; index_product++)
    {
        int result = strcmp(alternative_product_name, (productList[index_product].product_name));
        if(result != 0)
        {
            printf("\nError: The requested product name was not found !");
            break;
        }
        else
        {
            marker = true;
            index_alternative_product = index_product;
        }
    }

    if(marker)
    {
        product alternative_product;

        printf("\nEnter ID of the Product: "); 
        scanf("%d", &alternative_product.product_id); getchar();

        printf("\nEnter the name of the Product: "); 
        fgets(alternative_product.product_name, sizeof(alternative_product.product_name) + 1, stdin);

        printf("\nEnter the Product's manuafacturing date: ");
        scanf("%d%d%d", &alternative_product.product_time.day, &alternative_product.product_time.month, &alternative_product.product_time.year); 

        printf("\nEnter the Producter: ");
        employee new_employee; addEmployeeInformation(&new_employee); alternative_product.producter = new_employee;

        *(productList + index_alternative_product) = alternative_product;
    }
}

void deleteProductByID(product *&productList, int &num_of_product)
{
    int ID_location_of_product_deleted;
    printf("\nEnter the ID of the product to delete: ");
    scanf("%d", &ID_location_of_product_deleted); getchar();

    if(ID_location_of_product_deleted != productList->product_id)
    {
        printf("\nError: Cannot find product ID to delete !");
    }
    else
    {
        for(int index_product = ID_location_of_product_deleted - 1; index_product < num_of_product; index_product++)
        *(productList + index_product) = *(productList + (index_product + 1));

        num_of_product--;
    }
}

void findMostContributingID(product *productList, int num_of_product)
{
    int num_of_emoloyee_id = num_of_product;
    int arr_employee_id[num_of_emoloyee_id];

    for(int index_product = 0; index_product < num_of_product; index_product++)
        arr_employee_id[index_product] = productList[index_product].producter.employee_id;

    //countFrequency(arr_emloyee_id, num_of_emoloyee_id);
    int arr_frequency[MAX_PRODUCT];
    int unique_elements[MAX_PRODUCT] = {0};
    int unique_count = 0;

    for (int i = 0; i < num_of_emoloyee_id; i++) 
    {
        bool is_new_element = true;

        for (int j = 0; j < unique_count; j++) 
        {
            if (arr_employee_id[i] == unique_elements[j]) 
            {
                is_new_element = false;
                break;
            }
        }

        if (is_new_element) 
        {
            unique_elements[unique_count] = arr_employee_id[i];
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) 
    {
        int count_frequency = 0;

        for (int j = 0; j < num_of_emoloyee_id; j++) 
            if (arr_employee_id[j] == unique_elements[i]) 
                count_frequency++;
                
        arr_frequency[i] = count_frequency;   
    }

    int largest_frequency = arr_frequency[0];
    int contribute_value = 0;
    for(int i = 1; i < unique_count; i++)
    {
        if(largest_frequency < arr_frequency[i])
        {
            largest_frequency = arr_frequency[i];
            contribute_value = i;
        }
    }

    printf("ID of the employee who contributed the most based on the number of products produced: %d", unique_elements[contribute_value]);
    printf("The contribution amount of ID %d = %d", unique_elements[contribute_value], largest_frequency);
}

void sortProductsByPrice(product *productList, int num_of_product)
{
    for(int i = 0; i < num_of_product - 1; i++)
    {
        for(int j = i + 1; j < num_of_product; j++)
        {
            if((productList + i)->product_price > (productList + j)->product_price)
            {
                product temp_product = *(productList + i);
                *(productList + i) = *(productList + j);
                *(productList + j) = temp_product;
            }
        }
    }
}

void saveProductList(const product *productList, int num_of_product)
{
    FILE *output_file = fopen("product_list.txt", "w");

    if(output_file != NULL)
    {
        for(int i = 0; i < num_of_product; i++)
        {
            fprintf(output_file, "%d, %s, %d, %d/%d/%d, %s\n",
            (productList + i)->product_id, 
            (productList + i)->product_name, 
            (productList + i)->product_price, 
            (productList + i)->product_time.day, (productList + i)->product_time.month, (productList + i)->product_time.year, 
            (productList + i)->producter.employee_name);
        }
        printf("Product list saved successfully.\n");
        fclose(output_file);
    }
    else
        fprintf(stderr, "Failed to open the output file.\n");
}

bool checkTime(const product &product)
{
    if(product.product_time.day <= 0 || product.product_time.month <= 0 || product.product_time.year <= 0) 
        return false;
    if(product.product_time.month == 4 || product.product_time.month == 6 || product.product_time.month == 9 || product.product_time.month == 11)
        if(product.product_time.day >= 30) 
            return false;
    else if(product.product_time.month == 2)
    {
        if(product.product_time.year % 4 != 0 && product.product_time.day > 28) 
            return false;
        else if(product.product_time.year % 4 == 0 && product.product_time.day > 29) 
            return false;
    }
    else if(product.product_time.month > 12 || product.product_time.day > 31) 
        return false;
    else if(product.product_time.year < 1000 || product.product_time.year > 9999)
        return false;
    return true;
}

int checkPrice(const product &product)
{
    return product.product_price >= 0;
}

bool checkEmployeeAge(employee &employee)
{
    if(employee.employee_age > 65 || employee.employee_age < 18)
        return false;
    return true;
}

bool checkEmployeePhoneNumber(employee &employee, int index_number)
{
    if(employee.employee_phoneNumber[index_number] < 0 || employee.employee_phoneNumber[index_number] > 9)
        return false;
    return true;
}

void printMenu()
{
    printf("\n======================================================================\n");
    printf("==================*** PRODUCT MANAGEMENT PROGRAM ***==================\n");
    printf("======================================================================\n\n");

    printf("+----------+---------------------------------------------------------+\n");
    printf(":   S No.  + FUNCTION                                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   1st    : Create a new product                                    :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    : Create a new product list                               :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    : Displays a list of products                             :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   4th    : Update product information that needs fixing            :\n"); 
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   5th    : Delete the product by ID                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   6th    : Find the ID of the employee with the most contributions :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   7th    : Sort products by price                                  :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   8th    : Save product list to the system                         :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   9th    : Displays the list of available products on the system   :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   10st   : Create new products on the system (Quick feature)       :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":    0     : Exit the program                                        :\n");
    printf("+----------+---------------------------------------------------------+\n");

    printf("\n======================================================================");
}
