#include <stdio.h>

void prime(int n, int *arr) {
    if (n == 0 || n == 1) return;

    int idx = 0;
    for (int i = 2; i <= n; i++) {
        int res = i;
        bool check = true;
        for (int j = 2; j <= res / 2; j++) {
            if (res % j == 0) {
                check = false;
                break;
            }
        }
        if (check == true) {
            if (check == true) printf ("%d\t", res);
            *(arr + idx) = res;
            idx++;
        }
    }
}

int main() {
    int m, n, res = 0;
    scanf("%d %d", &m, &n);
    int arr[n];

    prime(n, arr);
    for (int i = 0; i < n; i++) {
        if (arr[i] >= m) {
            res += arr[i];
        }
    }

    printf("\n %d", res);
}