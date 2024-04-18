#include <stdio.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

int readProductsFromFile(const char* filename, Product* productList, int maxProducts) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file.\n");
        return 0;
    }

    int numProducts = 0;
    while (fscanf(file, "%d %s %f", &productList[numProducts].id, productList[numProducts].name, &productList[numProducts].price) == 3) {
        numProducts++;
        if (numProducts >= maxProducts) {
            break;
        }
    }

    fclose(file);
    return numProducts;
}

int main() {
    Product productList[MAX_PRODUCTS];
    int numProducts = readProductsFromFile("products.txt", productList, MAX_PRODUCTS);

    // In thông tin sản phẩm đã đọc
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", productList[i].id, productList[i].name, productList[i].price);
    }

    return 0;
}