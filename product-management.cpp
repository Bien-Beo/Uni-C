#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 100;

struct product_time
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct employee
{
    unsigned int employee_id;
    char employee_name[50];
    unsigned short employee_age;
    char employee_gender[10];
    char employee_address[MAX_SIZE];
    unsigned short employee_phoneNumber[10] = {0};
};

struct product
{
    unsigned int product_id;
    char product_name[MAX_SIZE];
    unsigned int product_price;
    struct product_time product_time;
    struct employee producter;
};

void addEmployeeInformation(employee *employee);

void addNewProduct(product *&productList, int &num_of_product);
void addNewProductList(product *&productList, int &num_of_product);
void displayProductList(const product *productList, int num_of_product);
void editProductByName(product *productList, int num_of_product);
void deleteProductByID(product *productList, int *num_of_product);
void findMostContributingID(product *productList, int num_of_product);
void sortProductsByPrice(product *productList, int num_of_product);

void saveProductList();

int main()
{
    unsigned int num_of_product = 1;
    product *productList = (product*)malloc(num_of_product * sizeof(product));
    unsigned int ordinal;
}

void addEmployeeInformation(employee *employee)
{
    printf("\nEnter ID of the Employee: "); 
    scanf("%d", &employee->employee_id); getchar();

    printf("\nEnter the name of the Employee: ");
    fgets(employee->employee_name, sizeof(employee->employee_name) + 1, stdin);

    printf("\nEnter the age of the Employee: ");
    scanf("%d", &employee->employee_age);

    printf("\nEnter the gender of the Employee: ");
    fgets(employee->employee_gender, sizeof(employee->employee_gender) + 1, stdin);

    printf("\nEnter the address of the Employee: ");
    fgets(employee->employee_address, sizeof(employee->employee_address) + 1, stdin);

    printf("\nEnter the phone number of the Employee: ");
    for(int i = 1; i < 10; i++)
        scanf("%d", &employee->employee_phoneNumber[i]); getchar();
}

void addNewProduct(product *&productList, int &num_of_product)
{
    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin);

    printf("\nEnter the Product's manuafacturing date: ");
    scanf("%d%d%d", &new_product.product_time.day, &new_product.product_time.month, &new_product.product_time.year); 

    printf("\nEnter the Producter: ");
    employee new_employee; addEmployeeInformation(&new_employee); new_product.producter = new_employee;

    num_of_product++;
    product *arr_resizable = (product*)malloc(num_of_product * sizeof(product));

    for(int i = 0; i < num_of_product - 1; i++)
        arr_resizable[i] = productList[i];

    arr_resizable[num_of_product - 1] = new_product;
    free(productList);

    productList = arr_resizable;
}

void addNewProductList(product *&productList, int &num_of_product)
{
    unsigned int quantity; scanf("%d", &quantity);
    int newSize = num_of_product + quantity;
    for(int i = num_of_product - 1; i < newSize - 1; i++)
        addNewProduct(productList, num_of_product);
}

void displayProductList(const product *productList, int num_of_product)
{

}

void editProductByName(product *productList, int num_of_product)
{
    bool marker = false;
    unsigned int index_alternative_product;
    char alternative_product_name[100];
    fgets(alternative_product_name, sizeof(alternative_product_name) + 1, stdin);

    for(int index_product = 0; index_product < num_of_product - 2; index_product++)
    {
        for(int index_name_element = 0; index_name_element < MAX_SIZE; index_name_element++)
        {
            if(alternative_product_name[index_name_element] != *(productList + index_product)->product_name[index_name_element])
                break;
            else
            {
                marker = true;
                index_alternative_product = index_product;
            }
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
        employee new_employee; addNewEmployee(&new_employee); alternative_product.producter = new_employee;

        *(productList + index_alternative_product) = alternative_product;
    }
}

void deleteProductByID(product *productList, int *num_of_product)
{
    unsigned int ID_location_of_product_deleted;
    scanf("%d", &ID_location_of_product_deleted);

    for(int index_product = ID_location_of_product_deleted - 1; index_product < num_of_product - 2; index_product++)
        *(productList + ID_location_of_product_deleted) = *(productList + ID_location_of_product_deleted + 1);

    num_of_product--;
}

void findMostContributingID(product *productList, int num_of_product)
{
    unsigned int num_of_emoloyee_id = num_of_product - 1;
    unsigned int arr_employee_id[num_of_emoloyee_id];

    for(int index_product = 0; index_product < num_of_product - 2; index_product++)
        arr_employee_id[index_product] = *(productList + index_product)->producter.employee_id;

    countFrequency(arr_emloyee_id, num_of_emoloyee_id);
}

void countFrequency(unsigned int arr[], unsigned int size)
{
    unsigned int arr_frequency[MAX_SIZE];
    unsigned int unique_elements[MAX_SIZE] = {0};
    unsigned int unique_count = 0;

    for (int i = 0; i < size; i++) 
    {
        bool is_new_element = true;

        for (int j = 0; j < unique_count; j++) 
        {
            if (arr[i] == unique_elements[j]) 
            {
                is_new_element = false;
                break;
            }
        }

        if (is_new_element) 
        {
            unique_elements[unique_count] = arr[i];
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) 
    {
        int count_frequency = 0;

        for (int j = 0; j < size; j++) 
            if (arr[j] == unique_elements[i]) 
                count_frequency++;
                
        arr_frequency[i] = count_frequency;   
    }

    unsigned int largest_frequency = arr_frequency[0];
    unsigned int contribute_value = 0;
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
    for(int i = 0; i < num_of_product - 3; i++)
    {
        for(int j = i + 1; j < num_of_product - 2; j++)
        {
            if(*(productList + i)->product_price > *(productList + j)->product_price)
            {
                product temp_product = *(productList + i);
                *(productList + i) = *(productList + j);
                *(productList + j) = temp_product;
            }
        }
    }
}