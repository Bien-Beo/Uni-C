#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NAME_LENGTH 100

struct product_time
{
    int day;
    int month;
    int year;
};

struct employee
{
    int employee_id;
    char employee_name[NAME_LENGTH];
    int employee_age;
    char employee_gender[10];
    char employee_address[NAME_LENGTH];
    char employee_phoneNumber[10];
    int num_products_made;
};

struct product
{
    int product_id;
    char product_name[NAME_LENGTH];
    double product_price;
    struct product_time product_time;
    struct employee *employee;
    int key;
};

struct node
{
    employee data;
    struct node *pNext;
};

typedef struct singlyLinkedList
{
    node *pHead;
    node *pTail;
} singeList;

void initEmployeeInformation(employee *employee);
node *creatNewNode(employee employee);
void linkInitialization(singeList &employeeList);
bool isEmpty(singeList &employeeList);
void addNewEmployee(singeList &employeeList, employee newEmployee);
void addNewEmployeeList(singeList &employeeList, employee employee);
void addNewEmployeeListToFile(singeList &employeeList, employee newEmployee);
void displayEmployeeList(singeList &employeeList);
void sortEmployeesByProductCount(singeList &employeeList);
void swapDataNode(node *node_1, node *node_2);
bool checkEmployeePhoneNumber(const employee employee);
bool checkEmployeeAge(employee &employee);
bool isDuplicateID(const singeList &employeeList, int id);
void deleteNodeDataByID(singeList &employeeList, employee *employee);
void deleteLinkedList(singeList &employeeList);
void readEmployeeListFromFile(singeList &employeeList);
void saveEmployeeList(const singeList &employeeList);

void addNewProduct(product *&productList, int &num_of_product, singeList &employeeList);
void addNewProductList(product *&productList, int &num_of_product, singeList &employeeList);
void addNewProductToFile(product *&productList, int &num_of_product, product *newProduct);
void displayProductList(const product *productList, int num_of_product, singeList &employeeList);
void editProductByName(product *productList, int num_of_product);
void deleteProductByID(product *&productList, int &num_of_product, singeList &employeeList);
void deleteProductList(struct product *&productList, int &num_of_product);
void sortProductsByPrice(product *productList, int num_of_product);
void readProductListFromFile(product *&productList, int &num_of_product, singeList &employeeList);
void saveProductList(const product *productList, int num_of_product);
bool checkTime(const product &product);
int checkPrice(const product &product);

void printMenu_Employee();
void printMenu_Product();
void printStatusMenu();
char *pop_str_last(char *str);
void pressAnyKeyToContinue();

int main()
{
    int num_of_product = 0;
    product *productList = (product*)malloc(sizeof(product));

    int num_of_employee = 0;
    singeList employeeList; linkInitialization(employeeList);

    while(1)
    {
        printMenu_Employee();
        int choose;
        printf("\nPlease enter your choice: "); scanf("%d", &choose);

        switch(choose)
        {
        case 1:
            {
                readEmployeeListFromFile(employeeList);

                employee employee_case_1;
                addNewEmployee(employeeList, employee_case_1);

                char choose_case_1;
                int check_choose_case_1;
                do
                {
                    printStatusMenu();
                    printf("Please enter your choice: "); scanf("%c", &choose_case_1);
                    check_choose_case_1 = (int)choose_case_1;
                    if(check_choose_case_1 != 121 && check_choose_case_1 != 89 && check_choose_case_1 != 110 && check_choose_case_1 != 78)
                        printf("\nError: Invalid selection !");
                } while (check_choose_case_1 != 121 && check_choose_case_1 != 89 && check_choose_case_1 != 110 && check_choose_case_1 != 78);

                if(check_choose_case_1 == 121 || check_choose_case_1 == 89)
                    saveEmployeeList(employeeList);
                else if(check_choose_case_1 == 110 || check_choose_case_1 == 78)
                {
                    deleteNodeDataByID(employeeList, &(employeeList.pHead->data));
                    saveEmployeeList(employeeList);
                }

                deleteLinkedList(employeeList);
                pressAnyKeyToContinue();
                system("cls");
                break;
            }

        case 2:
            {
                readEmployeeListFromFile(employeeList);

                node *pTmp_index_last;
                node *firstNode  = employeeList.pHead;
                employee employee_case_2;
                addNewEmployeeList(employeeList, employee_case_2);

                char choose_case_2;
                int check_choose_case_2;
                do
                {
                    printStatusMenu();
                    printf("Please enter your choice: "); scanf("%c", &choose_case_2);
                    check_choose_case_2 = (int)choose_case_2;
                    if(check_choose_case_2 != 121 && check_choose_case_2 != 89 && check_choose_case_2 != 110 && check_choose_case_2 != 78)
                        printf("\nError: Invalid selection !");
                } while (check_choose_case_2 != 121 && check_choose_case_2 != 89 && check_choose_case_2 != 110 && check_choose_case_2 != 78);

                if(check_choose_case_2 == 121 || check_choose_case_2 == 89)
                    saveEmployeeList(employeeList);
                else if(check_choose_case_2 == 110 || check_choose_case_2 == 78)
                {
                    displayEmployeeList(employeeList);
                    pTmp_index_last = employeeList.pHead;
                    while(pTmp_index_last != firstNode)
                    {
                        pTmp_index_last = employeeList.pHead;
                        employeeList.pHead = pTmp_index_last->pNext;
                    }
                }

                deleteLinkedList(employeeList);
                pressAnyKeyToContinue();
                system("cls");
                break;
            }

        case 3:
            {
                readEmployeeListFromFile(employeeList);
                deleteLinkedList(employeeList);
                pressAnyKeyToContinue();
                system("cls");
                break;
            }

        case 4:
            {
                system("cls");
                printMenu_Product();
                int choose_product;
                do
                {
                    printf("\nPlease enter your choice: "); scanf("%d", &choose_product);
                    if(choose_product == 1)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        addNewProduct(productList, num_of_product, employeeList);
                        pressAnyKeyToContinue();

                        saveEmployeeList(employeeList);
                        saveProductList(productList, num_of_product);

                        deleteProductList(productList, num_of_employee);
                        deleteLinkedList(employeeList);

                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 2)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        addNewProductList(productList, num_of_product, employeeList);
                        pressAnyKeyToContinue();

                        saveEmployeeList(employeeList);
                        saveProductList(productList, num_of_product);

                        deleteProductList(productList, num_of_employee);
                        deleteLinkedList(employeeList);

                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 3)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        pressAnyKeyToContinue();
                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 4)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList,num_of_product,employeeList); printf("\n");
                        deleteProductByID(productList, num_of_product, employeeList); printf("\n");                     

                        saveEmployeeList(employeeList);
                        saveProductList(productList, num_of_product);
                        system("cls");

                        displayProductList(productList,num_of_product,employeeList);
                        pressAnyKeyToContinue();
                        system("cls");

                        deleteProductList(productList, num_of_employee);
                        deleteLinkedList(employeeList);

                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 5)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);
                        editProductByName(productList, num_of_product);
                        pressAnyKeyToContinue();

                        saveEmployeeList(employeeList);
                        saveProductList(productList, num_of_product);

                        deleteProductList(productList, num_of_employee);
                        deleteLinkedList(employeeList);

                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 6)
                    {
                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        sortProductsByPrice(productList, num_of_product);
                        displayProductList(productList, num_of_product, employeeList);
                        pressAnyKeyToContinue();

                        saveEmployeeList(employeeList);
                        saveProductList(productList, num_of_product);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        readProductListFromFile(productList, num_of_product, employeeList);
                        system("cls");
                        displayProductList(productList, num_of_product, employeeList);

                        deleteProductList(productList, num_of_product);
                        deleteLinkedList(employeeList);

                        system("cls");
                        printMenu_Product();
                    }

                    else if(choose_product == 0)
                        break;

                    else
                    {
                        printf("\nError: Invalid selection !");
                        printMenu_Product();
                    }
                } while (choose_product != 1 || choose_product != 2 || choose_product != 3 || choose_product != 4 || choose_product != 5 || choose_product != 6 || choose_product == 0);
                
                break;
            }

        case 5:
            {
                readEmployeeListFromFile(employeeList);
                sortEmployeesByProductCount(employeeList);
                system("cls");
                displayEmployeeList(employeeList);
                printf("\nSuccessfully arrange employee !\n");
                pressAnyKeyToContinue();
                saveEmployeeList(employeeList);
                deleteLinkedList(employeeList);
                system("cls");
                break;
            }

        case 0:
            free(productList);
            return 0;

        //choose:
        default:
            system("cls");
            printf("\nWarning: Invalid choice. Please try again !\n");
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------

void initEmployeeInformation(employee *employee)
{
    printf("\nEnter ID of the Employee: "); 
    scanf("%d", &employee->employee_id); getchar();

    printf("\nEnter the name of the Employee: ");
    fgets(employee->employee_name, sizeof(employee->employee_name) + 1, stdin); pop_str_last(employee->employee_name);

    do
    {
        printf("\nEnter the age of the Employee: ");
        scanf("%d", &employee->employee_age); getchar();
        if(checkEmployeeAge(*employee))
            printf("\nError: Age is not within working age !");
    } while (checkEmployeeAge(*employee));

    printf("\nEnter the gender of the Employee: ");
    fgets(employee->employee_gender, sizeof(employee->employee_gender) + 1, stdin); pop_str_last(employee->employee_gender);

    printf("\nEnter the address of the Employee: ");
    fgets(employee->employee_address, sizeof(employee->employee_address) + 1, stdin); pop_str_last(employee->employee_address);

    do
    {
        printf("\nRequirement: Only enter 9 numbers after the first 0 !");
        printf("\nEnter the phone number of the Employee: ");
        scanf("%10s", &employee->employee_phoneNumber);
        if(!checkEmployeePhoneNumber(*employee))
            printf("\nError: Wrong phone number format !"); 
    } while (!checkEmployeePhoneNumber(*employee));

    printf("\nNumber of products made: 0\n");
    employee->num_products_made = 0;
    getchar();

    printf("\nStatus: Created employee information successfully !");
}

node *creatNewNode(employee employee)
{
	node *pNode;
    do
    {
        pNode = (node*)malloc(sizeof(node));
        if(pNode == NULL)
            printf("\nError: Allocating memory !");
    }while(pNode == NULL);
    
    initEmployeeInformation(&employee);
    pNode->data = employee;
    pNode->pNext = NULL;
    return pNode;
}

void linkInitialization(singeList &employeeList)
{
    employeeList.pHead = employeeList.pTail = NULL;
}

bool isEmpty(singeList &employeeList)
{
    return employeeList.pHead == NULL;
}

void addNewEmployee(singeList &employeeList, employee newEmployee)
{
    bool mark;
	node *new_node;
    do
    {
        mark = false;
        new_node = creatNewNode(newEmployee);
        if(new_node->data.employee_id != 0 && isDuplicateID(employeeList, new_node->data.employee_id))
        {
            printf("\nError: Duplicate employee ID!\n");
            mark = true;
            free(new_node);
        }
    } while(mark);

    if(isEmpty(employeeList))
        employeeList.pHead = employeeList.pTail = new_node;
    else
    {
        new_node->pNext = employeeList.pHead;
        employeeList.pHead = new_node;
    }
    printf("\nStatus: Successfully added new employee !\n");
}

void addNewEmployeeList(singeList &employeeList, employee employee)
{
    int quantity; 
    do
    {
        printf("\nEnter the number of employees: "); scanf("%d", &quantity); getchar();
        if(quantity <= 0)
            printf("\nError: Number of employees cannot be negative !");
    } while (quantity <= 0);
    
    while(quantity--)
        addNewEmployee(employeeList, employee);
    printf("\nStatus: Added employee list successfully !");
}

void addNewEmployeeListToFile(singeList &employeeList, employee newEmployee)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = newEmployee;
    newNode->pNext = NULL;

    if (employeeList.pHead == NULL)
        employeeList.pHead = newNode;
    else
    {
        node *currentNode = employeeList.pHead;
        while (currentNode->pNext != NULL)
            currentNode = currentNode->pNext;
        currentNode->pNext = newNode;
    }
}

void displayEmployeeList(singeList &employeeList)
{
    node *pTmp = employeeList.pHead;
    if(pTmp == NULL)
    {
        printf("\nThe Employee list is empty !");
        return;
    }
    while(pTmp != NULL)
    {
        printf("%d, %s, %d, %s, %s, %s, %d\n",
            pTmp->data.employee_id, 
            pTmp->data.employee_name, 
            pTmp->data.employee_age, 
            pTmp->data.employee_gender, 
            pTmp->data.employee_address, 
            pTmp->data.employee_phoneNumber,
            pTmp->data.num_products_made);
        pTmp = pTmp->pNext;
    }
    printf("\nStatus: Display list of employees successfully !");
}

void sortEmployeesByProductCount(singeList &employeeList)
{
    if(employeeList.pHead->pNext == NULL || isEmpty(employeeList))
    {
        return;
    }

    bool swapped;
    node *current;
    node *temp = NULL;

    do 
    {
        swapped = false;
        current = employeeList.pHead;

        while (current->pNext != temp) {
            if (current->data.num_products_made < current->pNext->data.num_products_made) 
            {
                swapDataNode(current, current->pNext);
                swapped = true;
            }
            current = current->pNext;
        }
        temp = current;
    } while (swapped);
}

void swapDataNode(node *node_1, node *node_2)
{
    employee temp = node_1->data;
    node_1->data = node_2->data;
    node_2->data = temp;
}

bool checkEmployeePhoneNumber(const employee employee)
{
    if (strlen(employee.employee_phoneNumber) != 10) {
        return false;
    }

    if (employee.employee_phoneNumber[0] != '0') {
        return false;
    }

    for (int i = 1; i < 10; i++)
        if (employee.employee_phoneNumber[i] < '0' || employee.employee_phoneNumber[i] > '9')
            return false;

    return true;
}

bool checkEmployeeAge(employee &employee)
{
    if(employee.employee_age > 65 || employee.employee_age < 18)
        return true;
    return false;
}

bool isDuplicateID(const singeList &employeeList, int id)
{
    const node *current_node = employeeList.pHead;
    while(current_node != NULL)
    {
        if(current_node->data.employee_id == id)
            return true;
        current_node = current_node->pNext;
    }
    return false;
}

void deleteNodeDataByID(singeList &employeeList, employee *employee) 
{
    node *current = employeeList.pHead;
    node *previous = NULL;

    while (current != NULL) 
    {
        if (current->data.employee_id == employee->employee_id)  
            break;
        previous = current;
        current = current->pNext;
    }

    if (current == NULL) 
    {
        printf("\nStatus: No employee data to be deleted found !");
        return;
    }

    if (previous == NULL) 
        employeeList.pHead = current->pNext;
    else 
        previous->pNext = current->pNext;

    delete[] current;
}

void deleteLinkedList(singeList &employeeList) 
{
    struct node *current = employeeList.pHead;
    struct node *next;
    while (current != NULL) 
    {
        next = current->pNext;
        free(current);
        current = next;
    }

    employeeList.pHead = NULL; 
}

void readEmployeeListFromFile(singeList &employeeList)
{
    FILE *inputFile;
    do
    {
        inputFile = fopen("employee_list.txt", "r");
        if (inputFile == NULL) 
            printf("\nError: Could not open file !");
    } while (inputFile == NULL);

    employee employee_replacement;
    while (fscanf(inputFile, "%d, %[^,], %d, %[^,], %[^,], %[^,], %d\n",
                &employee_replacement.employee_id,
                employee_replacement.employee_name,
                &employee_replacement.employee_age,
                employee_replacement.employee_gender,
                employee_replacement.employee_address,
                employee_replacement.employee_phoneNumber,
                &employee_replacement.num_products_made) == 7)
                {
                    printf("\nStatus: Loading employee data !");
                    addNewEmployeeListToFile(employeeList, employee_replacement);
                    printf("\nStatus: Upload data successfully !\n");
                }
    printf("\n");
    system("cls");
    displayEmployeeList(employeeList);

    rewind(inputFile);
    fclose(inputFile);
}

void saveEmployeeList(const singeList &employeeList)
{
    FILE *output_file;
    do
    {
        output_file = fopen("employee_list.txt", "w");
        if (output_file == NULL) 
            printf("\nError: Could not open file !");
    } while (output_file == NULL);

    if(output_file != NULL)
    {
        const node *current_node = employeeList.pHead;
        while (current_node != NULL)
        {
            fprintf(output_file, "%d, %s, %d, %s, %s, %.10s, %d\n",
                current_node->data.employee_id,
                current_node->data.employee_name,
                current_node->data.employee_age,
                current_node->data.employee_gender,
                current_node->data.employee_address,
                current_node->data.employee_phoneNumber,
                current_node->data.num_products_made);
            printf("\n\nStatus: Saved employee successfully !\n");

            current_node = current_node->pNext;
        }

        printf("\nStatus: Employee list saved successfully !");
        fclose(output_file);
    }
    else
    {
        fprintf(stderr, "\nError: Failed to open the output file !");
    }
}

// ------------------------------------------------------------------------------------------------------------------------

void addNewProduct(product *&productList, int &num_of_product, singeList &employeeList)
{
    num_of_product++;
    product *arr_resizable;
    do
    {
        arr_resizable = (product*)malloc(num_of_product * sizeof(product));
        if(arr_resizable == NULL)
            printf("\nError: Allocating memory !");
    } while (arr_resizable == NULL);

    for(int i = 0; i < num_of_product - 1; i++)
        *(arr_resizable + i) = productList[i];

    free(productList);
    productList = arr_resizable;

    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin); pop_str_last(new_product.product_name);

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

    int employee_in_charge;
    printf("\nEnter the ID of the employee in charge: ");
    scanf("%d", &employee_in_charge); getchar();

    bool mark = false; 
    do
    {
        node *current = employeeList.pHead;
        while (current != NULL)
        {
            if(current->data.employee_id == employee_in_charge)
            {
                current->data.num_products_made++;
                new_product.employee = &(current->data);
                mark = true;
                break;
            }
            current = current->pNext;
        }
        if(mark)
            printf("\nStatus: The employee's ID has been successfully added !");
        else
            printf("\nError: Employee ID not found !");
    } while(!mark);

    arr_resizable[num_of_product - 1] = new_product;
    printf("\nStatus: Product added successfully !");
}

void addNewProductToFile(product *&productList, int &num_of_product, product *newProduct)
{
    num_of_product++;
    product *arr_resizable;
    do
    {
        arr_resizable = (product*)malloc(num_of_product * sizeof(product));
        if(arr_resizable == NULL)
            printf("\nError: Allocating memory !");
    } while (arr_resizable == NULL);

    for(int i = 0; i < num_of_product - 1; i++)
        *(arr_resizable + i) = productList[i];

    free(productList);
    productList = arr_resizable;

    arr_resizable[num_of_product - 1] = *newProduct;
    //printf("\nStatus: Downloading employee data successfully !");
}

void addNewProductList(product *&productList, int &num_of_product, singeList &employeeList)
{
    int quantity;
    do
    {
        printf("\nEnter the number of products: "); scanf("%d", &quantity); getchar();
        if(quantity <= 0)
            printf("\nError: Number of products cannot be negative !");
    } while (quantity <= 0);

    int newSize = num_of_product + quantity;
    for(int i = num_of_product; i < newSize; i++)
        addNewProduct(productList, num_of_product, employeeList);

    printf("\nStatus: Added product list successfully !");
}

void displayProductList(const product *productList, int num_of_product, singeList &employeeList)
{
    if(num_of_product == 0)
        printf("Error: Product list information does not exist !\n");
    else
    {
        for(int i = 0; i < num_of_product; i++)
        {
            printf("%d, %s, %.3lf, %d/%d/%d, %d\n",
                (*(productList + i)).product_id, 
                (*(productList + i)).product_name, 
                (*(productList + i)).product_price, 
                (*(productList + i)).product_time.day, (*(productList + i)).product_time.month, (*(productList + i)).product_time.year,
                (*(productList + i)).employee->employee_id);
        }
        printf("\nStatus: Displaying product list successfully !");
    }
}

void editProductByName(product *productList, int num_of_product)
{
    bool marker = false;
    bool check = true;
    int index_alternative_product;
    char alternative_product_name[NAME_LENGTH];

    do
    {
        printf("\nEnter the name of the alternative product: "); getchar();
        fgets(alternative_product_name, sizeof(alternative_product_name) + 1, stdin); pop_str_last(alternative_product_name);

        for(int index_product = 0; index_product < num_of_product; index_product++)
        {
            int result = strcmp(alternative_product_name, (productList[index_product].product_name));
            if(result != 0)
            {
                if(index_product == (num_of_product - 1))
                    printf("\nError: The requested product name was not found !");
            }
            else
            {
                marker = true;
                check = false;
                index_alternative_product = index_product;
                break;
            }
        }
        if(check)
            printf("\nError: No valid product name found !");
    } while (check);
    

    if(marker)
    {
        product alternative_product;

        printf("\nEnter ID of the Product: "); 
        scanf("%d", &alternative_product.product_id); getchar();

        printf("\nEnter the name of the Product: "); 
        fgets(alternative_product.product_name, sizeof(alternative_product.product_name) + 1, stdin); pop_str_last(alternative_product.product_name);

        do
        {
            printf("\nEnter the product's price: ");
            scanf("%lf", &alternative_product.product_price); getchar();
            if(!checkPrice(alternative_product))
                printf("\nError: The product's price is a non-negative number !");
        }   while (!checkPrice(alternative_product));

        do
        {
            printf("\nEnter the Product's manuafacturing date: ");
            scanf("%d%d%d", &alternative_product.product_time.day, &alternative_product.product_time.month, &alternative_product.product_time.year);
            if(!checkTime(alternative_product))
                printf("\nError: Incorrect time format !");
        } while (!checkTime(alternative_product)); 

        alternative_product.employee = (*(productList + index_alternative_product)).employee;

        *(productList + index_alternative_product) = alternative_product;
    }
}

void deleteProductByID(product *&productList, int &num_of_product, singeList &employeeList)
{
    int ID_of_product_deleted;
    do
    {
        printf("\nEnter the ID of the product to delete: "); scanf("%d", &ID_of_product_deleted); getchar();
        if(ID_of_product_deleted <= 0)
            printf("\nError: ID of products cannot be negative !");
        
    } while (ID_of_product_deleted <= 0);


    bool mark = false;
    int index_product_delete;
    for(index_product_delete = 0; index_product_delete < num_of_product; index_product_delete++)
    {
        if(ID_of_product_deleted == productList[index_product_delete].product_id)
        {
            mark = true;
            productList[index_product_delete].employee->num_products_made--;
            for(index_product_delete; index_product_delete < num_of_product; index_product_delete++)
            {
                    *(productList + index_product_delete) = *(productList + (index_product_delete + 1));
            }
            num_of_product--;
            break;
        }
    }
    if(mark == false)
    {
        printf("\nError: Cannot find product ID to delete !");
    }
}

void deleteProductList(struct product *&productList, int &num_of_product) 
{
    if (productList != NULL)
    {
       if (productList != NULL)
        {
            for (int i = 0; i < num_of_product; i++) {
                productList[i].employee = NULL;
                productList[i].key = NULL;
                productList[i].product_id = NULL;
                productList[i].product_price = NULL;
                productList[i].product_time.day = NULL;
                productList[i].product_time.month = NULL;
                productList[i].product_time.year = NULL;
            }
            num_of_product = 0;
        }
        else
        {
            printf("\nError: Product array does not exist !");
        }
    }
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

void readProductListFromFile(product *&productList, int &num_of_product, singeList &employeeList)
{
    readEmployeeListFromFile(employeeList);

    FILE *inputFile_product;
    do
    {
        inputFile_product = fopen("product_list.txt", "r");
        if (inputFile_product == NULL) 
        {
            printf("\nError: Could not open file !");
            return;
        }
    } while (inputFile_product == NULL); 

	while (true) 
    {
        product new_product;
        int result = fscanf(inputFile_product, "%d, %[^,], %lf, %d/%d/%d, %d\n",
                          &new_product.product_id,
                          new_product.product_name,
                          &new_product.product_price,
                          &new_product.product_time.day,
                          &new_product.product_time.month,
                          &new_product.product_time.year,
                          &new_product.key);

        if (result != 7) 
            break;

        node *current_node = employeeList.pHead;
        while (current_node != NULL)
        {
            if (current_node->data.employee_id == new_product.key)
            {
                new_product.employee = &(current_node->data);
                //printf("\nStatus: Loading employee data !");
                break;
            }
            current_node = current_node->pNext;
        }

        addNewProductToFile(productList, num_of_product, &new_product); printf("\n");
    }

    fclose(inputFile_product);
}

void saveProductList(const product *productList, int num_of_product)
{
    FILE *output_file = fopen("product_list.txt", "w");

    if(output_file != NULL)
    {
        for(int i = 0; i < num_of_product; i++)
        {
            fprintf(output_file, "%d, %s, %.3lf, %d/%d/%d, %d\n",
            (productList + i)->product_id, 
            (productList + i)->product_name, 
            (productList + i)->product_price, 
            (productList + i)->product_time.day, (productList + i)->product_time.month, (productList + i)->product_time.year,
            (productList + i)->employee->employee_id);
        }
        printf("\nStatus: Product list saved successfully !");
        fclose(output_file);
    }
    else
        fprintf(stderr, "\nError: Failed to open the output file !");
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

// ------------------------------------------------------------------------------------------------------------------------

void printMenu_Employee()
{
    printf("                      FACTORY MANAGEMENT PROGRAM                      \n");
    printf("\nServer: EMPLOYEE");
    printf("\n==================*** EMPLOYEE MANAGEMENT PROGRAM ***=================\n");

    printf("+----------+---------------------------------------------------------+\n");
    printf(":   S No.  : FUNCTION                                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   1st    : Create a new employee                                   :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    : Create a new employee list                              :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    : Displays a list of employees                            :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   4rd    : Server switch: PRODUCTS                                 :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   5rd    : Arrange employees based on the number of products create:\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":    0     : Exit server: EMPLOYEE                                   :\n");
    printf("+----------+---------------------------------------------------------+\n");

    printf("======================================================================");
}

void printMenu_Product()
{
    printf("                      FACTORY MANAGEMENT PROGRAM                      \n");
    printf("\nServer: PRODUCTS");
    printf("\n==================*** PRODUCTS MANAGEMENT PROGRAM ***==================\n");

    printf("+----------+---------------------------------------------------------+\n");
    printf(":   S No.  : FUNCTION                                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   1st    : Create a new product                                    :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    : Create a new product list                               :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    : Displays a list of products                             :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   4rd    : Delete the product by ID product                        :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   5rd    : Edit product information by name product                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   6rd    : Sort products by price product                          :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":    0     : Exit server: PRODUCTS                                   :\n");
    printf("+----------+---------------------------------------------------------+\n");

    printf("======================================================================");
}

void printStatusMenu()
{
    printf("\n\nWarning: Do you want to save the data you just entered into the system ?\n");
    printf("Warning: If you do not save all entered data, you will be lost !\n");
    printf("+---------------------------------+----------------------------------+\n");
    printf(":          [y] Save               :          [n] Don't save          :\n");
    printf("+---------------------------------+----------------------------------+\n");
}

char *pop_str_last(char *str) 
{
    const int len = strlen(str);
    if (len == 0)
        return '\0';
    else 
    {
        str[len - 1] = '\0';
        return str;
    }
}

void pressAnyKeyToContinue() 
{
    printf("\nPress any key to continue...");
    fflush(stdin);
    getch();
}
