#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define NAME_LENGTH 100

const char finished = 'X';
const char unfinished = 'O';

struct task
{
    int id_task;
    char name_task[NAME_LENGTH];
    char status_task;
};

struct node
{
    struct task data;
    struct node *pNext;
};

typedef struct singlyLinkedList
{
    struct node *pHead;
    struct node *pTail;
} singleList;

void initToDoList(singleList &todo_list);
void initToDoTask(task *new_task);
node *creatNewDataTask(task data_task);
bool isEmptyToDoList(singleList &todo_list);
void addNewToDoTask(singleList &todo_list, task new_task);
void deleteTaskByID(singleList &todo_list);
int quantityTask(singleList &todo_list);
void displayToDoList(singleList &todo_list);
void editStatusTaskByID(singleList &todo_list);
void printMenu_Task();
char *pop_str_last(char *str);
void pressAnyKeyToContinue();

int main()
{
    int quantity_tasks = 0;
    singleList todo_list; initToDoList(todo_list);

    while(1)
    {
        printf("\n======================================================================\n");
        printf("===                         TODO LIST                              ===\n");
        displayToDoList(todo_list);
        printMenu_Task();
        int choose;
        printf("\nPlease enter your choice: "); scanf("%d", &choose);

        switch (choose)
        {
            case 1:
            {
                system("cls");
                task new_task;
                addNewToDoTask(todo_list, new_task);
                pressAnyKeyToContinue();
                system("cls");
                break;
            }

            case 2:
                {
                    system("cls");
                    displayToDoList(todo_list);
                    deleteTaskByID(todo_list);
                    system("cls");
                    displayToDoList(todo_list);
                    pressAnyKeyToContinue();
                    system("cls");
                    break;
                }
                
            case 3:
                {
                    system("cls");
                    displayToDoList(todo_list);
                    editStatusTaskByID(todo_list);
                    system("cls");
                    displayToDoList(todo_list);
                    pressAnyKeyToContinue();
                    system("cls");
                    break;
                }

            case 0:
                return 0;
            
            default:
                system("cls");
                printf("\nWarning: Invalid choice. Please try again !\n");
                break;
        }
    }
}

void initToDoList(singleList &todo_list)
{
    todo_list.pHead = todo_list.pTail = NULL;
}

void initToDoTask(task *new_task)
{
    printf("\nPlease enter ID task: "); 
    scanf("%d", &new_task->id_task); getchar();

    printf("\nPlease enter your task: ");
    fgets(new_task->name_task, sizeof(new_task->name_task) + 1, stdin); pop_str_last(new_task->name_task);

    new_task->status_task = unfinished;
}

node *creatNewDataTask(task data_task)
{
    node *new_task;
    do
    {
        new_task = (node*)malloc(sizeof(node));
        if(new_task == NULL)
            printf("\nError: Allocating memory !");
    } while (new_task == NULL);
    
    initToDoTask(&data_task);
    new_task->data = data_task;
    new_task->pNext = NULL;
    return new_task;
}

void addNewToDoTask(singleList &todo_list, task new_task)
{
    node *data_new_task = creatNewDataTask(new_task);

    if(isEmptyToDoList(todo_list))
        todo_list.pHead = todo_list.pTail = data_new_task;
    else
    {
        todo_list.pTail->pNext = data_new_task;
        todo_list.pTail = data_new_task;
    }

    printf("\nStatus: Successfully added new task !");
}

int quantityTask(singleList &todo_list)
{
    node *pCount = todo_list.pHead;
    int quantity = 0;

    while (pCount == NULL)
    {
        pCount = pCount->pNext;
        quantity++;
    }

    return quantity;    
}

void displayToDoList(singleList &todo_list)
{
    if(isEmptyToDoList(todo_list))
    {
        printf("+---------------+-------------------------------------------+--------+\n");
        printf(": ID            : Task Name                                 : Status :\n");
        printf("+---------------+-------------------------------------------+--------+\n");
        printf("======================================================================\n");
        return;
    }

    printf("+---------------+-------------------------------------------+--------+\n");
    printf(": ID            : Task Name                                 : Status :\n");
    printf("+---------------+-------------------------------------------+--------+\n");
    node *cur = todo_list.pHead;
    while (cur != NULL)
    {
        printf(": %-12d  ", cur->data.id_task);
        printf(": %-42s", cur->data.name_task);
        printf(": %-7c:", cur->data.status_task);
        printf("\n+---------------+-------------------------------------------+--------+\n");
        cur = cur->pNext;
    }
    printf("======================================================================\n");
}

void deleteTaskByID(singleList &todo_list)
{
    if(isEmptyToDoList(todo_list))
    {
        printf("\nError: The ToDo List is empty !");
        return;
    }

    int ID;
    printf("\nPlease enter the ID of the task to delete: "); 
    scanf("%d", &ID); getchar();

    node *cur = todo_list.pHead;
    node *previous = NULL;
    
    while(cur != NULL)
    {
        if(cur->data.id_task == ID)
            break;
        previous = cur;
        cur = cur->pNext;
    }

    if(cur == NULL)
    {
        printf("\nStatus: No task data to be deleted found !");
        return;
    }

    if(previous == NULL)
        todo_list.pHead = cur->pNext;
    else
        previous->pNext = cur->pNext;

    delete[] cur;
}

void editStatusTaskByID(singleList &todo_list)
{
    if(isEmptyToDoList(todo_list))
    {
        printf("\nError: The ToDo List is empty !");
        return;
    }

    int ID;
    printf("\nPlease enter the ID of the task to edit: "); 
    scanf("%d", &ID); getchar();

    node *cur = todo_list.pHead;
    
    while(cur != NULL)
    {
        if(cur->data.id_task == ID)
            break;
        cur = cur->pNext;
    }

    if(cur == NULL)
    {
        printf("\nStatus: No task data to be deleted found !");
        return;
    }
    else
    {
        cur->data.status_task = finished;
        printf("\nNotification: Mission status updated successfully !");
    }
}

bool isEmptyToDoList(singleList &todo_list)
{
    return todo_list.pHead == NULL;
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
    printf("\n\nPress any key to continue...");
    fflush(stdin);
    getch();
}

void printMenu_Task()
{
    printf("\n\n\n");
    printf("----------------------------------------------------------------------\n");
    printf(":   1st    : Create a new task                                       :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    : Delete task by ID                                       :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    : Edit status task                                        :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":    0     : Exit ToDo List                                          :\n");
    printf("----------------------------------------------------------------------");
}
