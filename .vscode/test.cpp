#include <stdio.h>
#include <conio.h>

void pressAnyKeyToContinue() 
{
    printf("\nPress any key to continue...");
    getch();
}

int main()
{
    pressAnyKeyToContinue();
    return 0;
}