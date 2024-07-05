#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool isOverlapped (int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2) {
    if(y2 <= b1 || y1 >= b2 || x1 >= a2 || x2 <= a1)
        return false;
    else
        return true;
}

int lappedArea(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2) {
    if (!isOverlapped(x1, x2, y1, y2, a1, a2, b1, b2))
        return 0;

    int overlapWidth = fmin(x2, a2) - fmax(x1, a1);
    int overlapHeight = fmin(y2, b2) - fmax(y1, b1);

    return overlapWidth * overlapHeight;
}

int area(int x1, int x2, int y1, int y2) {
    return abs((x2 - x1)) * abs((y2 - y1));
}
int main() {
    int x1, x2, y1, y2;
    int a1, a2, b1, b2;
    printf("Enter the 1st rectangle's coordinate: ");
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("Enter the 2 rectangle's coordinate: ");
    scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
    if(isOverlapped(x1, x2, y1, y2, a1, a2, b1, b2))
        printf("No.\n");
    else
        printf("Yes.\n");
    int sArea = lappedArea(x1, x2, y1, y2, a1, a2, b1, b2);
    int firstArea = area(x1, x2, y1, y2);
    int secondArea = area(a1, a2, b1, b2);
    printf("Total area of two rectangle is: %d \n", firstArea + secondArea -sArea);
    
    return 0;
}