#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned short int MAX_SIZE = 100;
const unsigned short int INITIALIZED_SIZE = 1;

struct product_time
{
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;
};

struct employee
{
    unsigned int employee_id;
    char employee_name[50];
    unsigned short employee_age;
    char employee_gender[10];
    char employee_address[MAX_SIZE];
    unsigned short int employee_phoneNumber[10] = {0};
};

struct product
{
    unsigned int product_id;
    char product_name[MAX_SIZE];
    double product_price;
    struct product_time product_time;
    struct employee producter;
};

void addEmployeeInformation(employee *employee);

void addNewProduct(product *&productList, int &num_of_product);
void addNewProductList(product *&productList, int &num_of_product);
void displayProductList(const product *productList, int num_of_product);
void readProductListFromFile(const char *filename, struct Product productList[], int *num_of_product);
void addProductToFile(const char* filename, product *productList, int &num_of_product);
void editProductByName(product *productList, int num_of_product);
void deleteProductByID(product *productList, int *num_of_product);
void updateProductAfterDeletion(const char* filename, const Product *productList, int num_of_product);
void findMostContributingID(product *productList, int num_of_product);
void sortProductsByPrice(product *productList, int num_of_product);
void saveProductList(const product *productList, int num_of_product);
void printMenu();

int main()
{
    product *productList = (product*)malloc(INITIALIZED_SIZE * sizeof(product));
    unsigned int num_of_product = 0;
    unsigned int ordinal;

    while(1)
    {
        printMenu();
        unsigned short int choose;
        printf("Please enter your choice: "); scanf("%d", &choose);

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
            updateProductAfterDeletion("product_list.txt", productList, num_of_product);
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
            readProductListFromFile("product_list.txt", productList, num_of_product);
            displayProductList(productList, num_of_product);
            break;

        case 10:
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
    num_of_product++;
    product *arr_resizable = (product*)malloc(num_of_product * sizeof(product));

    for(int i = 0; i < num_of_product; i++)
        arr_resizable[i] = productList[i];

    free(productList);
    productList = arr_resizable;

    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin);

    printf("\nEnter the Product's manuafacturing date: ");
    scanf("%d%d%d", &new_product.product_time.day, &new_product.product_time.month, &new_product.product_time.year); 

    printf("\nEnter the Producter: ");
    employee new_employee; addEmployeeInformation(&new_employee); new_product.producter = new_employee;

    arr_resizable[num_of_product - 1] = new_product;
}

//void addProductToFile(const char* filename, product *productList, int &num_of_product)
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
        printf("%d, %d, %s, %d, %d/%d/%d, %s\n", i + 1, 
            *(productList + i)->product_id, 
            *(productList + i)->product_name, 
            *(productList + i)->product_price, 
            *(productList + i)->product_time.day, *(productList + i)->product_time.month, *(productList + i)->product_time.year, 
            *(productList + i)->producter.employee_name);
    }
}

//void readProductListFromFile(const char *filename, struct Product productList[], int *num_of_product)
{
    FILE *inputFile = fopen(filename, "r");

    if (inputFile != NULL) 
    {
        while (fscanf(inputFile, "%d, %[^,], %d, %d, %d, %d, %[^,]\n", 
        &productList[*numProducts].product_id, 
        productList[*numProducts].product_name,
        &productList[*numProducts].product_price, 
        &productList[*numProducts].product_time.day, 
        &productList[*numProducts].product_time.month, 
        &productList[*numProducts].product_time.year, 
        productList[*numProducts].producter.employee_name) == 7) 
        {
            (*num_of_product)++;
        }

        fclose(inputFile);
    } 
    else
        fprintf(stderr, "Failed to open the input file.\n");
}

void editProductByName(product *productList, int num_of_product)
{
    bool marker = false;
    unsigned int index_alternative_product;
    char alternative_product_name[MAX_SIZE];
    fgets(alternative_product_name, sizeof(alternative_product_name) + 1, stdin);

    for(int index_product = 0; index_product < num_of_product; index_product++)
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

void deleteProductByID(product *productList, int &num_of_product)
{
    unsigned int ID_location_of_product_deleted;
    scanf("%d", &ID_location_of_product_deleted);

    for(int index_product = ID_location_of_product_deleted - 1; index_product < num_of_product; index_product++)
        *(productList + index_product) = *(productList + index_product + 1);

    num_of_product--;
}

//void updateProductAfterDeletion(const char* filename, const Product *productList, int num_of_product)
{
    FILE *file = fopen(filename, "w");

    if (inputFile != NULL) 
    {
        for(int i = 0; i < num_of_product - 2; i++)
            fprintf(outputFile, "%d, %s, %d, %d, %d, %d, %s\n", 
            productList->product_id, 
            productList->product_name,
            productList->product_price, 
            productList->product_time.day, 
            productList->product_time.month, 
            productList->product_time.year, 
            productList->producter.employee_name);

        fclose(file);
    }
    else
        fprintf(stderr, "Failed to open the input file.\n");
}

void findMostContributingID(product *productList, int num_of_product)
{
    unsigned int num_of_emoloyee_id = num_of_product;
    unsigned int arr_employee_id[num_of_emoloyee_id];

    for(int index_product = 0; index_product < num_of_product; index_product++)
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
    for(int i = 0; i < num_of_product - 1; i++)
    {
        for(int j = i + 1; j < num_of_product; j++)
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

void saveProductList(const product *productList, int num_of_product)
{
    FILE *output_file = fopen("product_list.txt", "w");

    if(output_file != NULL)
    {
        for(int i = 0; i < num_of_product - 2; i++)
        {
            fprintf(output_file, "%d, %d, %s, %d, %d/%d/%d, %s\n", i + 1, 
            *(productList + i)->product_id, 
            *(productList + i)->product_name, 
            *(productList + i)->product_price, 
            *(productList + i)->product_time.day, *(productList + i)->product_time.month, *(productList + i)->product_time.year, 
            *(productList + i)->producter.employee_name);
        }
        printf("Product list saved successfully.\n");
        fclose(output_file);
    }
    else
        fprintf(stderr, "Failed to open the output file.\n");
}

void printMenu()
{
    printf("======================================================================\n");
    printf("==================*** PRODUCT MANAGEMENT PROGRAM ***==================\n");
    printf("======================================================================\n\n");

    printf("+----------+---------------------------------------------------------+\n");
    printf(":   S No.  + FUNCTION                                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   1st    + Create a new product                                    :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    + Create a new product list                               :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    + Displays a list of products                             :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   4th    + Update product information that needs fixing            :\n"); 
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   5th    + Delete the product                                      :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   6th    + Find the ID of the employee with the most contributions :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   7th    + Sort products by price                                  :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   8th    + Save product list to the system                         :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   9th    + Displays the list of available products on the system   :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   10th   + Exit the program                                        :\n");
    printf("+----------+---------------------------------------------------------+\n");

    printf("\n======================================================================");
}